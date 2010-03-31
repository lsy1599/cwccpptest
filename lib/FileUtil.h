#ifndef __FILE_UTIL__
#define __FILE_UTIL__

#include <string>
#include <algorithm>
#include <direct.h>
#include <windows.h>

using namespace std;

bool FolderExists(const char* path);


/**
 *
 * example:
struct isSep{
	bool operator()(char c){
		return c == '\\';
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	const char* path = "c:\\a\\b\\c\\d\\";
	string sPath(path);
	rTrim<isSep>( sPath ); 
	CreateFolder( sPath.c_str() );
	return 0;
}
 */
template<typename checker>
void rTrim(std::string& str){	
	string::iterator i;
	checker chk;
	for (i = str.end() - 1; ;i--) {
		if (!chk(*i)) {
			str.erase(i + 1, str.end());
			break;
		}
		if (i == str.begin()) {
			str.clear();
			break;
		}
	}
}

void CreateFolder(const char* path);

#endif