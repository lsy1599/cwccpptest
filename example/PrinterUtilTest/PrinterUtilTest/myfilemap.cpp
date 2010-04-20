/*
 * 
 * myfilemap.c
 *
   Copyright (C) 2006 Michael H. Overlin

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
   
   Contact at poster_printer@yahoo.com
 */

#include <assert.h>
#include <windows.h> 

#include "myfilemap.h"


MyFileMap::MyFileMap(void) {
	this->hFile = INVALID_HANDLE_VALUE;
	this->hMap = NULL;
	this->lpMap = NULL;
	this->dwSize = 0;
}

MyFileMap::~MyFileMap() {
	if (IsOpen()) {
		this->Close();
	}
}

BOOL MyFileMap::Open(const tstring& tstr) {
	BOOL bRetValue = FALSE;

	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hMap = NULL;
	LPVOID lpMap = NULL;

	try {
		hFile = CreateFile( 
			tstr.c_str(),
			GENERIC_READ,           
			FILE_SHARE_READ,        
			NULL,                   
			OPEN_EXISTING,          
			FILE_ATTRIBUTE_NORMAL,  
			NULL                     
			);

		if (hFile != INVALID_HANDLE_VALUE) {
			hMap = CreateFileMapping(
				hFile,
				NULL,
				PAGE_READONLY,
				0,
				0,
				NULL
				);
		
			if (hMap != NULL) {
				lpMap = MapViewOfFile(
					hMap,
					FILE_MAP_READ,
					0,
					0,
					NULL
					);
				if (lpMap != NULL) {
					this->dwSize = GetFileSize(hFile, NULL);
					this->hFile = hFile;
					this->hMap = hMap;
					this->lpMap = lpMap;

					bRetValue = TRUE;
				}
			}
		}
		if (!bRetValue) {
			if (lpMap != NULL) {
				UnmapViewOfFile(lpMap);
			}
			if (hMap != NULL) {
				CloseHandle(hMap);
			}
			if (hFile != INVALID_HANDLE_VALUE) {
				CloseHandle(hFile);
			}
		}
	} catch(...) {
		bRetValue = FALSE;
		if (lpMap != NULL) {
			try { UnmapViewOfFile(lpMap); } catch(...) {}
		}
		if (hMap != NULL) {
			try { CloseHandle(hMap); } catch (...) {}
		}
		if (hFile != INVALID_HANDLE_VALUE) {
			try { CloseHandle(hFile); } catch (...) {}
		}
	}


	return bRetValue;
}

void MyFileMap::Close(void) {
	assert(this->lpMap != NULL);
	assert(this->hMap != NULL);
	assert(this->hFile != INVALID_HANDLE_VALUE);

	// SO I DON'T HAVE TO DEAL WITH EXCEPTIONS
	// TO ENSURE OBJECT STAYS IN VALID STATE BELOW
	// IF EXCEPTION OCCURS, LET HANDLES HANG (FOR NOW)
	LPVOID lpMap = this->lpMap;
	HANDLE hMap = this->hMap;
	HANDLE hFile = this->hFile;

	this->lpMap = NULL;
	this->hMap = NULL;
	this->hFile = INVALID_HANDLE_VALUE;
	this->dwSize = 0;

	UnmapViewOfFile(lpMap);
	CloseHandle(hMap);
	CloseHandle(hFile);
}

const void* MyFileMap::GetBasePtr(VOID) const { 
	assert(this->IsOpen());
	return this->lpMap; 
}

const void* MyFileMap::GetOffsetPtr(const DWORD dwOffset) const {
	PCBYTE lp = (PCBYTE) GetBasePtr();
	assert(dwOffset < this->dwSize);
	return (LPCVOID) (lp + dwOffset);
}

DWORD MyFileMap::GetSize(VOID) const { 
	assert(this->IsOpen());
	return this->dwSize; 
}

// ****************************************************************************************

MyFileReadWriteMap::MyFileReadWriteMap(void) {
	this->hFile = INVALID_HANDLE_VALUE;
	this->hMap = NULL;
	this->lpMap = NULL;
	this->dwSize = 0;
}

MyFileReadWriteMap::~MyFileReadWriteMap() {
	if (IsOpen()) {
		this->Close();
	}
}

BOOL MyFileReadWriteMap::Create(const tstring& tstr, DWORD dwCb) {
	BOOL bRetValue = FALSE;

	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hMap = NULL;
	LPVOID lpMap = NULL;

	try {
		hFile = CreateFile( 
			tstr.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ,        
			NULL,                   
			CREATE_ALWAYS,          
			FILE_ATTRIBUTE_NORMAL,  
			NULL                     
			);

		if (hFile != INVALID_HANDLE_VALUE) {
			hMap = CreateFileMapping(
				hFile,
				NULL,
				PAGE_READWRITE,
				0,
				dwCb,
				NULL
				);
		
			if (hMap != NULL) {
				lpMap = MapViewOfFile(
					hMap,
					FILE_MAP_WRITE,
					0,
					0,
					dwCb
					);
				if (lpMap != NULL) {
					this->dwSize = dwCb;
					this->hFile = hFile;
					this->hMap = hMap;
					this->lpMap = lpMap;

					bRetValue = TRUE;
				}
			}
		}
		if (!bRetValue) {
			if (lpMap != NULL) {
				UnmapViewOfFile(lpMap);
			}
			if (hMap != NULL) {
				CloseHandle(hMap);
			}
			if (hFile != INVALID_HANDLE_VALUE) {
				CloseHandle(hFile);
			}
		}
	} catch(...) {
		bRetValue = FALSE;
		if (lpMap != NULL) {
			try { UnmapViewOfFile(lpMap); } catch(...) {}
		}
		if (hMap != NULL) {
			try { CloseHandle(hMap); } catch (...) {}
		}
		if (hFile != INVALID_HANDLE_VALUE) {
			try { CloseHandle(hFile); } catch (...) {}
		}
	}


	return bRetValue;
}

void MyFileReadWriteMap::Close(void) {
	assert(this->lpMap != NULL);
	assert(this->hMap != NULL);
	assert(this->hFile != INVALID_HANDLE_VALUE);

	// SO I DON'T HAVE TO DEAL WITH EXCEPTIONS
	// TO ENSURE OBJECT STAYS IN VALID STATE BELOW
	// IF EXCEPTION OCCURS, LET HANDLES HANG (FOR NOW)
	LPVOID lpMap = this->lpMap;
	HANDLE hMap = this->hMap;
	HANDLE hFile = this->hFile;

	this->lpMap = NULL;
	this->hMap = NULL;
	this->hFile = INVALID_HANDLE_VALUE;
	this->dwSize = 0;

	UnmapViewOfFile(lpMap);
	CloseHandle(hMap);
	CloseHandle(hFile);
}

void* MyFileReadWriteMap::GetBasePtr(void)  { 
	assert(this->IsOpen());
	return this->lpMap; 
}

void* MyFileReadWriteMap::GetOffsetPtr(const DWORD dwOffset)  {
	PCBYTE lp = (PCBYTE) GetBasePtr();
	assert(dwOffset < this->dwSize);
	return (void *) (lp + dwOffset);
}

DWORD MyFileReadWriteMap::GetSize(VOID) const { 
	assert(this->IsOpen());
	return this->dwSize; 
}

HANDLE MyFileReadWriteMap::GetFileMapHandle(void) {
	return this->hMap;
}
