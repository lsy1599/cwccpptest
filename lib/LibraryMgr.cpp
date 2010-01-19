// Yet another DLL manager class
// Copyright (c) 2007 Boris Oleinic <obn@inbox.ru>
// You may do whatever you like with this file, I just don't care.

#include "LibraryMgr.h"


LibraryMgr_t::LibraryMgr_t(void)
: m_hModule(0), m_bAutoFree(true)
{
}

LibraryMgr_t::LibraryMgr_t(const TCHAR* ptcFileName)
: m_hModule(0), m_bAutoFree(true)
{
	LoadLibrary( ptcFileName );
}

LibraryMgr_t::~LibraryMgr_t(void)
{
	if ( m_hModule && m_bAutoFree )
	{
		FreeLibrary();
	}
}

bool LibraryMgr_t::LoadLibrary(
							 const TCHAR* ptcFileName
							 )
{
	if (! ptcFileName)
		return false;

	if ( m_hModule )
	{
		FreeLibrary();
	}

	m_sFileNAme.assign( ptcFileName );
	m_hModule = ::LoadLibrary( m_sFileNAme.c_str() );

	if (m_hModule == 0){
		MessageBox(0, ptcFileName, 0, 0);
	}
	return m_hModule != NULL;
}

bool LibraryMgr_t::FreeLibrary()
{
	if( ! m_hModule )
		return false;

	::FreeLibrary( m_hModule );
	m_hModule = NULL;
	m_sFileNAme.erase();
	//Msgbox( m_sFileNAme.length() ); 

	return true;
}

FARPROC LibraryMgr_t::GetProcAddress(
		const char* ptcProcName
		)
{
	if( ! m_hModule )
		return NULL;

	return ::GetProcAddress( m_hModule, ptcProcName );
}

HMODULE LibraryMgr_t::GetModuleHandle()
{
	if( ! m_hModule )
		return NULL;

	return ::GetModuleHandle( m_sFileNAme.c_str() );
}

bool LibraryMgr_t::GetModuleFileName(std::basic_string<TCHAR>& sName)
{
	if( ! m_hModule )
		return false;

	sName.assign( m_sFileNAme );
	return true;
}

bool LibraryMgr_t::FreeLibraryAndExitThread( DWORD dwExitCode )
{
	if( ! m_hModule )
		return false;

	::FreeLibraryAndExitThread( m_hModule, dwExitCode );

	m_hModule = 0;

	return true;
}