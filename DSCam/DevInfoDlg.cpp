// DevInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DSCam.h"
#include "DevInfoDlg.h"
#include "afxdialogex.h"


// CDevInfoDlg dialog

IMPLEMENT_DYNAMIC(CDevInfoDlg, CDialogEx)

CDevInfoDlg::CDevInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDevInfoDlg::IDD, pParent)
{
	
}

CDevInfoDlg::~CDevInfoDlg()
{
}

void CDevInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDevInfoDlg, CDialogEx)
END_MESSAGE_MAP()


// CDevInfoDlg message handlers
BOOL CDevInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	switch(theApp.m_CCD.m_runstatus)
	{
		case RUNMODE_PLAY:
			SetDlgItemText(IDC_LB_STATUS_CCD,_T("已连接"));
			break;
		case RUNMODE_PAUSE:
			SetDlgItemText(IDC_LB_STATUS_CCD,_T("暂停中"));
			break;
		case RUNMODE_STOP:
		default:
			SetDlgItemText(IDC_LB_STATUS_CCD,_T("未连接"));
			break;
	}

	//if(theApp.m_vsgui.isVsOpen())
	if(theApp.m_vsgui.m_isopen)
	{
		SetDlgItemText(IDC_LB_STATUS_VS,_T("已连接"));
		CString cstr(_T(""));
		cstr.Format(_T("%d"),theApp.m_vsgui.m_vsinfo.version);
		SetDlgItemText(IDC_LB_VS_VERSION,cstr.GetBuffer());
		cstr.Format(_T("%d"),theApp.m_vsgui.m_vsinfo.serNo);
		SetDlgItemText(IDC_LB_VS_SERNO,cstr.GetBuffer());
		cstr.Format(_T("%.2lf - %.2lf (nm)"),theApp.m_vsgui.m_vsinfo.minWl,theApp.m_vsgui.m_vsinfo.maxWl);
		SetDlgItemText(IDC_LB_VS_WAVERANGE,cstr.GetBuffer());
	}
	else
	{
		SetDlgItemText(IDC_LB_STATUS_VS,_T("未连接"));
		SetDlgItemText(IDC_LB_VS_VERSION,_T("----"));
		SetDlgItemText(IDC_LB_VS_SERNO,_T("----"));
		SetDlgItemText(IDC_LB_VS_WAVERANGE,_T("----"));
	}


	

	return TRUE;  // return TRUE  unless you set the focus to a control
}
