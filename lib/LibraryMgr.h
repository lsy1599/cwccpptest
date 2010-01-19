// Yet another DLL manager class
// Copyright (c) 2007 Boris Oleinic <obn@inbox.ru>
// You may do whatever you like with this file, I just don't care.

#include <windows.h>
#include <string>

#ifndef LIBRARYMGR_H_INCLUDED
#define LIBRARYMGR_H_INCLUDED

class LibraryMgr_t
{
public:
	LibraryMgr_t(void);
	LibraryMgr_t(const TCHAR* ptcFileName);

	~LibraryMgr_t(void);

	bool LoadLibrary( const TCHAR* ptcFileName );
	bool FreeLibrary();

	FARPROC GetProcAddress( const char* ptcProcName );

	HMODULE GetModuleHandle();

	bool GetModuleFileName(std::basic_string<TCHAR>& sName);

	bool FreeLibraryAndExitThread( DWORD dwExitCode );

	void SetAutoFree(bool bFree) { m_bAutoFree = bFree; }

private:
	HMODULE m_hModule;
	bool m_bAutoFree;
	std::basic_string<TCHAR> m_sFileNAme;

};

#endif //LIBRARYMGR_H_INCLUDED