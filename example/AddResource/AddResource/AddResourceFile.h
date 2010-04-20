#pragma once

bool AddFileAsResource(
					   LPCTSTR szExe,
					   LPCTSTR szResFile,
					   LPCTSTR szResName,
					   LPCTSTR szResType);

bool AddDirectoryFilesAsResources(
						LPCTSTR szExe,
						LPCTSTR szResDirectory,
						LPCTSTR szResType);