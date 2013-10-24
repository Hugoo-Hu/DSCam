
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#include "DSCam.h"
#include "settings.h"
#include "DevInfoDlg.h"
#include "VsGuiConnDlg.h"
#include "VsGuiSettingDlg.h"
#include "CamSettingDlg.h"
#include "CapProgressDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const UINT WM_CCDVIDEOMSG = ::RegisterWindowMessage(_T("CCDVideoMsg"));
volatile BOOL g_syncflag=FALSE;

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)

	ON_COMMAND(ID_DEV_OPEN_CCD,&CMainFrame::on_dev_open_ccd)
	ON_COMMAND(ID_DEV_OPEN_VS,&CMainFrame::on_dev_open_vs)
	ON_COMMAND(ID_DEV_OPEN_ALL,&CMainFrame::on_dev_open_all)
	ON_COMMAND(ID_DEV_CLOSE_CCD,&CMainFrame::on_dev_close_ccd)
	ON_COMMAND(ID_DEV_CLOSE_VS,&CMainFrame::on_dev_close_vs)
	ON_COMMAND(ID_DEV_CLOSE_ALL,&CMainFrame::on_dev_close_all)

	ON_COMMAND(ID_DEV_INFO,&CMainFrame::on_dev_info)
	ON_COMMAND(ID_DEV_SETTING_VS,&CMainFrame::on_dev_setting_vs)
	ON_COMMAND(ID_DEV_SETTING_CCD,&CMainFrame::on_dev_setting_ccd)

	ON_COMMAND(ID_VIDEO_PLAY,&CMainFrame::on_video_play)
	ON_COMMAND(ID_VIDEO_PAUSE,&CMainFrame::on_video_pause)
	ON_COMMAND(ID_VIDEO_CAP,&CMainFrame::on_video_cap)
	ON_COMMAND(ID_VIDEO_CAP_CONSECUTIVE,&CMainFrame::on_video_cap_consecutive)


	ON_REGISTERED_MESSAGE(WM_CCDVIDEOMSG,&CMainFrame::on_ccd_video_msg)


END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));

	// set the visual style to be used the by the visual manager
	//CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		//!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_CAM))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	//CString strCustomize;
	//bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	//ASSERT(bNameValid);
	//m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	//m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Enable toolbar and docking window menu replacement
	//EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	//CMFCToolBar::EnableQuickCustomization();

	//CString strIcon;
	//bNameValid = strIcon.LoadString(IDS_CAM_ICON);
	//ASSERT(bNameValid);
	//HICON hico=AfxGetApp()->LoadIcon(IDI_DSCAM);
	//SetIcon(hico,true);
	//SetIcon(hico,false);

	//TODO:

	Csettings *settings=Csettings::getInstance();

#ifdef XMLDOM
	settings->get_image_attr_dom(theApp.m_CCD.m_path2save,theApp.m_CCD.m_image_type);
	theApp.m_vsgui.m_wl_step=settings->get_wl_step_dom();
	//string str=settings->get_vsport_dom();
#else
	settings->get_image_attr(theApp.m_CCD.m_path2save,theApp.m_CCD.m_image_type);
	theApp.m_vsgui.m_wl_step=settings->get_wl_step();
#endif
	////theApp.m_CCD.m_path2save=settings->getpath2save();

	//string str;
	//switch(theApp.m_CCD.m_image_type)
	//{
	//	case FILE_JPG:
	//		str=_T("jpg");
	//		break;
	//	case FILE_BMP:
	//		str=_T("bmp");
	//		break;
	//	case FILE_RAW:
	//		str=_T("raw");
	//		break;
	//}
	//CString cstr;
	//cstr.Format(_T("m_path = %s,m_type = %s"),theApp.m_CCD.m_path2save.c_str(),str.c_str());
	//MessageBox(cstr.GetBuffer());

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	//cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
	//	 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnClose()
{
	//DS_RUNMODE ccd_status=theApp.m_CCD.m_runstatus;
	////if(ccd_status!=DS_RUNMODE::RUNMODE_STOP)
	////{
	//if(ccd_status==RUNMODE_PAUSE)
	//	CameraStop();
	//CameraUnInit();
	////}

	//if(theApp.m_vsgui.isVsOpen())
	//	theApp.m_vsgui.vsclose();
	on_dev_close_all();

	CFrameWndEx::OnClose();
}

vector<string> getCommPort()
{
         HKEY hkey;
         LPCTSTR path="HARDWARE\\DEVICEMAP\\SERIALCOMM\\";
         LONG ret=0;
         vector<string> ports;
         ret=::RegOpenKeyEx(HKEY_LOCAL_MACHINE,path,0,KEY_READ,&hkey);
         if(ret!=ERROR_SUCCESS) return ports;
         
         int i=0;
         TCHAR name[256];
         UCHAR szPortName[256];
         DWORD dwindex=0;
         DWORD dwname;
         DWORD dwsizeofPortName;
         DWORD type;

         do
         {
                   dwname=sizeof(name);
                   dwsizeofPortName=sizeof(szPortName);
                   ret=RegEnumValue(hkey,dwindex++,name,&dwname,NULL,&type,szPortName,&dwsizeofPortName);
                   if(ret==ERROR_SUCCESS)
                   {
                           TCHAR tchartmp[256];
                           memset(tchartmp,0,sizeof(tchartmp));
                           for(int j=0,k=0;j!=dwsizeofPortName;++j)
                           {
                                    if(szPortName[j]!='\0')
                                    {
                                             tchartmp[k]=szPortName[j];
                                             ++k;
                                    }
                           }
                           ports.push_back(string(tchartmp));
                           ++i;
                    }
                    else break;
          }
          while(1);
          RegCloseKey(hkey);
          sort(ports.begin(),ports.end());

          return ports;
}

/*==============================================================
函数:	SnapThreadCallback
功能:   定义提供给SDK使用的函数功能.
参数:   *pBuffer 当前帧图像数据指针. 数据类型BYTE,格式为RGB24, 长度为ImageWidth*ImageHeight*3

返回值: 
说明: 用户可以在此函数中编写自己的程序例如图像处理,控制等等

	例如下面代码在图像中画一条红线.

--------------------------------------------------------------*/

int CALLBACK SnapThreadCallback(BYTE *pBuffer)
{
#if 0
	int Width = 0;
	int Height= 0;
	if (STATUS_OK != CameraGetImageSize(&Width, &Height))
	{
		return FALSE;	
	}
	for (int i= 100; i<=101; i++)
	{
		for (int j=0; j<Width; j++)
		{
			*(pBuffer+(i*Width+j)*3+0) = 0x00;
			*(pBuffer+(i*Width+j)*3+1) = 0x00;
			*(pBuffer+(i*Width+j)*3+2) = 0xff;
		}
	}
#endif
	return TRUE;
}

UINT __cdecl video_cap_func(LPVOID arg)
{
	string filename;
	string strpath=theApp.m_CCD.m_path2save;
	//DS_FILE_TYPE imagetype=FILE_JPG;
	//Csettings *setting=Csettings::getInstance();
	//setting->get_image_attr(strpath,imagetype);
	if(strpath.rfind('\\')!=strpath.size()-1)
		strpath+="\\";
	CString cstr;

	//cstr.Format(_T("path = %s"),strpath.c_str());
	//MessageBox(theApp.m_pMainWnd->GetSafeHwnd(),cstr.GetBuffer(),_T("提示"),MB_OK);
	
	float wl_min_cap=(float)theApp.m_vsgui.m_wl_min_cap;
	float wl_max_cap=(float)theApp.m_vsgui.m_wl_max_cap;
	float wl_step=(float)theApp.m_vsgui.m_wl_step;
	//DS_FILE_TYPE image_type=theApp.m_CCD.m_image_type;

	for(int i=0;wl_min_cap+i*wl_step<=theApp.m_vsgui.m_wl_max_cap;++i)
	{
		if(!g_syncflag)
			break;
		VsSetWavelength(theApp.m_vsgui.m_vshwnd,wl_min_cap+i*wl_step,TRUE);
		//Sleep(200);
		//Sleep(theApp.m_CCD.m_exposuretime*10);
		Sleep(300);
		cstr.Format("%d",(int)(wl_min_cap+i*wl_step));
		filename=strpath+cstr.GetBuffer();
		CameraCaptureFile(filename.c_str(),theApp.m_CCD.m_image_type);
		//Sleep(theApp.m_CCD.m_exposuretime*100);
		//Sleep(200);
		Sleep(200);
	}

	//Sleep(1000);
	//MessageBox(theApp.m_pMainWnd->GetSafeHwnd(),_T("连拍结束"),_T("提示"),MB_OK);
	//cstr.Format(_T("path = %s"),strpath.c_str());
	//MessageBox(theApp.m_pMainWnd->GetSafeHwnd(),cstr.GetBuffer(),_T("提示"),MB_OK);
	g_syncflag=FALSE;
	Sleep(50);
	//HWND hwnd=FindWindow(_T("CCapPsrogressDlg"),_T("连拍中"));
	//HWND hwnd=FindWindow(_T("CCapProgressDlg"),NULL);
	HWND hwnd=FindWindow(NULL,_T("连拍中"));

	//cstr.Format(_T("hwnd = %d"),hwnd);
	//MessageBox(theApp.m_pMainWnd->GetSafeHwnd(),cstr.GetBuffer(),_T("提示"),MB_OK);
	if(hwnd!=NULL)
		SendMessage(hwnd,WM_CLOSE,NULL,NULL);

	return 0;
}

void CMainFrame::on_dev_open_ccd()
{
	BOOL isccdinit=theApp.m_CCD.m_isinit;
	DS_RUNMODE ccd_status=theApp.m_CCD.m_runstatus;
	DS_CAMERA_STATUS ds_err=STATUS_OK;

	//if(ccd_status==RUNMODE_STOP)
	if(!isccdinit)
	{
		if ( STATUS_OK != (ds_err=CameraInit(SnapThreadCallback, theApp.m_CCD.m_resolution, 
			((CMainFrame*)AfxGetMainWnd())->GetActiveView()->m_hWnd, this->m_hWnd)))
		{
			string strret("Init Camera failed!\tError: ");

			switch(ds_err)
			{
				case STATUS_NO_DEVICE_FIND:
					strret+="No device found.";
					break;
				case STATUS_NOT_ENOUGH_SYSTEM_MEMORY:
					strret+="Not enough memory.";
					break;
				case STATUS_PARAMETER_INVALID:
					strret+="Invalid parameter.";
					break;
				default:
					strret+="Other error.";
					break;
			}
			
			MessageBox(strret.c_str(), "Error", MB_OK | MB_ICONSTOP);
			return;
			
		}

		//theApp.m_CCD.m_runstatus=RUNMODE_PLAY;
		theApp.m_CCD.m_isinit=TRUE;
		CameraPlay();
		CameraSetLongExpPower(FALSE);
		theApp.m_CCD.m_runstatus=RUNMODE_PLAY;
		CameraSetVideoMessage(WM_CCDVIDEOMSG);
		CameraDisplayEnable(TRUE);
	}
}

void CMainFrame::on_dev_open_vs()
{
	//if(theApp.m_vsgui.isVsOpen())
	//	return;

	//Csettings *settings=Csettings::getInstance();
	//string strport=settings->get_vsport();
	//try
	//{
	//	theApp.m_vsgui.vsopen(strport);
	//	
	//	theApp.m_vsgui.get_filter_identity();
	//}
	//catch(Cerr_vs_communication)
	//{
	//	vector<string> sysports=getCommPort();
	//	for(int i=0;i!=sysports.size();++i)
	//	{
	//		try
	//		{
	//			if(sysports[i]==strport)
	//				continue;
	//			theApp.m_vsgui.vsopen(sysports[i]);
	//			settings->set_vsport(sysports[i]);
	//			break;
	//		}
	//		catch(Cerr_vs_already_open)
	//		{
	//			settings->set_vsport(sysports[i]);
	//			theApp.m_vsgui.get_filter_identity();
	//			break;
	//		}
	//		catch(Cerr_vs_no_character_echo)
	//		{
	//			//initializing
	//			Sleep(100);
	//			settings->set_vsport(sysports[i]);
	//			theApp.m_vsgui.get_filter_identity();
	//			break;
	//		}
	//		catch(...)
	//		{}
	//	}
	//}
	//catch(Cerr_vs_interface_not_available)
	//{
	//	vector<string> sysports=getCommPort();
	//	for(int i=0;i!=sysports.size();++i)
	//	{
	//		try
	//		{
	//			if(sysports[i]==strport)
	//				continue;
	//			theApp.m_vsgui.vsopen(sysports[i]);
	//			settings->set_vsport(sysports[i]);

	//			break;
	//		}
	//		catch(Cerr_vs_already_open)
	//		{
	//			settings->set_vsport(sysports[i]);
	//			theApp.m_vsgui.get_filter_identity();
	//			break;
	//		}
	//		catch(...)
	//		{}
	//	}
	//}
	//catch(Cerr_vs_no_dev_present)
	//{
	//	vector<string> sysports=getCommPort();
	//	for(int i=0;i!=sysports.size();++i)
	//	{
	//		try
	//		{
	//			if(sysports[i]==strport)
	//				continue;
	//			theApp.m_vsgui.vsopen(sysports[i]);
	//			settings->set_vsport(sysports[i]);
	//			break;
	//		}
	//		catch(Cerr_vs_already_open)
	//		{
	//			settings->set_vsport(sysports[i]);
	//			theApp.m_vsgui.get_filter_identity();
	//			break;
	//		}
	//		catch(...)
	//		{}
	//	}
	//}
	//catch(Cerr_vs_no_character_echo)
	//{
	//	//initializing
	//	Sleep(100);
	//	theApp.m_vsgui.get_filter_identity();
	//}
	//catch(Cerr_vs_already_open)
	//{
	//	theApp.m_vsgui.get_filter_identity();
	//}
	//catch(...)
	//{
	//	
	//}
	
	if(theApp.m_vsgui.m_isopen)
		return;
	Csettings *setting=Csettings::getInstance();
	string strport(_T(""));
#ifdef XMLDOM
	strport=setting->get_vsport_dom();
#else
	strport=setting->get_vsport();
#endif
	int err=0;
	map<string,int> errmap;
	strport=_T("COM4");
	if(!VsOpen(&theApp.m_vsgui.m_vshwnd,strport.c_str(),&err))
	{
		errmap[strport]=err;
		theApp.m_vsgui.m_vshwnd=NULL;
		vector<string> ports=getCommPort();
		BOOL issuccess=FALSE;
		for(int i=0;i!=ports.size();++i)
		{
			if(strport==ports[i])
				continue;
			if(!VsOpen(&theApp.m_vsgui.m_vshwnd,strport.c_str(),&err))
			{
				errmap[ports[i]]=err;
				continue;
			}
			theApp.m_vsgui.m_isopen=TRUE;
			theApp.m_vsgui.m_comport=ports[i];
			setting->set_vsport(ports[i]);
			issuccess=TRUE;
			break;
		}
		if(!issuccess)
		{
			CString cstr;
			string strerr;
			strerr=_T("Can't connect VariSpec.\nError codes:\n");
			for(map<string,int>::iterator iter=errmap.begin();iter!=errmap.end();++iter)
			{
				cstr.Format(_T("%s,%d\n"),iter->first.c_str(),iter->second);
				strerr+=cstr.GetBuffer();
			}
			MessageBox(strerr.c_str(),_T("错误"),MB_OK|MB_ICONERROR);
		}
	}
	else
	{
		theApp.m_vsgui.m_isopen=TRUE;
		theApp.m_vsgui.m_comport=strport;
	}

	if(theApp.m_vsgui.m_isopen)
	{
		BOOL status=VsClearPendingCommands(theApp.m_vsgui.m_vshwnd);

		status=VsGetFilterIdentity(theApp.m_vsgui.m_vshwnd,&theApp.m_vsgui.m_vsinfo.version,&theApp.m_vsgui.m_vsinfo.serNo, \
			&theApp.m_vsgui.m_vsinfo.minWl,&theApp.m_vsgui.m_vsinfo.maxWl);
		status=VsGetWavelength(theApp.m_vsgui.m_vshwnd,&theApp.m_vsgui.m_wl_curr);
		//status=VsGetWavelengthStep(theApp.m_vsgui.m_vshwnd,&theApp.m_vsgui.m_wl_step);
		//theApp.m_vsgui.m_wl_step=0.0f;

		theApp.m_vsgui.m_wl_max_cap=theApp.m_vsgui.m_vsinfo.maxWl;
		theApp.m_vsgui.m_wl_min_cap=theApp.m_vsgui.m_vsinfo.minWl;
	}
}

void CMainFrame::on_dev_open_all()
{
	on_dev_open_ccd();
	on_dev_open_vs();
}

void CMainFrame::on_dev_close_ccd()
{
	if(!theApp.m_CCD.m_isinit)
		return;
	DS_RUNMODE ccd_status=theApp.m_CCD.m_runstatus;

	//if(ccd_status==RUNMODE_PAUSE)
	CameraStop();
	CameraUnInit();
	theApp.m_CCD.m_isinit=FALSE;
	theApp.m_CCD.m_runstatus=RUNMODE_STOP;
}

void CMainFrame::on_dev_close_vs()
{
	//if(theApp.m_vsgui.isVsOpen())
	//{
	//	theApp.m_vsgui.vsclose();
	//}
	if(theApp.m_vsgui.m_isopen)
	{
		if(VsClose(theApp.m_vsgui.m_vshwnd))
			theApp.m_vsgui.m_isopen=FALSE;
	}
}

void CMainFrame::on_dev_close_all()
{
	on_dev_close_ccd();
	on_dev_close_vs();
}

void CMainFrame::on_dev_info()
{
	CDevInfoDlg infodlg;
	infodlg.DoModal();
}

void CMainFrame::on_dev_setting_vs()
{
	//if(theApp.m_vsgui.isVsOpen())
	if(theApp.m_vsgui.m_isopen)
	{
		CVsGuiSettingDlg vs_setting_dlg;
		vs_setting_dlg.DoModal();
	}
	else
		MessageBox(_T("VariSpec设备未连接"),_T("错误"),MB_ICONERROR);
}

void CMainFrame::on_dev_setting_ccd()
{
	//if(theApp.m_CCD.m_runstatus!=RUNMODE_STOP)
	if(theApp.m_CCD.m_isinit)
	{
		CCamSettingDlg ccd_setting_dlg;
		ccd_setting_dlg.DoModal();
	}
	else
	{
		MessageBox(_T("CCD未初始化"),_T("错误"),MB_ICONERROR);
	}
}

void CMainFrame::on_video_play()
{
	//if(theApp.m_CCD.m_runstatus==RUNMODE_STOP)
	if(!theApp.m_CCD.m_isinit)
	{
		MessageBox(_T("CCD设备未初始化."),_T("错误"),MB_ICONSTOP);
		return;
	}
	if(theApp.m_CCD.m_runstatus==RUNMODE_PLAY)
		return;
	
	CameraPlay();
	CameraSetLongExpPower(FALSE);
	theApp.m_CCD.m_runstatus=RUNMODE_PLAY;
	CameraSetVideoMessage(WM_CCDVIDEOMSG);
	CameraDisplayEnable(TRUE);
}

void CMainFrame::on_video_pause()
{
	if(!theApp.m_CCD.m_isinit)
	{
		MessageBox(_T("CCD设备未初始化."),_T("错误"),MB_ICONSTOP);
		return;
	}
	if(theApp.m_CCD.m_runstatus==RUNMODE_PLAY)
	{
		CameraPause();
		theApp.m_CCD.m_runstatus=RUNMODE_PAUSE;
	}
}

void CMainFrame::on_video_cap()
{
	if(theApp.m_CCD.m_isinit&&theApp.m_CCD.m_runstatus!=RUNMODE_STOP)
	{
		if(theApp.m_CCD.m_path2save==_T(""))
		{
			MessageBox(_T("保存路径为空,请选择一个文件夹保存图片"),_T("错误"),MB_ICONERROR);
			return;
		}
		string filename;
		string strpath=theApp.m_CCD.m_path2save;
		DS_FILE_TYPE imagetype=FILE_JPG;
		//Csettings *setting=Csettings::getInstance();
		//setting->get_image_attr(strpath,imagetype);

		if(strpath.rfind('\\')!=strpath.size()-1)
			strpath+="\\";
		CString cstr;
		cstr.Format("%d",(int)theApp.m_vsgui.m_wl_curr);
		filename=strpath+"image_"+cstr.GetBuffer();
		
		DS_CAMERA_STATUS err=STATUS_OK;
		if((err=CameraCaptureFile(filename.c_str(),theApp.m_CCD.m_image_type))!=STATUS_OK)
		{
			//cstr.Format(_T("error code = %d"),err);
			//MessageBox(cstr.GetBuffer());
		}
		//cstr.Format("err=%d",err);
		//MessageBox(cstr.GetBuffer());

	}
}

long CMainFrame::on_ccd_video_msg(WPARAM wP, LPARAM lP)
{
	++theApp.m_CCD.m_videocnt;

	return 0;
}

void CMainFrame::on_video_cap_consecutive()
{
	if(theApp.m_CCD.m_isinit&&theApp.m_CCD.m_runstatus!=RUNMODE_STOP&&theApp.m_vsgui.m_isopen)
	{
		if(theApp.m_CCD.m_path2save==_T(""))
		{
			MessageBox(_T("保存路径为空,请选择一个文件夹保存图片"),_T("错误"),MB_ICONERROR);
			return;
		}
		if(theApp.m_vsgui.m_wl_step==0.0f)
		{
			MessageBox(_T("步长为0,请设置"),_T("错误"),MB_ICONERROR);
			return;
		}
		g_syncflag=TRUE;
		AfxBeginThread(video_cap_func,NULL);
		CCapProgressDlg capprogdlg;
		capprogdlg.DoModal();
	}
}

