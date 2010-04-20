// CXmlDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CXmlDemo.h"
#include "CXmlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCXmlDemoApp

BEGIN_MESSAGE_MAP(CCXmlDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCXmlDemoApp construction

CCXmlDemoApp::CCXmlDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCXmlDemoApp object

CCXmlDemoApp theApp;


// CCXmlDemoApp initialization

BOOL CCXmlDemoApp::InitInstance()
{
	CWinApp::InitInstance();

	//Do not forget CoInitialize
	::CoInitialize(NULL);


	CCXmlDemoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CCXmlDemoApp::ExitInstance()
{
	::CoUninitialize();

	return CWinApp::ExitInstance();
}
