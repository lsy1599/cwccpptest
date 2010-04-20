// FontInputDialogMFCDlg.h : header file
//

#pragma once


// CFontInputDialogMFCDlg dialog
class CFontInputDialogMFCDlg : public CDialog
{
// Construction
public:
	CFontInputDialogMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FONTINPUTDIALOGMFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	void UpdateUI();

private:
	CEdit*		m_edit;
	CFont		m_font;  
	COLORREF	m_FontColor;
	CString		m_FontName;
	int			m_FontSize;
};
