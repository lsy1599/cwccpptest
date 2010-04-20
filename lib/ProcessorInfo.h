#include <windows.h>
#pragma once

class CProcessorInfo{
public:
	CProcessorInfo(void);
	~CProcessorInfo(void);
public:
	DWORD MHz;
	DWORD PlatformID;
	LPTSTR Name;
};
