#include "MemoryInfo.h"
#include "ProcessorInfo.h"
#pragma once

class CSystemInfo{
public:
	CSystemInfo(void);
	~CSystemInfo(void);

public:
	CProcessorInfo getProcessorInfo();	
	CMemoryInfo getMemoryInfo();
};
