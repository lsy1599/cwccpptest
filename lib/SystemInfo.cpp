#include "StdAfx.h"
#include "SystemInfo.h"
#include <windows.h>
#include <atlbase.h>
CSystemInfo::CSystemInfo(void)
{
}

CSystemInfo::~CSystemInfo(void)
{
}

/**
 * ���o�B�z����T
 *
 */
CProcessorInfo CSystemInfo::getProcessorInfo(){
	// Ū���n���� HKEY_LOCAL_MACHINE\HARDWARE\DESCRIPTION\System\CentralProcessor\0
	CRegKey reg;
	CProcessorInfo info;
    if(reg.Open(HKEY_LOCAL_MACHINE, _T("HARDWARE\DESCRIPTION\System\CentralProcessor\0") )== ERROR_SUCCESS) {
		DWORD dValue ;
        if (reg.QueryDWORDValue(_T("~MHz"), dValue)==ERROR_SUCCESS){
			info.MHz = dValue;
        }

        if (reg.QueryDWORDValue(_T("Platform ID"), dValue)==ERROR_SUCCESS){
			info.PlatformID = dValue;
        }

		TCHAR szValue[1024];
		ULONG szValueSize = sizeof(szValue)/sizeof(szValue[0]);
		reg.QueryStringValue(_T("ProcessorNameString"), szValue, &szValueSize);
		_tcsncpy(info.Name, szValue, szValueSize);

	}

	return info;
}

/**
 * ���o�O�����T
 *
 */
CMemoryInfo CSystemInfo::getMemoryInfo(void){    
    MEMORYSTATUS memoryStatus;
    ZeroMemory( &memoryStatus,sizeof(MEMORYSTATUS) );
    memoryStatus.dwLength = sizeof(MEMORYSTATUS);

    ::GlobalMemoryStatus ( &memoryStatus );

    //return Ceil(memoryStatus.dwTotalPhys/1024/1024);

	return CMemoryInfo(memoryStatus);
}
