#include <windows.h>
#pragma once

class CMemoryInfo {
public:
	CMemoryInfo(const MEMORYSTATUS& status){
		m_status = status;
	}

	~CMemoryInfo(void){}
public:
	SIZE_T getTotalPhysicalByte(){
		return m_status.dwTotalPhys;
	}

	DWORD getMemoryLoad(){
		return m_status.dwMemoryLoad;
	}

	SIZE_T getAvaliablePhysiscalByte(){
		return m_status.dwAvailPhys;
	}

	SIZE_T getTotalVirtualByte(){
		return m_status.dwTotalVirtual;
	}
	SIZE_T getAvaliableVirtualByte(){
		return m_status.dwAvailVirtual;
	}
	SIZE_T getTotalPageFileByte(){
		return m_status.dwTotalPageFile;
	}
	SIZE_T getAvaliablePageFileByte(){
		return m_status.dwAvailPageFile;
	}
protected:
	MEMORYSTATUS m_status;
};
