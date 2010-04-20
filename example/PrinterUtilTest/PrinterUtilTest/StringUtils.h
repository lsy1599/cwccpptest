#ifndef __STRING_UTILS__
#define __STRING_UTILS__

#include <strsafe.h>
#include <assert.h>

typedef unsigned int	uint;
/**
 * �r��һݰO����Ŷ�
 *
 * @parmam lptstr	�r��
 * @return			�O����Ŷ�
 */
size_t StringBufferSize(IN LPCTSTR lptstr) {
	size_t szRetValue = 0;
	TCHAR atstr[] = TEXT("");
	HRESULT hr = StringCbLength(lptstr, STRSAFE_MAX_CCH * sizeof(TCHAR), &szRetValue);
	assert(hr == S_OK);
	szRetValue += sizeof(atstr);
	return szRetValue;
}

/**
 * �r��ƥ�
 *
 * @param	lptstr	�r��ӷ�
 * @return			�ƥ�	
 */
LPTSTR StringDuplicate(IN LPCTSTR lptstr) {
	size_t sz = StringBufferSize(lptstr);
	LPTSTR lptstrDup = (LPTSTR) malloc(sz);
	CopyMemory(lptstrDup, lptstr, sz);
	return lptstrDup;
}


LPTSTR vMyCatStringsString(BOOL bIncludeNullTerms, LPCTSTR lptstrArg, va_list& in_vaList) {
	DWORD dwCchExtra = (bIncludeNullTerms ? 1 : 0);
	LPTSTR lptstrRetValue = NULL;

	va_list vaList = in_vaList;
	DWORD dwCch = 0;
	for(LPCTSTR lptstr = lptstrArg; lptstr != NULL; lptstr = va_arg(vaList, LPCTSTR)) {
		dwCch += ::lstrlen(lptstr) + dwCchExtra;
	}
	++ dwCch;

	lptstrRetValue = (LPTSTR) malloc(dwCch * sizeof(TCHAR));
	if (lptstrRetValue != NULL) {
		LPTSTR lptstrCtr = lptstrRetValue;
		vaList = in_vaList;
		for(LPCTSTR lptstr = lptstrArg; lptstr != NULL; lptstr = va_arg(vaList, LPCTSTR)) {
			dwCch = ::lstrlen(lptstr) + dwCchExtra;
			memcpy(lptstrCtr, lptstr, dwCch * sizeof(TCHAR));
			lptstrCtr += dwCch;
		}
		*lptstrCtr = 0;
	}

	return lptstrRetValue;
}

LPTSTR MyCatStringsString(BOOL bIncludeNullTerms, LPCTSTR lptstrArg, ...) {
	va_list vaList;
	va_start(vaList, lptstrArg);
	LPTSTR lptstrRetValue = ::vMyCatStringsString(bIncludeNullTerms, lptstrArg, vaList);
	va_end(vaList);
	return lptstrRetValue;
}


LPTSTR *MyCatStringPtrs(LPTSTR lptstrArg, ...) {
	LPTSTR *plptstrRetValue = NULL;
	va_list vaList;

	va_start(vaList, lptstrArg);
	unsigned int nStrings = 0;
	for(LPCTSTR lptstr = lptstrArg; lptstr != NULL; lptstr = va_arg(vaList, LPCTSTR)) {
		++ nStrings;
	}
	++ nStrings; // INCLUDING SPACE FOR NULL TERMINATOR
	va_end(vaList);

	plptstrRetValue = (LPTSTR *) malloc(nStrings * sizeof(LPTSTR));
	if (plptstrRetValue != NULL) {
		va_start(vaList, lptstrArg);
		unsigned int k = 0;
		for(LPTSTR lptstr = lptstrArg; lptstr != NULL; lptstr = va_arg(vaList, LPTSTR)) {
			plptstrRetValue[k ++] = lptstr;
		}
		plptstrRetValue[k] = NULL;
		va_end(vaList);
	}

	return plptstrRetValue;
}

void MyFreeStringPtrs(LPTSTR *plptstr) {
	for(uint k = 0; plptstr[k]; ++k) {
		free(plptstr[k]);
	}
	free(plptstr);
}


/**
 * �r��X��
 *
 * @param	lptstrArg		
 * @return					�X�֫�r��
 */
LPTSTR MyCatStrings(LPCTSTR lptstrArg, ...) {
	va_list vaList;
	va_start(vaList, lptstrArg);
	LPTSTR lptstrRetValue = ::vMyCatStringsString(FALSE, lptstrArg, vaList);
	va_end(vaList);
	return lptstrRetValue;
}


/**
 * �r��X��
 *
 * @param	lptstrDir		�ؿ��W��
 * @param	lptstrFileName	�ɮצW��
 * @param	lptstrExt		���ɦW
 * @return					�X�֫�r��
 */
LPTSTR MakeFullFileName(LPCTSTR lptstrDir, LPCTSTR lptstrFileName, IN LPCTSTR lptstrExt) {
	LPTSTR lptstrRetValue = MyCatStrings(lptstrDir, TEXT("\\"), lptstrFileName, lptstrExt, NULL);
	return lptstrRetValue;
}
#endif