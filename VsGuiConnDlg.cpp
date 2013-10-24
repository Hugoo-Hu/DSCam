// VsGuiConnDlg.cpp : implementation file
//

#include "stdafx.h"
#include "settings.h"
#include "DSCam.h"
#include "VsGuiConnDlg.h"
#include "afxdialogex.h"


// CVsGuiConnDlg dialog

IMPLEMENT_DYNAMIC(CVsGuiConnDlg, CDialogEx)

CVsGuiConnDlg::CVsGuiConnDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVsGuiConnDlg::IDD, pParent)
{

}

CVsGuiConnDlg::~CVsGuiConnDlg()
{
}

void CVsGuiConnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVsGuiConnDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_COMAUTODETECT, &CVsGuiConnDlg::OnBnClickedBnComautodetect)
END_MESSAGE_MAP()


// CVsGuiConnDlg message handlers
BOOL CVsGuiConnDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	vector<string> strports=getCommPort();
	for(int i=0;i!=strports.size();++i)
		((CComboBox *)GetDlgItem(IDC_CB_COM))->AddString(strports[i].c_str());
	if(theApp.m_vsgui.m_isopen)
		((CComboBox *)GetDlgItem(IDC_CB_COM))->SelectString(0,theApp.m_vsgui.m_comport.c_str());

	return TRUE;// return TRUE  unless you set the focus to a control
}

void CVsGuiConnDlg::OnOK()
{
	CString cstr(_T(""));
	GetDlgItemText(IDC_CB_COM,cstr);
	if(theApp.m_vsgui.m_isopen)
		goto end;

	//try
	//{
	//	theApp.m_vsgui.vsopen(cstr.GetBuffer());
	//}
	//catch(Cerr_vs_already_open)
	//{}
	//catch(Cerr_vs_no_character_echo)
	//{
	//	Sleep(100);
	//}
	//catch(...)
	//{
	//	MessageBox(_T("无法连接VariSpec设备"),_T("错误"),MB_ICONERROR);
	//	return;
	//}
	//MessageBox(_T("已连接VariSpec设备"),_T("成功"),MB_OK);
	//theApp.m_vsgui.get_filter_identity();
	int err=0;
	if(!VsOpen(&theApp.m_vsgui.m_vshwnd,cstr.GetBuffer(),&err))
	{
		cstr.Format(_T("无法连接VariSpec设备,error code: %d"),err);
		MessageBox(cstr.GetBuffer(),_T("错误"),MB_ICONERROR);
	}
	else
	{
		MessageBox(_T("连接VariSpec设备成功"),_T("成功"));
		theApp.m_vsgui.m_isopen=TRUE;
		theApp.m_vsgui.m_comport=cstr.GetBuffer();
		Csettings *settings=Csettings::getInstance();
		settings->set_vsport(theApp.m_vsgui.m_comport);
		VsClearPendingCommands(theApp.m_vsgui.m_vshwnd);
		VsGetFilterIdentity(theApp.m_vsgui.m_vshwnd,&theApp.m_vsgui.m_vsinfo.version,&theApp.m_vsgui.m_vsinfo.serNo, \
			&theApp.m_vsgui.m_vsinfo.minWl,&theApp.m_vsgui.m_vsinfo.maxWl);
	}

end:
	CDialogEx::OnOK();
}


void CVsGuiConnDlg::OnBnClickedBnComautodetect()
{
	// TODO: Add your control notification handler code here
	if(theApp.m_vsgui.m_isopen)
		return;
	Csettings *settings=Csettings::getInstance();
	vector<string> sysports=getCommPort();
	BOOL flag=FALSE;

	for(int i=0;i!=sysports.size();++i)
	{
		//try
		//{
		//	theApp.m_vsgui.vsopen(sysports[i]);
		//	settings->set_vsport(sysports[i]);
		//	flag=TRUE;
		//	break;
		//}
		//catch(Cerr_vs_already_open)
		//{
		//	settings->set_vsport(sysports[i]);
		//	theApp.m_vsgui.get_filter_identity();
		//	flag=TRUE;
		//	break;
		//}
		//catch(Cerr_vs_no_character_echo)
		//{
		//	Sleep(100);
		//	settings->set_vsport(sysports[i]);
		//	theApp.m_vsgui.get_filter_identity();
		//	flag=TRUE;
		//	break;
		//}
		//catch(...)
		//{
		//	flag=FALSE;
		//}
		int err=0;
		if(!VsOpen(&theApp.m_vsgui.m_vshwnd,sysports[i].c_str(),&err))
			continue;
		flag=TRUE;
		theApp.m_vsgui.m_isopen=TRUE;
		theApp.m_vsgui.m_comport=sysports[i];
		settings->set_vsport(sysports[i]);
		VsClearPendingCommands(theApp.m_vsgui.m_vshwnd);
		VsGetFilterIdentity(theApp.m_vsgui.m_vshwnd,&theApp.m_vsgui.m_vsinfo.version,&theApp.m_vsgui.m_vsinfo.serNo, \
			&theApp.m_vsgui.m_vsinfo.minWl,&theApp.m_vsgui.m_vsinfo.maxWl);
		break;
	}

	if(flag)
	{
		MessageBox(_T("已连接上设备"),_T("成功"),MB_OK);
	}
	else
		MessageBox(_T("无法连接设备"),_T("错误"),MB_OK|MB_ICONERROR);
}
