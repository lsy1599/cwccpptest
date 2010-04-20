#include "stdafx.h"
#include "AddResource.h"
#include "Icon.h"

bool AddResource(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData)
{
	if(MAKEINTRESOURCE(RT_ICON) == szResType)
	{
		return AddIconResource(szExe, szResName, szResType, lpData, cbData);
	}
	
	return AddResourceData(szExe, szResName, szResType, lpData, cbData);
}


bool AddResourceData(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData)
{
	if(
		NULL == szExe		|| 
		NULL == szResName	||
		NULL == szResType	||
		NULL == lpData		||
		0 == cbData
		)
	{
		return false;
	}

	// synchronize resource update
	HANDLE hMutex = ::CreateMutex(
		NULL,
		TRUE,
		_T("Mutex_AddResrouceManagedApp"));

	if(NULL == hMutex)
	{
		return false;
	}

	// request ownership
	::WaitForSingleObject(hMutex, INFINITE);

	HANDLE hUpdateRes = ::BeginUpdateResource(
		szExe,
		FALSE);

	if(NULL == hUpdateRes)
	{
		// ERROR: 
		return false;
	}

	bool bRes = false;

	if(0 == ::UpdateResource(
		hUpdateRes,	// update resource handle 
		szResType,	// type
		szResName,	// name
		MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),  // language
		lpData,		// ptr to resource info 
		cbData)) // size of resource info. 
	{
		DWORD dwErr = ::GetLastError();
		// ERROR: Could not add resource
	}	

	if(0 != (::EndUpdateResource(hUpdateRes, FALSE)))
	{
		bRes = true;
	}

	::ReleaseMutex(hMutex);

	return bRes;
}


#define ReadFromBuffer(dest, src, size) memcpy(dest, src, size); src += size;
bool IsIntResource(LPCTSTR& szRes);

// get the highest number found as icon name
BOOL CALLBACK EnumIconsProc(
	HMODULE hModule,
    LPCTSTR lpszType,
    LPTSTR lpszName,
    LONG_PTR lParam
)
{	
	int* pnMaxIcon = (int*)lParam; 

	if(TRUE == IS_INTRESOURCE(lpszName))
	{		
		int nName = PtrToInt(lpszName); 

		if(nName > *pnMaxIcon)
		{
			*pnMaxIcon = nName;
		}
	}

	return TRUE;
}

int getLastIconId(LPCTSTR szExe)
{
	// Load the DLL/EXE without executing its code
	HMODULE hLib = ::LoadLibraryEx(szExe, NULL, LOAD_LIBRARY_AS_DATAFILE );
	if(hLib == NULL)
	{
		return -1;
	}

	int nIcon = 0;
	if(0 == ::EnumResourceNames(hLib, RT_ICON, EnumIconsProc, (LONG_PTR)&nIcon))
	{
		nIcon = -1;
	}

	FreeLibrary(hLib);
	return nIcon;
}

bool AddIconResource(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData)
{
	LPBYTE pBuff = (LPBYTE)lpData;

	LPGRPICONDIR pGrpIconDir = (LPGRPICONDIR)malloc( sizeof( GRPICONDIR ) );
	ReadFromBuffer( &(pGrpIconDir->idReserved), pBuff, sizeof( WORD ));
	ReadFromBuffer( &(pGrpIconDir->idType), pBuff, sizeof( WORD ));
	ReadFromBuffer( &(pGrpIconDir->idCount), pBuff, sizeof( WORD ));
	if(0 == pGrpIconDir->idCount)
	{
		goto CleanUp;
	}

	pGrpIconDir = (LPGRPICONDIR)realloc( pGrpIconDir, ( sizeof( WORD ) * 3 ) + sizeof( GRPICONDIRENTRY ) * pGrpIconDir->idCount );
	
	int nStartID = getLastIconId(szExe) + 1;
	if(-1 == nStartID)
	{
		goto CleanUp;
	}

	// set icon id's
	for(int i = 0; i < pGrpIconDir->idCount; ++i)
	{
		pGrpIconDir->idEntries[i].nID = i + nStartID;
	}

	// add icon group
	if(!AddResourceData(
		szExe,
		szResName,
		RT_GROUP_ICON,
		pGrpIconDir,
		sizeof(GRPICONDIR) + sizeof(GRPICONDIRENTRY) * (pGrpIconDir->idCount - 1)))
	{
		goto CleanUp;
	}


	LPICONDIRENTRY lpIconDirEntry = (LPICONDIRENTRY)pBuff;
	for(int i = 0; i < pGrpIconDir->idCount; ++i)
	{
		// add each icon
		// resource name is the id		
		if(!AddResourceData(
			szExe,
			MAKEINTRESOURCE(pGrpIconDir->idEntries[i].nID),
			MAKEINTRESOURCE(RT_ICON),
			(LPBYTE)lpData + lpIconDirEntry->dwImageOffset,
			lpIconDirEntry->dwBytesInRes))
		{
			goto CleanUp;
		}

		++lpIconDirEntry;
	}
	
CleanUp:

	free(pGrpIconDir);

	return true;
}
