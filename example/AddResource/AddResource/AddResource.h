#pragma once

bool AddResource(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData);

bool AddResourceData(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData);


bool AddIconResource(
				 LPCTSTR szExe, 
				 LPCTSTR szResName,
				 LPCTSTR szResType,
				 const LPVOID lpData,
				 const DWORD cbData);