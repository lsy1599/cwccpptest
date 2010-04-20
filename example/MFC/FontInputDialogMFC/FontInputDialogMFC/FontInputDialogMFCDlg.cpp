// FontInputDialogMFCDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FontInputDialogMFC.h"
#include "FontInputDialogMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFontInputDialogMFCDlg dialog




CFontInputDialogMFCDlg::CFontInputDialogMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontInputDialogMFCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontInputDialogMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFontInputDialogMFCDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CFontInputDialogMFCDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CFontInputDialogMFCDlg message handlers

BOOL CFontInputDialogMFCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here	
	m_edit = static_cast<CEdit*>( GetDlgItem(IDC_EDIT1) );	
	m_FontColor = RGB(0, 0, 0);
	m_FontName = _T("新細明體");
	m_FontSize = 8;
	UpdateUI();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFontInputDialogMFCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFontInputDialogMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFontInputDialogMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	// 設定 Edit 控制項的文字顏色
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1){	
      pDC->SetTextColor( m_FontColor );            
	}
	return (HBRUSH) new CBrush(m_FontColor);
}

void CFontInputDialogMFCDlg::UpdateUI(){
	SetDlgItemInt(IDC_FONTSIZE, m_FontSize);		
	SetDlgItemText(IDC_FONTNAME, m_FontName);	
}

/**
 * 字型設定
 *
 *
 */
void CFontInputDialogMFCDlg::OnBnClickedButton1(){
	LOGFONT lf;
	CFont *pFont = m_edit->GetFont();
	pFont->GetLogFont(&lf);
	_tcscpy(lf.lfFaceName, m_FontName );
	
	CFontDialog dlg(&lf);
	dlg.m_cf.rgbColors = m_FontColor;   
	if (dlg.DoModal() == IDOK){
		m_FontColor = dlg.GetColor();//字型顏色		
		m_FontName	= dlg.GetFaceName();
		m_FontSize	= dlg.GetSize()/10;
		dlg.GetCurrentFont(&lf);
		
		UpdateUI();

		m_font.DeleteObject();
		m_font.CreateFontIndirect(&lf);
		m_edit->SetFont( &m_font );				

		TCHAR buf[255];
		int len = GetDlgItemText(IDC_EDIT1, buf, 255);	
		if (len > 0){
			TCHAR* result = new TCHAR[len+1];
			_tcsncpy(result, buf, len);
			result[len] = '\0';
			MessageBox(result);
		}
		
	}else{
		MessageBox(_T("N") );
	}

}
