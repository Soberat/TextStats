// TextStatsDlg.cpp : implementation file
// Author: Miros³aw Wi¹cek
//		   Elektronika i Telekomunikacja, 305237

#include "pch.h"
#include "framework.h"
#include "TextStats.h"
#include "TextStatsDlg.h"
#include "afxdialogex.h"
#include "Utils.h"
#include "TextInfo.h"
#include <filesystem>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTextStatsDlg dialog



CTextStatsDlg::CTextStatsDlg(CWnd* pParent /*=nullptr*/) : CDialogEx(IDD_TEXTSTATS_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTextStatsDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PREVIEW, m_editPreview);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Control(pDX, IDC_EDIT_EXTENSIONS, m_editExtensions);
	DDX_Control(pDX, IDC_STATIC_EXTENSIONS, m_textExtensionsCorrect);
	DDX_Control(pDX, IDC_CHECK_FILTER, m_checkboxFilter);
	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
	DDX_Control(pDX, ID_BUTTON_ANALYZE, m_buttonAnalyze);
	DDX_Control(pDX, IDC_EDIT_LINES, m_editLines);
	DDX_Control(pDX, IDC_EDIT_WORDS, m_editWords);
	DDX_Control(pDX, IDC_EDIT_CHARS, m_editChars);
}

BEGIN_MESSAGE_MAP(CTextStatsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CTextStatsDlg::OnClickedButtonBrowse)
	ON_BN_CLICKED(ID_BUTTON_ANALYZE, &CTextStatsDlg::OnClickedButtonAnalyze)
	ON_EN_CHANGE(IDC_EDIT_EXTENSIONS, &CTextStatsDlg::OnChangeEditExtensions)
	ON_BN_CLICKED(IDC_CHECK_FILTER, &CTextStatsDlg::OnClickedCheckFilter)
	ON_BN_CLICKED(ID_BUTTON_EXIT, &CTextStatsDlg::OnClickedButtonExit)
END_MESSAGE_MAP()


// CTextStatsDlg message handlers

BOOL CTextStatsDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	//Put example text in Extensions box to showcase how to use it
	CString initialExtensions{ ".jpg, .txt" };
	m_editExtensions.SetWindowTextW(initialExtensions);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTextStatsDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTextStatsDlg::OnPaint() {
	if (IsIconic()) {
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
	} else {
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTextStatsDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}


//End of automatically generated MFC code


/*
*	This function opens a Windows folder selection dialog. If the user chose a folder, the UI is updated with the new file path and file list.
*/
void CTextStatsDlg::OnClickedButtonBrowse() {
	CFolderPickerDialog dlg(NULL, 0, this);
	if (dlg.DoModal() == IDOK) {
		CString sFilePath = dlg.GetPathName();
		m_editPath.SetWindowTextW(sFilePath);

		std::vector<CString> files = Utils().listFiles(sFilePath);

		//Once a path is successfully chosen we can safely allow the user to use the Analyze function
		m_buttonAnalyze.EnableWindow(true);

		//Refresh the file list
		OnClickedCheckFilter();
	}
}

/*
*	Handler for the main function of the program, which is counting the lines, words and characters in given list of files.
*/
void CTextStatsDlg::OnClickedButtonAnalyze() {
	TextInfo ti {};
	bool filter = m_checkboxFilter.GetCheck();
	CString strPath, strCustomPhrase, linesText, wordsText, charsText, phraseText;

	CString extensions;
	std::vector<CString> splitExtensions {};

	//Get the current file path and list of files in it
	m_editPath.GetWindowTextW(strPath);
	std::vector<CString> fileList = Utils().listFiles(strPath);

	//Fetch extensions to be filtered
	if (filter) {
		m_editExtensions.GetWindowTextW(extensions);
		splitExtensions = Utils().split(extensions, _T(","));
		Utils().filterExtensions(fileList, splitExtensions);
	}

	//For each file in list open the file as an ifstream and read it line-by-line. The gathered data will be saved to an instance of TextInfo class. 
	for (auto file : fileList) {
		std::ifstream current;

		int status = Utils().openFile(file, current);

		if (status == -1) {
			//If the open function failed log it
			int nLen = m_editLog.GetWindowTextLengthW();
			m_editLog.SetFocus();
			m_editLog.SetSel(nLen, nLen);
			m_editLog.ReplaceSel(CString(_T("Error reading file: ") + file + _T("\r\n")));
		} else {
			ti.analyze(current);
			current.close();
		}
	}
	
	//Format and display numbers for the analyzed files
	linesText.Format(_T("%d"), ti.getLines());
	wordsText.Format(_T("%d"), ti.getWords());
	charsText.Format(_T("%d"), ti.getChars());

	m_editLines.SetWindowTextW(linesText);
	m_editWords.SetWindowTextW(wordsText);
	m_editChars.SetWindowTextW(charsText);
}


/*
*	This is the OnChange handler for the Extensions edit. Since our function Utils::split() is safe we can call this handler reglardless of whether the user has finished typing or not.
*/
void CTextStatsDlg::OnChangeEditExtensions() {
	CString extensions {};
	std::vector<CString> splitExtensions {};

	m_editExtensions.GetWindowTextW(extensions);
	splitExtensions = Utils().split(extensions, _T(","));

	CString str {};

	//Display the filtered extensions
	for (auto ext : splitExtensions) {
		str += (ext + _T(" "));
	}
	m_textExtensionsCorrect.SetWindowTextW(str);
	

	//We also call the OnClicked check handler, so the file list is updated immediately.
	OnClickedCheckFilter();
}

/*
*	Function handling the "Filter by extension" checkbox. 
*/
void CTextStatsDlg::OnClickedCheckFilter() {
	int checkboxFilter = m_checkboxFilter.GetCheck();

	CString strPath {}, extensionsText {};
	std::vector<CString> extensions {};

	//Fetch file path and extensions
	m_editPath.GetWindowTextW(strPath);
	m_editExtensions.GetWindowTextW(extensionsText);
	extensions = Utils().split(extensionsText, _T(","));

	//If the path is empty, we cannot show any files, therefore we display an error
	if (strPath.IsEmpty()) {
		m_editPreview.SetWindowTextW(CString("No file path given!"));
		return;
	}

	std::vector<CString> files = Utils().listFiles(strPath);
	CString s {};

	//We filter the files aquired above using listFiles based on the checkbox state
	if (checkboxFilter == BST_CHECKED) {
		Utils().filterExtensions(files, extensions);
	} 

	//For display purposes we append a carriage return and a newline to the list of files
	for (CString str : files) {
		s += (str + _T("\r\n"));
	}

	//We also replace the base path with nothing, since it is redundant
	s.Replace(strPath + "\\", _T(""));

	if (s.IsEmpty()) s = CString("No files found");
	m_editPreview.SetWindowTextW(s);

}


/*
* Exit with code 0 on user prompt.
*/
void CTextStatsDlg::OnClickedButtonExit() {
	exit(0);
}
