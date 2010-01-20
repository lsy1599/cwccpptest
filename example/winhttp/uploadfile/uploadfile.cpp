// uploadfile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "myhttprequest.h"
#include <iostream>


int main(int argc, char* argv[]){ 
	HttpRequest req;
/*
	std::wcout << req.SyncHttpRequest(
		BSTRPtr(L"POST").get(),
		BSTRPtr(L"http://192.168.10.120:2527/data.php?name=arick&sex=1").get(),
		BSTRPtr(L"method=post").get()
	) << std::endl;
	
	std::wcout << req.SyncHttpRequest(
		BSTRPtr(L"GET").get(),
		BSTRPtr(L"http://192.168.10.120:2527/data.php?name=arick&sex=1").get(),
		BSTRPtr(L"method=post").get()
	) << std::endl;
*/

	req.UploadFile(BSTRPtr(L"http://192.168.10.120:2527/file.php").get(), 
		BSTRPtr(L"method=post").get());
	return 0;
}


