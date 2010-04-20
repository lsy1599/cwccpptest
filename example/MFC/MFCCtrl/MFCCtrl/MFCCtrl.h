// MFCCtrl.h : main header file for the MFCCtrl DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCCtrlApp
// See MFCCtrl.cpp for the implementation of this class
//

class CMFCCtrlApp : public CWinApp
{
public:
	CMFCCtrlApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
