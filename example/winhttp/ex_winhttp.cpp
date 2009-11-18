// ex_winhttp.cpp : 定義主控台應用程式的進入點。
//

#include <windows.h>
#include <string>
#include <iostream>
#import <winhttp.dll> named_guids

int main(void)
{
  ::CoInitialize(NULL);
  std::string Uri = "http://www.google.com/";
  std::string Moved;
  WinHttp::IWinHttpRequestPtr Request;
  Request.CreateInstance(WinHttp::CLSID_WinHttpRequest);
  Request->Option[WinHttp::WinHttpRequestOption_EnableRedirects] = false;

  for (int i = 0; i < 10; ++i) {
    Request->Open("GET", Uri.c_str());
    Request->Send();
    long Status = Request->Status;
    if (Status == 301 || Status == 302 || Status == 303 || Status == 307) {
      Uri = Request->GetResponseHeader("Location");
      if (Status == 301) {
        Moved = Uri;
      }
    }else {
      break;
    }
  }

  if (!Moved.empty()) {
    std::cout << "Moved Permanently. New URI = " << Moved;
  }

  std::cout << Request->ResponseText;
  ::CoUninitialize();

  return 0;
}