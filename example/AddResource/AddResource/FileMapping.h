#pragma once

class FileMapping
{
protected:

	HANDLE m_hFile;
	HANDLE m_hMapping;
	LPVOID m_lpData;
	DWORD m_dwSize;
	DWORD m_dwError;

	void cleanUp();

public:

	FileMapping();
	~FileMapping();

	bool create(LPCTSTR szFile);
	void close();

	LPVOID getData() const;
	DWORD getLastError() const { return m_dwError; }
	DWORD getSize() const { return m_dwSize; }
};