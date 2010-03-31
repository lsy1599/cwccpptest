#include "stdafx.h"
#include "FileUtil.h"

bool FolderExists(const char* path){
	bool ret;
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
		ret = true;
	}else{
		ret = false;
	}
    FindClose(hFind);

	return ret;
}




void CreateFolder(const char* path){	
	if(FolderExists(path)){
		return;
	}else{
		string s(path);
		string sep("\\");		
		string::iterator pos = std::find_end(s.begin(), s.end(), sep.begin(), sep.end());

		if (pos != s.end()){
			string s2(s.begin(), pos);
			//std::cout << s2 << std::endl;
			if (!FolderExists(s2.c_str())){
				CreateFolder(s2.c_str());
			}
			_mkdir(path);
		}
	}

}