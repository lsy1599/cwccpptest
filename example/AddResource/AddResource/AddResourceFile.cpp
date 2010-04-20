#include "StdAfx.h"
#include ".\addresourcefile.h"
#include "FileMapping.h"
#include "AddResource.h"
#include <shlwapi.h>
#include "Icon.h"

#if _MSC_VER >= 1400
#include <stdlib.h>
#include <errno.h>
#endif

//
// getResTypeFromFileType
//
LPCTSTR getResTypeFromFileType(LPCTSTR szResFile)
{
	if(szResFile == NULL)
	{
		return NULL;
	}

	/*
	typedef map<string, LPCTSTR> MapTypes;
	MapTypes mapTypes;

	mapTypes[_T(".html")] = RT_HTML;
	mapTypes[_T(".htm")] = RT_HTML;
	mapTypes[_T(".bmp")] = RT_BITMAP;
	mapTypes[_T(".ico")] = RT_ICON;

	LPCTSTR szExtension = PathFindExtension(szResFile);
	MapTypes::const_iterator it = mapTypes.find(szExtension);
	if(mapTypes.end() == it)
	{
		return RT_RCDATA;
	}
	else
	{
		return it->second;
	}
	*/

	LPCTSTR szExtension = PathFindExtension(szResFile);
	if((_tcsicmp(szExtension, _T(".htm")) == 0) || (_tcsicmp(szExtension, _T(".html")) == 0)) //PathIsHTMLFile 
	{
		return RT_HTML;
	}
	else
		if(_tcsicmp(szExtension, _T(".bmp")) == 0)
		{
			return RT_BITMAP;
		}
		else
			if(_tcsicmp(szExtension, _T(".ico")) == 0)
			{
				return RT_ICON;
			}

	return RT_HTML;
}


void MakeUpper(LPCTSTR& szRes)
{
	// make the resource name and type upper case
	// this is a MUST for the resources name and type

	TCHAR* szResUp = new TCHAR[_tcslen(szRes) + 1];
	_tcscpy(szResUp, szRes);
	_tcsupr(szResUp);

	szRes = szResUp;
}

bool IsIntResource(LPCTSTR& szRes)
{
   	int id = _tstoi(szRes);

	// check if its an integer and its resource id
	if(
#if _MSC_VER < 1400
		(0 != id) && 
#else
		// for MS 2005 check the global err var
		(0 != id) && (ERANGE != errno) &&
#endif		
		(TRUE == IS_INTRESOURCE(id)))
	{
		szRes = MAKEINTRESOURCE(id);
		return true;
	}
	else
	{
		return false;
	}
}

//
// AddFileAsResource
//
bool AddFileAsResource(
					   LPCTSTR szExe,
					   LPCTSTR szResFile,
					   LPCTSTR szResName,
					   LPCTSTR szResType)
{
	if( (NULL == szExe) ||
		(NULL == szResFile))
	{
		return false;
	}

	bool bIsNameIntRes = false;
	bool bIsTypeIntRes = false;
	bool bRet = false;
	
	if(NULL == szResName)
	{
		// use the resource filename as the resource name
		szResName = PathFindFileName(szResFile);
	}
	else
	{
		bIsNameIntRes = IsIntResource(szResName);
	}

	if(NULL == szResType)
	{
		// try to determine the resource type based on resource file extension
		szResType = getResTypeFromFileType(szResFile);
		bIsTypeIntRes = true;
	}
	else
	{
		bIsTypeIntRes = IsIntResource(szResType);
	}


	if(!bIsNameIntRes)
	{
		// if its not a predefined resource make it upper case
		MakeUpper(szResName);
	}

	if(!bIsTypeIntRes)
	{
		// if its not a predefined resource make it upper case
		MakeUpper(szResType);
	}



	// map the resource file
	FileMapping fileMapping;
	if(!fileMapping.create(szResFile))
	{
		printf(_T("\nmapping the resource file failed"));
		goto CleanUp;
	}
	

	if(!AddResource(
		szExe, 
		szResName,
		szResType,
		fileMapping.getData(),
		fileMapping.getSize()
		))
	{
		printf(_T("\nadding resource failed"));
		goto CleanUp;
	}

	bRet = true;

CleanUp:
	if(!bIsNameIntRes)
	{
		delete szResName; szResName = NULL;
	}

	if(!bIsTypeIntRes)
	{
		delete szResType; szResType = NULL;
	}

	return bRet;
}

//
// AddDirectoryFilesAsResources
//
bool AddDirectoryFilesAsResources(
						LPCTSTR szExe,
						LPCTSTR szResDirectory,
						LPCTSTR szResType)
{
	if( (NULL == szExe) ||
		(NULL == szResDirectory))
	{
		return false;
	}

	TCHAR szDirSpec[MAX_PATH];  // directory specification
	_tcscpy(szDirSpec, szResDirectory);
	PathAppend(szDirSpec, _T("*.*"));

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = ::FindFirstFile(szDirSpec, &findFileData);

	if (INVALID_HANDLE_VALUE == hFind) 
	{
		//printf ("Invalid file handle. Error is %u\n", GetLastError());
		return false;
	} 
	else 
	{
		//printf ("First file name is %s\n", FindFileData.cFileName);
		do
		{
			if( 
				((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == findFileData.dwFileAttributes) &&
				(_tcsicmp(findFileData.cFileName, _T(".")) == 0) ||
				(_tcsicmp(findFileData.cFileName, _T("..")) == 0))
			{
				continue;
			}

			TCHAR szResFile[MAX_PATH];
			_tcscpy(szResFile, szResDirectory);
			PathAppend(szResFile, findFileData.cFileName);

			bool bRet = AddFileAsResource(szExe, szResFile, NULL, szResType);
		}
		while (::FindNextFile(hFind, &findFileData) != 0);

		DWORD dwError = ::GetLastError();
		
		::FindClose(hFind);
		if (dwError != ERROR_NO_MORE_FILES) 
		{
			//printf ("FindNextFile error. Error is %u\n", dwError);
			return false;
		}
	}

   return true;
}
