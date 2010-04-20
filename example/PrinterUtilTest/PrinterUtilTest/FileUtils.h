#ifndef __FILE_UTILS__
#define __FILE_UTILS__

#include "myfilemap.h"
#include "CoreUtils.h"

#pragma comment(lib, "Lz32.lib")

const TCHAR FALLBACK_TEMP_PATH[]	= TEXT(".\\");
const int MAX_TEMP_PATH_CCH	= (MAX_PATH - 14);


/**
 * 取得驅動程式目錄
 *
 * @return	驅動程式目錄
 */
LPTSTR MyGetPrinterDriverDirectory(void) {
	LPTSTR lptstrRetValue = NULL;
	DWORD dwCbNeeded;
	::GetPrinterDriverDirectory(NULL, NULL, 1, 0, 0, &dwCbNeeded);
	if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
		lptstrRetValue = (LPTSTR) malloc(dwCbNeeded);
		if (lptstrRetValue != NULL) {
			if ( ! ::GetPrinterDriverDirectory(NULL, NULL, 1, (LPBYTE) lptstrRetValue, dwCbNeeded, &dwCbNeeded)) {
				free(lptstrRetValue);
				lptstrRetValue = NULL;
			}
		}
	} 
	return lptstrRetValue;
}

/**
 * 將資源檔的資料寫入檔案
 *
 * @param	hInst
 * @param	lptstrFileName
 * @param	wIDResource
 * @param	wIDType
 * @return
 */
BOOL WriteResourceToFile(HINSTANCE hInst, LPCTSTR lptstrFileName, WORD wIDResource, WORD wIDType/*, const ::SYSTEMTIME* psystimeStamp*/) {
	BOOL bRetValue = FALSE;
	HRSRC hResInfo = ::FindResource(hInst, MAKEINTRESOURCE(wIDResource), MAKEINTRESOURCE(wIDType));
	if (hResInfo != NULL) {
		HGLOBAL hgRes = ::LoadResource(hInst, hResInfo);
		if (hgRes != NULL) {
			void *pvRes = ::LockResource(hgRes);
			if (pvRes != NULL) {
				DWORD dwcRes = ::SizeofResource(hInst, hResInfo);
				try {
					::MyFileReadWriteMap mfm;
					if (mfm.Create(lptstrFileName, dwcRes)) {
						::CopyMemory( mfm.GetBasePtr(), pvRes, dwcRes );
						bRetValue = TRUE;
					}
				} catch( ... ) {
					bRetValue = FALSE;
				}

				//HANDLE hFile = ::CreateFile(lptstrFileName, 
				//	GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
				//if (hFile != INVALID_HANDLE_VALUE) {
				//	try {
				//		DWORD dwcWritten;
				//		if ( ::WriteFile(hFile, pvRes, dwcRes, &dwcWritten, 0)) {
				//			if (dwcWritten == dwcRes) {
				//				bRetValue = TRUE;
				//			} 
				//		}
				//		//if (bRetValue) {
				//		//	if (psystimeStamp != NULL) {
				//		//		::FILETIME ft;
				//		//		if (::SystemTimeToFileTime(psystimeStamp, &ft)) {
				//		//			if (! ::SetFileTime(hFile, &ft, NULL, &ft)) {
				//		//				bRetValue = FALSE;
				//		//			}
				//		//		} else {
				//		//			bRetValue = FALSE;
				//		//		}
				//		//	}
				//		//}
				//		CloseHandle(hFile);
				//	} catch( ...) {
				//		CloseHandle(hFile);
				//	}
				//}
				UnlockResource(hgRes);
			}
			::FreeResource(hgRes);
		}
	}

	if (!bRetValue) {
		try { ::DeleteFile(lptstrFileName); } catch (...) {}
	}

	return bRetValue;
}

/**
 * 取得 TEMP 目錄
 * 
 * @param	lptstrPath		字串緩衝區
 * @param	dwcChBuff		緩衝區大小,  BUFFER HAVE SPACE FOR MAX_TEMP_PATH_CCH+1 TCHARS
 */
void MyGetTempPath(LPTSTR lptstrPath, DWORD dwcChBuff) {
	assert(dwcChBuff >= 3);
	DWORD dwcChLength = ::GetTempPath(dwcChBuff, lptstrPath); // LENGTH IS STRING LENGTH
	if (dwcChLength == 0 || dwcChLength > dwcChBuff-1) {
		::StringCchCopy(lptstrPath, dwcChBuff, FALLBACK_TEMP_PATH);
	}
}

/**
 * 取得包含路徑的暫存名稱
 *
 * @param lptstrTempFileName	字串緩衝區
 * @param dwcChBuff				緩衝區大小, dwcChBuff MUST BE AT LEAST MAX_PATH + 1 
 * @return						TRUE, FALSE=
 */
BOOL GetFullTempFileName(LPTSTR lptstrTempFileName, DWORD dwcChBuff) {
	assert(dwcChBuff >= MAX_PATH+1);

	TCHAR atstrTempPath[MAX_TEMP_PATH_CCH+1];
	::MyGetTempPath(atstrTempPath, ARRCOUNT(atstrTempPath));
	BOOL bSuccess = ::GetTempFileName(atstrTempPath, NULL, 0, lptstrTempFileName) != 0;
	return bSuccess;
}


/**
 * 解開資源檔
 *
 *
 */
BOOL DecompressResource(IN HINSTANCE hInst, IN WORD wIDResource, IN WORD wIDType, OUT PVOID& pv, OUT DWORD& dwCb) {
	BOOL bRetValue = FALSE;
	TCHAR atstrTempFileName[MAX_PATH+1];
	if (::GetFullTempFileName(atstrTempFileName, ARRCOUNT(atstrTempFileName))) {
		if (::WriteResourceToFile(hInst, atstrTempFileName, wIDResource, wIDType/*, psystimeStamp*/)) {
			try {
				::OFSTRUCT of;
				INT iFile = ::LZOpenFile(atstrTempFileName, &of, OF_READ);
				if (iFile >= 0) {
					PVOID pvTemp = NULL;
					try {
						LONG lCb = ::LZSeek(iFile, 0, 2);
						if (lCb > 0 && lCb <= INT_MAX) {
							if (::LZSeek(iFile, 0, 0) == 0) {
								pvTemp = malloc(lCb);
								if (pvTemp != NULL) {
									INT iRead = ::LZRead(iFile, (LPSTR) pvTemp, (INT) lCb) ;
									if (iRead == lCb) {
										pv = pvTemp;
										pvTemp = NULL;
										dwCb = lCb;
										bRetValue = TRUE;
									}
								}
							}
						}
						::LZClose(iFile);
						if (pvTemp != NULL) {
							free(pvTemp);
						}
					} catch( ... ) {
						::LZClose(iFile);
						if (pvTemp != NULL) {
							free(pvTemp);
						}
					}
				}
			} catch( ... ) {
			}
			try { ::DeleteFile(atstrTempFileName); } catch(...) {}
		}
	}
	return bRetValue;
}

/**
 * 將壓縮在資源檔的資料寫入檔案
 *
 * @param	hInst
 * @param	lptstrFileName
 * @param	wIDResource
 * @param	wIDType
 * @return
 */
BOOL WriteCompressedResourceToFile(HINSTANCE hInst, LPCTSTR lptstrFileName, 
								   WORD wIDResource, WORD wIDType/*, const ::SYSTEMTIME* psystimeStamp*/) {
	BOOL bRetValue = FALSE;
	TCHAR atstrTempFileName[MAX_PATH+1];
	if (::GetFullTempFileName(atstrTempFileName, ARRCOUNT(atstrTempFileName))) {
		if (::WriteResourceToFile(hInst, atstrTempFileName, wIDResource, wIDType/*, psystimeStamp*/)) {
			try {
				::OFSTRUCT of;
				INT iFile = ::LZOpenFile(atstrTempFileName, &of, OF_READ);
				if (iFile >= 0) {
					try {
						LONG lCb = ::LZSeek(iFile, 0, 2);
						if (lCb > 0 && lCb <= INT_MAX) {
							if (::LZSeek(iFile, 0, 0) == 0) {
								try {
									::MyFileReadWriteMap mfm;
									if (mfm.Create(lptstrFileName, lCb)) {
										void *pv = mfm.GetBasePtr();
										if (::LZRead(iFile, (LPSTR) pv, (INT) lCb) == lCb) {
											bRetValue = TRUE;
										}
									}
								} catch( ... ) {
								}
							}
						}
						::LZClose(iFile);
					} catch( ... ) {
						::LZClose(iFile);
					}
				}
			} catch( ... ) {
			}
			try { ::DeleteFile(atstrTempFileName); } catch(...) {}
		}
	}

	if (!bRetValue) {
		try { ::DeleteFile(lptstrFileName); } catch(...) {}
	}
	return bRetValue;
}


#endif