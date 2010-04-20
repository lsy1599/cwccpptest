// CXmlDemoDlg.h : header file
//

#pragma once

#include "./CXml/Xml.h"
using namespace Generic;


// CCXmlDemoDlg dialog
class CCXmlDemoDlg : public CDialog
{
// Construction
public:
	CCXmlDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CXMLDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	// the xml class
	CXml			m_objXml;

	CString m_strSampleCode;
	CString m_strXmlContent;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	CString GetAppPath();

	void ReloadXmlFile();
	
public:
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
