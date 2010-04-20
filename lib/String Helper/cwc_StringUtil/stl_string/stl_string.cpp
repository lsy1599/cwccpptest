/**
 *
 * @ref	http://www.codeproject.com/useritems/STL_string_util.asp
 */
#include <iostream>
#include <string>
#include "StringUtil.h"

using namespace std;



int main()
{
	string str = "  Chui-Wen Chiu  ";
	cout << "-->" << str << "<--" << endl;
	cwc::StringUtil::rTrim(str);
	cout << "-->" << str << "<--" << endl;

	return 0;
}

