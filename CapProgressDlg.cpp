// CapProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DSCam.h"
#include "CapProgressDlg.h"
#include "afxdialogex.h"


extern volatile BOOL g_syncflag;

// CCapProgressDlg dialog

IMPLEMENT_DYNAMIC(CCapProgressDlg, CDialogEx)

CCapProgressDlg::CCapProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCapProgressDlg::IDD, pParent)
{

}

CCapProgressDlg::~CCapProgressDlg()
{
}

void CCapProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCapProgressDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CCapProgressDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCapProgressDlg message handlers
BOOL CCapProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(IDLE_EVENT,400,NULL);

	return TRUE;
}


void CCapProgressDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if(g_syncflag)
		return;

	CDialogEx::OnClose();
}


void CCapProgressDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	
	g_syncflag=FALSE;

	CDialogEx::OnCancel();
}

void CCapProgressDlg::OnTimer(UINT_PTR nIDEvent)
{
	((CProgressCtrl *)GetDlgItem(IDC_PB_CAP_STATUS))->StepIt();
}
