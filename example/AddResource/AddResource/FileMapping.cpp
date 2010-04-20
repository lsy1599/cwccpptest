#include "StdAfx.h"
#include <windows.h>
#include ".\filemapping.h"

FileMapping::FileMapping() :
m_hFile(NULL),
m_hMapping(NULL),
m_lpData(NULL),
m_dwSize(0),
m_dwError(ERROR_SUCCESS)
{
}

FileMapping::~FileMapping(void)
{
	close();
}

bool FileMapping::create(LPCTSTR szFile)
{
	// 
	m_hFile = ::CreateFile(
		szFile,
		GENERIC_READ,
		0, 
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if(INVALID_HANDLE_VALUE == m_hFile)
	{
		// ERROR: cannot open the file
		m_dwError = ::GetLastError();
		return false;
	}

	DWORD hDw;
	if(INVALID_FILE_SIZE == (m_dwSize = GetFileSize(m_hFile, &hDw)))
	{
		// Error getting the file size
		m_dwError = ::GetLastError();
		cleanUp();
		return false;
	}

	m_hMapping = ::CreateFileMapping(
		m_hFile,
		0,
		PAGE_READONLY,
		0,
		0,
		NULL);

	if(NULL == m_hMapping)
	{
		// ERROR: cannot create file mapping
		m_dwError = ::GetLastError();
		cleanUp();
		return false;
	}

	m_lpData = ::MapViewOfFile(
		m_hMapping,
		FILE_MAP_READ,
		0,
		0,
		0);

	if(NULL == m_lpData)
	{
		// ERROR: mapping the view faield	
		m_dwError = ::GetLastError();
		cleanUp();
		return false;
	}

	return true;
}

void FileMapping::close()
{
	cleanUp();
}

LPVOID FileMapping::getData() const
{
	return m_lpData;
}

void FileMapping::cleanUp()
{
	if(m_lpData != NULL)
	{
		::UnmapViewOfFile(m_lpData); 
		m_lpData = NULL;
	}

	if(m_hMapping != NULL)
	{
		::CloseHandle(m_hMapping);
		m_hMapping = NULL;
	}

	if(m_hFile != NULL)
	{
		::CloseHandle(m_hFile);
		m_hFile = NULL;
	}
}