// CXmlDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CXmlDemo.h"
#include "CXmlDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCXmlDemoDlg dialog




CCXmlDemoDlg::CCXmlDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCXmlDemoDlg::IDD, pParent)
	, m_strSampleCode(_T(""))
	, m_strXmlContent(_T(""))
{
}

void CCXmlDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CODE, m_strSampleCode);
	DDX_Text(pDX, IDC_EDIT_XML, m_strXmlContent);
}

BEGIN_MESSAGE_MAP(CCXmlDemoDlg, CDialog)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCXmlDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCXmlDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCXmlDemoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCXmlDemoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CCXmlDemoDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CCXmlDemoDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CCXmlDemoDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CCXmlDemoDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CCXmlDemoDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CCXmlDemoDlg message handlers

BOOL CCXmlDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	OnBnClickedButton1();

	return TRUE;  // return TRUE  unless you set the focus to a control
}



// get the execute path
CString CCXmlDemoDlg::GetAppPath()
{
	TCHAR szFullPath[MAX_PATH]; 
	CString szPath("");
	int nPos;
	nPos = 0;

	GetModuleFileName(NULL, szFullPath, MAX_PATH);
	szPath.Format(_T("%s"), szFullPath);
	nPos = szPath.ReverseFind('\\');
	if(nPos != -1)
	{
		szFullPath[nPos + 1] = 0x00;
	}
	szPath.Format(_T("%s"), szFullPath);
	return szPath;
}



void CCXmlDemoDlg::ReloadXmlFile()
{
	if( m_objXml.GetXmlFile().IsEmpty() )
	{
		m_strXmlContent = _T("");
		UpdateData(FALSE);
		return;
	}

	m_objXml.Save();
	CFile file;
	if( file.Open(m_objXml.GetXmlFile(), NULL) )
	{
		LPBYTE pBuf = new BYTE[file.GetLength() + 1];
		::ZeroMemory( pBuf, file.GetLength() + 1);
		file.Read( pBuf, file.GetLength());
		file.Close();

		// here, for test purpose, we just use UTF-8 xml file
		USES_CONVERSION;
		m_strXmlContent = A2T((LPSTR)pBuf);
		delete [] pBuf;

		UpdateData(FALSE);
	}

}

void CCXmlDemoDlg::OnBnClickedButton1()
{
	VERIFY( m_objXml.Open( GetAppPath() + _T("test.xml") ) );

	m_strSampleCode =	_T("CoInitialize(NULL);\r\n")
						_T("...\r\n")
						_T("m_objXml.Open( \"<file path>\" )\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}


void CCXmlDemoDlg::OnBnClickedButton2()
{
	AfxMessageBox( _T("the inner text of node a is:") + m_objXml.GetRoot()->GetChild( _T("a"), FALSE)->GetValue() );

	m_strSampleCode =	_T("m_objXml.GetRoot()->GetChild( _T(\"a\"), FALSE)->GetValue()\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}

void CCXmlDemoDlg::OnBnClickedButton3()
{
	m_objXml.GetRoot()->GetChild( _T("a"), FALSE)->SetValue(GetTickCount());

	m_strSampleCode =	_T("m_objXml.GetRoot()->GetChild( _T(\"a\"), FALSE)->SetValue(GetTickCount())\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}

void CCXmlDemoDlg::OnBnClickedButton4()
{
	AfxMessageBox( _T("the attribute name of c is:\n") +
		m_objXml.GetRoot()->GetChild( _T("b") )->GetChild(_T("c"))->GetAttribute( _T("name") )
		);

	m_strSampleCode =	_T("m_objXml.GetRoot()->GetChild( _T(\"b\") )->GetChild(_T(\"c\"))->GetAttribute( _T(\"name\") )\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}

void CCXmlDemoDlg::OnBnClickedButton5()
{
	m_objXml.GetRoot()->GetChild( _T("b") )->GetChild(_T("c"))->SetAttribute( _T("time"), GetTickCount() );

	m_strSampleCode =	_T("m_objXml.GetRoot()->GetChild( _T(\"b\") )->GetChild(_T(\"c\"))->SetAttribute( _T(\"time\"), GetTickCount() );\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}

void CCXmlDemoDlg::OnBnClickedButton6()
{
	CString strTemp = _T("");
	
	CXmlNodes nodes;
	nodes= m_objXml.GetRoot()->GetChild( _T("d") )->GetChildren();
	for( int i = 0; i < nodes.GetCount(); i++)
	{
		strTemp += nodes[i]->GetValue() + _T(",");
	}
	

	m_strSampleCode =	_T("CXmlNodes nodes;\r\n")
	_T("nodes= m_objXml.GetRoot()->GetChild( _T(\"d\") )->GetChildren();\r\n")
	_T("for( int i = 0; i < nodes.GetCount(); i++)\r\n")
	_T("{\r\n")
	_T("	strTemp += nodes[i]->GetValue() + _T(\",\");\r\n")
	_T("}\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();

	AfxMessageBox(strTemp);
}

void CCXmlDemoDlg::OnBnClickedButton8()
{
	for( int i = 0; i < 4; i++)
		m_objXml.GetRoot()->GetChild(_T("f"))->NewChild(_T("g"))->SetValue( GetTickCount() );


	m_strSampleCode =	_T("for( int i = 0; i < 4; i++)\r\n")
		_T("m_objXml.GetRoot()->GetChild(_T(\"f\"))->NewChild(_T(\"g\"))->SetValue( GetTickCount() );\r\n");

	UpdateData(FALSE);

	ReloadXmlFile();
}


void CCXmlDemoDlg::OnBnClickedButton7()
{
	m_objXml.GetRoot()->GetChild(_T("f"))->RemoveChildren();

	m_strSampleCode =	_T("m_objXml.GetRoot()->GetChild(_T(\"f\"))->RemoveChildren();\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();
}


void CCXmlDemoDlg::OnBnClickedButton9()
{
	CString strXPath = _T("//xmlRoot/h[@id='1']");
	CXmlNode node;
	node = m_objXml.SelectSingleNode(strXPath);

	m_strSampleCode =	_T("CString strXPath = _T(\"//xmlRoot/h[@id='1']\");\r\n")
		_T("CXmlNode node;\r\n")
		_T("node = m_objXml.SelectSingleNode(strXPath);\r\n");
	UpdateData(FALSE);

	ReloadXmlFile();

	AfxMessageBox( _T("the name of the item is:\n") + node.GetName());
}
