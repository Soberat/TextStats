
// TextStatsDlg.h : header file
//

#pragma once


// CTextStatsDlg dialog
class CTextStatsDlg : public CDialogEx
{
// Construction
public:
	CTextStatsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEXTSTATS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedButtonBrowse();
	CEdit m_previewEdit;
	afx_msg void OnClickedButtonAnalyze();
	CEdit m_pathEdit;
	CEdit m_customPhraseEdit;
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnChangeEditExtensions();
	CEdit m_extensionsEdit;
	CStatic m_ExtensionsCorrectText;
	afx_msg void OnClickedCheckFilter();
	CButton m_checkboxFilter;
	CEdit m_editLog;
	CButton m_buttonAnalyze;
	afx_msg void OnClickedButtonExit();
};
