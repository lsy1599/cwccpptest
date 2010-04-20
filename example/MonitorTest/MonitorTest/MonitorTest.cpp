// MonitorTest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <string>

void printSetting(int w, int h, int pixel){
    //std::wcout << w << "x" << h << "x" << pixel << "\n";
}

class Monitor{
public:


    Monitor(DISPLAY_DEVICE& dd)
    : m_id(dd.DeviceID), m_key(dd.DeviceKey), m_name(dd.DeviceName),m_desc(dd.DeviceString){
    
    }
private:

    std::wstring m_id;    
    std::wstring m_key;
    std::wstring m_name;
    std::wstring m_desc;
};

class MonitorManager : public std::vector<Monitor>{
public:

private:
    
};

int _tmain(int argc, _TCHAR* argv[])   {
DEVMODE dm;
ZeroMemory(&dm, sizeof(dm));
dm.dmSize = sizeof(dm);
EnumDisplaySettingsEx(_T("\\\\.\\DISPLAY2"), ENUM_REGISTRY_SETTINGS, &dm, 0);
HDC dc = CreateDC(_T("\\\\.\\DISPLAY2"), 0, 0, &dm);
HBRUSH oldBrush = static_cast<HBRUSH>(SelectObject(dc, GetStockObject(WHITE_BRUSH)));
Rectangle(dc, 0, 0, dm.dmPelsWidth, dm.dmPelsHeight);
MoveToEx(dc, 0, 0, 0);
LineTo(dc, dm.dmPelsWidth, dm.dmPelsHeight);
SelectObject(dc, oldBrush);
DeleteDC(dc); 
return 0;
/*
    HDC dc1= CreateDC(L"DISPLAY", L"\\.\DISPLAYV1", NULL, NULL);
    HDC dc2= CreateDC(L"DISPLAY", L"\\.\DISPLAYV2", NULL, NULL);
    
    MoveToEx(dc1, 0, 0, NULL); 
    LineTo(dc1, 100, 100);
    
    MoveToEx(dc2, 0, 0, NULL); 
    LineTo(dc2, 100, 100);
        */
    // 找出顯示器的總數量
    int  i;
    BOOL flag;
    DISPLAY_DEVICE dd;
    
 
    DEVMODEW   lpDEVMODE;   
    lpDEVMODE.dmSize   =   sizeof   (   DEVMODE   );   
    
    i = 0;
    flag = true;
    ZeroMemory(&dd, sizeof(dd));
    dd.cb = sizeof(dd);
    MonitorManager mm;
    do {
        //Monitor m;
        flag = EnumDisplayDevices(NULL, i, &dd, 0);
        //flag = EnumDisplayDevices(NULL, i, &m, 0);        
        if (flag) {
            //Monitor m(dd);
            //mm.push_back( m );    
            std::wcout << i<< ": \n"
                << "ID: " << dd.DeviceID << "\n"
                << "Key: "<<dd.DeviceKey << "\n"
                << "Name: " << dd.DeviceName << "\n"
                << "Desc: " << dd.DeviceString << "\n"
                << "??: " << (DISPLAY_DEVICE_ATTACHED_TO_DESKTOP & dd.StateFlags) << "\n"
                << "State: " << dd.StateFlags << "\n\n"   ; 
                
            

                
            DWORD   iModeNum   =   0;  
            int   dmBitsPerPel   =   0;  
            int   dmPelsWidth;  
            int   dmPelsHeight;           
            
            if(   EnumDisplaySettings   (   NULL,   ENUM_CURRENT_SETTINGS,   &lpDEVMODE)   ) {  
                  dmBitsPerPel   =   lpDEVMODE.dmBitsPerPel;  
                  dmPelsWidth   =   lpDEVMODE.dmPelsWidth;  
                  dmPelsHeight   =   lpDEVMODE.dmPelsHeight;  
                  
//if (DISPLAY_DEVICE_ATTACHED_TO_DESKTOP & dd.StateFlags){
            //    std::wcout << "GOT:" << i << "**\n\n";
            //}else{
                HDC dc1 = CreateDC(dd.DeviceName, NULL, NULL, &lpDEVMODE);
                if (dc1 == NULL){
                    std::wcout << "Create DC Fail\n";
                    ++i;
                    continue;
                }
                MoveToEx(dc1, 0, 0, NULL); 
                LineTo(dc1, 400, 400);    
                DeleteDC(dc1);                              
//            }
                  
                  printSetting(dmPelsWidth, dmPelsHeight, dmBitsPerPel);
            }   
                            
            while(   EnumDisplaySettings   (   NULL,   iModeNum++,   &lpDEVMODE)   ) {  
                  dmBitsPerPel   =   lpDEVMODE.dmBitsPerPel;  
                  dmPelsWidth   =   lpDEVMODE.dmPelsWidth;  
                  dmPelsHeight   =   lpDEVMODE.dmPelsHeight;  
                  std::wcout << "****\n";
                  printSetting(dmPelsWidth, dmPelsHeight, dmBitsPerPel);
            }   
                          
            i += 1;
        }
    } while (flag);



    return 0;
    }

