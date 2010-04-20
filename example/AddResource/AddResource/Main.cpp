// AddResourceManaged.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <shlwapi.h>
#include "AddResourceFile.h"

int _tmain(int argc, _TCHAR* argv[])
{

	if(argc < 3)
	{
		_tprintf(_T("\nError: Invalid number of arguments"));
		return -1;
	}

	// check if EXE exists
	LPCTSTR szExe = argv[1];
	if(FALSE == PathFileExists(szExe))
	{
		// ERROR: file does not exists
		_tprintf(_T("\nError: Executable file does not exists"));
		return -1;
	}

	LPCTSTR szResFile = argv[2];
	LPCTSTR szResName = NULL;
	LPCTSTR szResType = NULL;

	if(argc > 3)
	{
		szResName = argv[3];

		if(argc > 4)
		{
			szResType = argv[4];
		}
	}

	DWORD dwErr = 0;

	if((szResFile != NULL) && (0 != PathIsDirectory(szResFile)))
	{
		// path is a directory
		// add as resources all files from directory
		return AddDirectoryFilesAsResources(szExe, szResFile, szResType) ? 0 : -1;
	}
	else
	{
		// path is a file
		return AddFileAsResource(szExe, szResFile, szResName, szResType) ? 0 : -1;								
	}

	_tprintf(_T("\nSuccess !"));
	
	return 0;
}

