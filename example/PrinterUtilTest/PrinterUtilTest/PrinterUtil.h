#ifndef __PRINTER_UTIL__
#define __PRINTER_UTIL__

#include <windows.h>
#include <winspool.h>
#include <memory>

#include "StringUtils.h"
/**
 * ���o Printer ��T
 *
 * @param	hPrinter	Printer Handle
 * @return				Printer ��T���c
 */
PPRINTER_INFO_2 GetPrinterInfo2(IN HANDLE hPrinter) {
	PPRINTER_INFO_2 pinfo = NULL;
	DWORD dwcNeeded = 0;
	GetPrinter(hPrinter, 2, NULL, 0, &dwcNeeded);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		BOOL b;
		pinfo = (PPRINTER_INFO_2) malloc(dwcNeeded);
		b = GetPrinter(hPrinter, 2, (LPBYTE) pinfo, dwcNeeded, &dwcNeeded);
		if (b) {
			return pinfo;
		}
	}

	if (pinfo != NULL) {
		free(pinfo);
	}
		
	return NULL;
}

/**
 * ���o�L����`��
 *
 * @param dwcPrinterDrivers	�L����ƶq
 * @return					�Ҧ��L�����T			
 */
::PDRIVER_INFO_3 GetInstalledPrinterDrivers(OUT DWORD& dwcPrinterDrivers ) {
	::PDRIVER_INFO_3 pinfo = NULL;
	DWORD dwTemp;
	DWORD dwCbNeeded;
	::EnumPrinterDrivers(NULL, NULL, 3, NULL, 0, &dwCbNeeded, &dwTemp);
	if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		pinfo = (::PDRIVER_INFO_3) malloc(dwCbNeeded);
		if (pinfo != NULL) {
			if (! ::EnumPrinterDrivers(NULL, NULL, 3, (LPBYTE) pinfo, dwCbNeeded, &dwCbNeeded, &dwTemp)) {
				free(pinfo);
				pinfo = NULL;
			} else {
				dwcPrinterDrivers = dwTemp;
			}
		}
	}
	return pinfo;
}

/**
 * ���o Printer ��T
 *
 * @param	hPrinter	Printer �W��
 * @return				Printer ��T���c
 */
PPRINTER_INFO_2 GetPrinterInfo2(IN LPCTSTR lptstrPrinterName) {
	PPRINTER_INFO_2 pinfoRetValue = NULL;
	HANDLE hPrinter = NULL;
	OpenPrinter((LPTSTR) lptstrPrinterName, &hPrinter, NULL);
	if (hPrinter != NULL) {
		pinfoRetValue = GetPrinterInfo2(hPrinter);
		ClosePrinter(hPrinter);
	}
	return pinfoRetValue;
}

/**
 * ���o Printer ��T
 *
 * @param	hPrinter	Printer Handle
 * @return				Printer ��T���c
 */
::PDRIVER_INFO_3 GetPrinterDriverInfo3(IN HANDLE hPrinter) {
	::PDRIVER_INFO_3 pinfo = NULL;
	DWORD dwCbNeeded;
	::GetPrinterDriver(hPrinter, NULL, 3, 0, 0, &dwCbNeeded);
	if ( ::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		pinfo = (::PDRIVER_INFO_3) malloc(dwCbNeeded);
		if (pinfo != NULL) {
			if ( ! ::GetPrinterDriver(hPrinter, NULL, 3, (LPBYTE) pinfo, dwCbNeeded, &dwCbNeeded)) {
				free(pinfo);
				pinfo = NULL;
			}
		}
	}
	return pinfo;
}



/**
 * �ˬd�L����W�٬O�_�w�g�s�b
 *
 * @parmam lptstrName	�L����W��
 * @return				TRUE=�s�b, FALSE=���s�b
 */
BOOL IsPrinterInstalled(LPCTSTR lptstrName) {
	if (lptstrName != NULL) {
		HANDLE hPrinter = NULL;
		OpenPrinter((LPTSTR) lptstrName, &hPrinter, NULL);
		if (hPrinter != NULL) {
			ClosePrinter(hPrinter);
			return TRUE;
		}
	}
	return FALSE;
}

/**
 * �H Handle ���o Printer Name
 *
 * @param	hPrinter	Printer Handle
 * @return				Printer Name
 */
LPTSTR GetPrinterName(IN HANDLE hPrinter) {
	LPTSTR lptstrRetValue = NULL;
	PPRINTER_INFO_2 pinfo = GetPrinterInfo2(hPrinter);
	if (pinfo != NULL) {
		lptstrRetValue = ::StringDuplicate(pinfo->pPrinterName);
		free(pinfo);
	}
	return lptstrRetValue;
}


/**
 * �ˬd���w���L����O�_�w�g�w�ˡA�åB�^�ǫ��w�L�����T
 *
 * @param	out_pinfoDrivers
 * @param	out_kDriver
 * @param	lptstrDriverName
 * @return						TRUE=���, FALSE=�S���
 */
BOOL CheckPrinterDriverInstalled(OUT ::PDRIVER_INFO_3& out_pinfoDrivers, OUT unsigned int& out_kDriver, 
								 IN LPCTSTR lptstrDriverName) {
	BOOL bRetValue = FALSE;
	DWORD dwcPrinterDrivers;
	::PDRIVER_INFO_3 pinfoDrivers = ::GetInstalledPrinterDrivers(dwcPrinterDrivers);
	if (pinfoDrivers != NULL) {
		BOOL bFound = FALSE;
		unsigned int kDriver;
		for(kDriver = 0; kDriver < dwcPrinterDrivers; ++kDriver) {
			if (::lstrcmpi(pinfoDrivers[kDriver].pName, lptstrDriverName) == 0) {
				bFound = TRUE;
				break;
			}
		}

		if (bFound) {
			out_kDriver = kDriver;
			out_pinfoDrivers = pinfoDrivers;
		} else {
			free(pinfoDrivers);
			out_pinfoDrivers = NULL;
		}
		bRetValue = TRUE;
	}
	return bRetValue;
}




#endif