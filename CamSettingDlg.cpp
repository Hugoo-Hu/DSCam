// CamSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "settings.h"
#include "DSCam.h"
#include "CamSettingDlg.h"
#include "afxdialogex.h"


// CCamSettingDlg dialog

IMPLEMENT_DYNAMIC(CCamSettingDlg, CDialogEx)

CCamSettingDlg::CCamSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCamSettingDlg::IDD, pParent)
{

}

CCamSettingDlg::~CCamSettingDlg()
{
}

void CCamSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCamSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_PATH_SEARCH, &CCamSettingDlg::OnBnClickedBnPathSearch)
	ON_NOTIFY_RANGE(NM_CUSTOMDRAW,IDC_SD_CCD_RGAIN,IDC_SD_CCD_BGAIN,oncustomdraw_color_rgb)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_GAMMA,oncustomdraw_color_gamma)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_CONTRAST,oncustomdraw_color_contrast)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_SATURATION,oncustomdraw_color_saturation)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_AETARGET,oncustomdraw_aetarget)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_EXPOSUREGAIN,oncustomdraw_exposuregain)
	ON_NOTIFY(NM_CUSTOMDRAW,IDC_SD_CCD_EXPOSURETIME,oncustomdraw_exposuretime)
	ON_BN_CLICKED(IDC_CHB_CCD_COLORENHANCE, &CCamSettingDlg::OnBnClickedChbCcdColorenhance)
	ON_BN_CLICKED(IDC_BN_CCD_AWBONE, &CCamSettingDlg::OnBnClickedBnCcdAwbone)
	ON_BN_CLICKED(IDC_CHB_CCD_AE, &CCamSettingDlg::OnBnClickedChbCcdAe)
	ON_BN_CLICKED(IDC_BN_CCD_RESTARTEXPOSURE, &CCamSettingDlg::OnBnClickedBnCcdRestartexposure)
	ON_BN_CLICKED(IDC_RB_CCD_IMAGE_JPG, &CCamSettingDlg::OnBnClickedRbCcdImageJpg)
	ON_BN_CLICKED(IDC_RB_CCD_IMAGE_BMP, &CCamSettingDlg::OnBnClickedRbCcdImageBmp)
	ON_BN_CLICKED(IDC_RB_CCD_IMAGE_RAW, &CCamSettingDlg::OnBnClickedRbCcdImageRaw)
	ON_BN_CLICKED(IDC_RB_CCD_LINE, &CCamSettingDlg::OnBnClickedRbCcdLine)
	ON_BN_CLICKED(IDC_RB_CCD_HAMILTON, &CCamSettingDlg::OnBnClickedRbCcdHamilton)
	ON_BN_CLICKED(IDC_RB_CCD_LAROCHE, &CCamSettingDlg::OnBnClickedRbCcdLaroche)
	ON_BN_CLICKED(IDC_RB_CCD_DW_8, &CCamSettingDlg::OnBnClickedRbCcdDw8)
	ON_BN_CLICKED(IDC_RB_CCD_DW_16, &CCamSettingDlg::OnBnClickedRbCcdDw16)
	ON_BN_CLICKED(IDC_RB_CCD_IDATA_SEL_HIGH, &CCamSettingDlg::OnBnClickedRbCcdIdataSelHigh)
	ON_BN_CLICKED(IDC_RB_CCD_IDATA_SEL_MID, &CCamSettingDlg::OnBnClickedRbCcdIdataSelMid)
	ON_BN_CLICKED(IDC_RB_CCD_IDATA_SEL_LOW, &CCamSettingDlg::OnBnClickedRbCcdIdataSelLow)
	ON_CBN_SELCHANGE(IDC_CB_CCD_FRAMESPEED, &CCamSettingDlg::OnCbnSelchangeCbCcdFramespeed)
	ON_BN_CLICKED(IDC_RB_CCD_PARAM_A, &CCamSettingDlg::OnBnClickedRbCcdParamA)
	ON_BN_CLICKED(IDC_RB_CCD_PARAM_B, &CCamSettingDlg::OnBnClickedRbCcdParamB)
	ON_BN_CLICKED(IDC_RB_CCD_PARAM_C, &CCamSettingDlg::OnBnClickedRbCcdParamC)
	ON_BN_CLICKED(IDC_RB_CCD_PARAM_D, &CCamSettingDlg::OnBnClickedRbCcdParamD)
	ON_BN_CLICKED(IDC_BN_CCD_PARAM_SAVE, &CCamSettingDlg::OnBnClickedBnCcdParamSave)
END_MESSAGE_MAP()


// CCamSettingDlg message handlers
BOOL CCamSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_ED_PATH2SAVE,theApp.m_CCD.m_path2save.c_str());
	
	//Gamma range (0.20 - 1.50)
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GAMMA))->SetRange(20,150);
	//contrast range (0 - 255)
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_CONTRAST))->SetRange(0,255);
	//AETARGET range
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_AETARGET))->SetRange(40,180);
	//Exposure Time range
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSURETIME))->SetRange(1,1068*10);
	
	//RGAIN
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_RGAIN))->SetRange(0,255);
	//GGAIN
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GGAIN))->SetRange(0,255);
	//BGAIN
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_BGAIN))->SetRange(0,255);
	//Saturation
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_SATURATION))->SetRange(0,255);
	//exposure gain
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSUREGAIN))->SetRange(1,0x3ff);

	//
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->AddString(_T("12.5fps"));
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->AddString(_T("6.25fps"));
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->AddString(_T("3.13fps"));
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->AddString(_T("1.56fps"));
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->AddString(_T("0.78fps"));

	BYTE tmp;
	CameraGetCurrentParameterTeam(&tmp);
	m_param_team=(DS_PARAMETER_TEAM)tmp;
	theApp.m_CCD.m_param_team=m_param_team;
	switch (tmp)
	{
		case PARAMETER_TEAM_A:
			CheckDlgButton(IDC_RB_CCD_PARAM_A, BST_CHECKED);
			break;
		case PARAMETER_TEAM_B:
			CheckDlgButton(IDC_RB_CCD_PARAM_B, BST_CHECKED);
			break;
		case PARAMETER_TEAM_C:
			CheckDlgButton(IDC_RB_CCD_PARAM_C, BST_CHECKED);
			break;
		case PARAMETER_TEAM_D:
			CheckDlgButton(IDC_RB_CCD_PARAM_D, BST_CHECKED);
			break;
		default:
			tmp = PARAMETER_TEAM_A;
			CheckDlgButton(IDC_RB_CCD_PARAM_A, BST_CHECKED);
			break;
	}

	updateDlg();
	
	Csettings *settings=Csettings::getInstance();

#ifdef XMLDOM
	settings->get_image_attr_dom(m_path2save,m_image_type);
#else
	settings->get_image_attr(m_path2save,m_image_type);
#endif
	
	SetDlgItemText(IDC_ED_PATH2SAVE,m_path2save.c_str());
	switch(m_image_type)
	{
		case FILE_JPG:
			CheckDlgButton(IDC_RB_CCD_IMAGE_JPG,BST_CHECKED);
				break;
		case FILE_BMP:
			CheckDlgButton(IDC_RB_CCD_IMAGE_BMP,BST_CHECKED);
			break;
		case FILE_RAW:
			CheckDlgButton(IDC_RB_CCD_IMAGE_RAW,BST_CHECKED);
			break;
		default:
			CheckDlgButton(IDC_RB_CCD_IMAGE_JPG,BST_CHECKED);
			break;
	}

	return TRUE;// return TRUE  unless you set the focus to a control
}

void CCamSettingDlg::updateDlg()
{
	BYTE tmp=0;
	BOOL btmp;
	CString cstr;
	BYTE contrast = 0;
	USHORT usAnalogGain = 0;
	BYTE uiNoisePiexlOffset = 50;
	int rgain =64;
	int ggain =64;
	int bgain =64;
	BYTE saturation = 128;
	int itmp=0;
	//UINT rowtime=0;
	CameraGetExposureTime(&itmp);
	m_exposuretime=itmp;
	theApp.m_CCD.m_exposuretime=m_exposuretime;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSURETIME))->SetPos(itmp);
	//CameraGetRowTime(&rowtime);
	//cstr.Format(_T("%dF %dL %.2fS"),itmp/1068,itmp%1068,(float)itmp*rowtime/1000000);
	//SetDlgItemText(IDC_LB_CCD_EXPOSURETIME,cstr.GetBuffer());
	UpdateExposureTimeText();

	CameraGetAeState(&btmp);
	m_aestate=btmp;
	theApp.m_CCD.m_aestate=m_aestate;
	CheckDlgButton(IDC_CHB_CCD_AE,btmp);
	GetDlgItem(IDC_SD_CCD_EXPOSUREGAIN)->EnableWindow(!btmp);
	GetDlgItem(IDC_SD_CCD_EXPOSURETIME)->EnableWindow(!btmp);

	CameraGetAeTarget(&tmp);
	m_aetarget=tmp;
	theApp.m_CCD.m_aetarget=m_aetarget;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_AETARGET))->SetPos(tmp);
	GetDlgItem(IDC_SD_CCD_AETARGET)->EnableWindow(!btmp);
	cstr.Format(_T("%d"),tmp);
	SetDlgItemText(IDC_LB_CCD_AETARGET,cstr.GetBuffer());

	CameraGetGamma(&tmp);
	m_gamma=tmp;
	theApp.m_CCD.m_gamma=m_gamma;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GAMMA))->SetPos(tmp);

	CameraGetAnalogGain( &usAnalogGain );
	m_analoggain=usAnalogGain;
	theApp.m_CCD.m_analoggain=m_analoggain;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSUREGAIN))->SetPos(usAnalogGain);
	//float fgain=6+0.035f*usAnalogGain;
	//cstr.Format(_T("%.3fdb"),fgain);
	//SetDlgItemText(IDC_LB_CCD_EXPOSUREGAIN,cstr.GetBuffer());
	UpdateExposureGainText();

	CameraGetColorEnhancement(&btmp);
	m_color_enhance=btmp;
	theApp.m_CCD.m_color_enhance=m_color_enhance;
	CheckDlgButton(IDC_CHB_CCD_COLORENHANCE,btmp);

	CameraGetContrast(&contrast);
	m_contrast=contrast;
	theApp.m_CCD.m_contrast=m_contrast;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_CONTRAST))->SetPos(contrast);
	cstr.Format(_T("%d"),contrast);
	SetDlgItemText(IDC_LB_CCD_CONTRAST,cstr.GetBuffer());

	CameraGetGain(&rgain, &ggain, &bgain);
	m_rgain=rgain;
	m_ggain=ggain;
	m_bgain=bgain;
	theApp.m_CCD.m_rgain=m_rgain;
	theApp.m_CCD.m_ggain=m_ggain;
	theApp.m_CCD.m_bgain=m_bgain;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_RGAIN))->SetPos(rgain);
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GGAIN))->SetPos(ggain);
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_BGAIN))->SetPos(bgain);

	CameraGetSaturation(&saturation);
	m_saturation=saturation;
	theApp.m_CCD.m_saturation=m_saturation;
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_SATURATION))->SetPos(saturation);

	CameraGetFrameSpeed(&tmp);
	((CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED))->SetCurSel(tmp);
	m_frame_speed=(DS_FRAME_SPEED)tmp;
	theApp.m_CCD.m_frame_speed=m_frame_speed;
	if(m_frame_speed==FRAME_SPEED_NORMAL)
	{
		GetDlgItem(IDC_RB_CCD_DW_16)->EnableWindow(FALSE);
	}

	CameraGetDataWide(&btmp);
	m_data_wide=btmp;
	theApp.m_CCD.m_data_wide=m_data_wide;
	CheckDlgButton(IDC_RB_CCD_DW_8,!btmp?BST_CHECKED:BST_UNCHECKED);
	CheckDlgButton(IDC_RB_CCD_DW_16,btmp?BST_CHECKED:BST_UNCHECKED);

	CameraGetB2RGBMode(&tmp);
	m_b2rgb_mode=(DS_B2RGB_MODE)tmp;
	theApp.m_CCD.m_b2rgb_mode=m_b2rgb_mode;
	switch (tmp)
	{
		case B2RGB_MODE_LAROCHE:
			CheckDlgButton(IDC_RB_CCD_LAROCHE, 1);	
			break;
		case B2RGB_MODE_HAMILTON:
			CheckDlgButton(IDC_RB_CCD_HAMILTON, 1);	
			break;
		case B2RGB_MODE_LINE:
			CheckDlgButton(IDC_RB_CCD_LINE, 1);	
			break;
		default:
			break;
	}

	
}


void CCamSettingDlg::OnBnClickedBnPathSearch()
{
	// TODO: Add your control notification handler code here
	BROWSEINFO bi={0};
	bi.pidlRoot=NULL;
	bi.hwndOwner=this->GetSafeHwnd();
	bi.lpszTitle=_T("请选择保存图片的文件夹.");
	bi.ulFlags=BIF_RETURNFSANCESTORS;

	LPITEMIDLIST lpidlist=SHBrowseForFolder(&bi);
	if(lpidlist==NULL)
		return;

	TCHAR pathtmp[MAX_PATH];
	memset(pathtmp,0,MAX_PATH);

	if(!SHGetPathFromIDList(lpidlist,pathtmp))
		return;

	SetDlgItemText(IDC_ED_PATH2SAVE,pathtmp);
	string strpath(pathtmp);
	if(strpath!=theApp.m_CCD.m_path2save||m_image_type!=theApp.m_CCD.m_image_type)
	{
		theApp.m_CCD.m_path2save=strpath;
		Csettings *settings=Csettings::getInstance();
		//settings->setpath2save(strpath);

		//
#ifdef XMLDOM
		settings->set_image_attr_dom(m_path2save,m_image_type);
#else
		settings->set_image_attr(m_path2save,m_image_type);
#endif

		//string path,strtype;
		//DS_FILE_TYPE type;
		//settings->get_image_attr(path,type);
		//switch(type)
		//{
		//	case FILE_JPG:
		//		strtype=_T("jpg");
		//		break;
		//	case FILE_BMP:
		//		strtype=_T("bmp");
		//		break;
		//	case FILE_RAW:
		//		strtype=_T("raw");
		//		break;
		//}

		//CString cstr;
		//cstr.Format(_T("after set: path = %s,type = %s"),path.c_str(),strtype.c_str());
		//MessageBox(cstr.GetBuffer());
	}

}

void CCamSettingDlg::OnOK()
{
	//if(theApp.m_CCD.m_rgain!=m_rgain||theApp.m_CCD.m_ggain!=m_ggain||theApp.m_CCD.m_bgain!=m_bgain)
	//{
	//	CameraSetGain(m_rgain,m_ggain,m_bgain);
	//	theApp.m_CCD.m_rgain=m_rgain;
	//	theApp.m_CCD.m_ggain=m_ggain;
	//	theApp.m_CCD.m_bgain=m_bgain;
	//}
	//if(theApp.m_CCD.m_gamma!=m_gamma)
	//{
	//	}

	return CDialogEx::OnOK();
}

void CCamSettingDlg::oncustomdraw_color_rgb(UINT id,NMHDR* pNMHDR, LRESULT* pResult)
{
	m_rgain=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_RGAIN))->GetPos();
	m_ggain=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GGAIN))->GetPos();
	m_bgain=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_BGAIN))->GetPos();

	CString cstr;
	cstr.Format("%5.2f", m_rgain/64.0f);
	SetDlgItemText(IDC_LB_CCD_RGAIN,cstr.GetBuffer());

	cstr.Format("%5.2f",m_ggain/64.0f);
	SetDlgItemText(IDC_LB_CCD_GGAIN,cstr.GetBuffer());

	cstr.Format("%5.2f",m_bgain/64.0f);
	SetDlgItemText(IDC_LB_CCD_BGAIN,cstr.GetBuffer());

	CameraSetGain(m_rgain,m_ggain,m_bgain);

	theApp.m_CCD.m_rgain=m_rgain;
	theApp.m_CCD.m_ggain=m_ggain;
	theApp.m_CCD.m_bgain=m_bgain;
}

void CCamSettingDlg::oncustomdraw_color_gamma(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_gamma=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GAMMA))->GetPos();
	CameraSetGamma(m_gamma);
	theApp.m_CCD.m_gamma=m_gamma;
	float x = m_gamma/100.0f;
	CString cstr;
	cstr.Format("%4.2f", x);
	SetDlgItemText(IDC_LB_CCD_GAMMA,cstr.GetBuffer());
}

void CCamSettingDlg::oncustomdraw_color_contrast(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_contrast=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_CONTRAST))->GetPos();
	CameraSetContrast(m_contrast);
	theApp.m_CCD.m_contrast=m_contrast;
	CString cstr;
	cstr.Format("%d", m_contrast);
	SetDlgItemText(IDC_LB_CCD_CONTRAST,cstr.GetBuffer());
}

void CCamSettingDlg::oncustomdraw_color_saturation(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_saturation=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_SATURATION))->GetPos();
	CameraSetSaturation(m_saturation);
	theApp.m_CCD.m_saturation=m_saturation;
	CString cstr;
	cstr.Format("%d", m_saturation);
	SetDlgItemText(IDC_LB_CCD_SATURATION,cstr.GetBuffer());
}

void CCamSettingDlg::oncustomdraw_aetarget(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_aetarget=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_AETARGET))->GetPos();
	CameraSetAeTarget(m_aetarget);
	theApp.m_CCD.m_aetarget=m_aetarget;

	CString cstr;
	cstr.Format("%d", m_aetarget);
	SetDlgItemText(IDC_LB_CCD_AETARGET,cstr.GetBuffer());
}

void CCamSettingDlg::oncustomdraw_exposuregain(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_analoggain=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSUREGAIN))->GetPos();
	CameraSetAnalogGain(m_analoggain);
	theApp.m_CCD.m_analoggain=m_analoggain;

	UpdateExposureGainText();
}

void CCamSettingDlg::oncustomdraw_exposuretime(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(m_aestate)
		return;
	m_exposuretime=((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSURETIME))->GetPos();
	CameraSetExposureTime(m_exposuretime);
	theApp.m_CCD.m_exposuretime=m_exposuretime;

	UpdateExposureTimeText();
}


void CCamSettingDlg::OnBnClickedChbCcdColorenhance()
{
	// TODO: Add your control notification handler code here
	m_color_enhance=((CButton *)GetDlgItem(IDC_CHB_CCD_COLORENHANCE))->GetCheck()==BST_CHECKED;
	CameraSetColorEnhancement(m_color_enhance);
	GetDlgItem(IDC_SD_CCD_SATURATION)->EnableWindow(m_color_enhance);
	GetDlgItem(IDC_LB_CCD_SATURATION)->EnableWindow(m_color_enhance);
}


void CCamSettingDlg::OnBnClickedBnCcdAwbone()
{
	// TODO: Add your control notification handler code here
	CameraSetAWBState(TRUE);
	Sleep(200);
	CameraGetGain((int *)&m_rgain, (int *)&m_ggain, (int *)&m_bgain);
	
	CString cstr;
	cstr.Format("%5.2f", m_rgain/64.0f);
	SetDlgItemText(IDC_LB_CCD_RGAIN,cstr.GetBuffer());
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_RGAIN))->SetPos(m_rgain);
	
	cstr.Format("%5.2f", m_ggain/64.0f);
	SetDlgItemText(IDC_LB_CCD_GGAIN,cstr.GetBuffer());
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_GGAIN))->SetPos(m_ggain);
	
	cstr.Format("%5.2f", m_bgain/64.0f);
	SetDlgItemText(IDC_LB_CCD_BGAIN,cstr.GetBuffer());
	((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_BGAIN))->SetPos(m_bgain);
	
}

void CCamSettingDlg::UpdateExposureGainText()
{
	float analoggain=6 + (0.0351f * m_analoggain);
	CString cstr;
	cstr.Format("%.3f dB",  analoggain);
	SetDlgItemText(IDC_LB_CCD_EXPOSUREGAIN,cstr.GetBuffer());
}

void CCamSettingDlg::UpdateExposureTimeText()
{
	UINT rowtime;
	CString cstr;
	
	CameraGetRowTime(&rowtime);
	cstr.Format("%dF %dL %.2fS ", m_exposuretime/1068, m_exposuretime%1068, (float)m_exposuretime*rowtime/1000000 );
	SetDlgItemText(IDC_LB_CCD_EXPOSURETIME,cstr.GetBuffer());
}

void CCamSettingDlg::OnBnClickedChbCcdAe()
{
	// TODO: Add your control notification handler code here
	m_aestate=((CButton *)GetDlgItem(IDC_CHB_CCD_AE))->GetCheck()==BST_CHECKED;
	CameraSetAeState(m_aestate);

	GetDlgItem(IDC_SD_CCD_EXPOSUREGAIN)->EnableWindow(!m_aestate);
	GetDlgItem(IDC_LB_CCD_EXPOSUREGAIN)->EnableWindow(!m_aestate);
	GetDlgItem(IDC_SD_CCD_EXPOSURETIME)->EnableWindow(!m_aestate);
	GetDlgItem(IDC_LB_CCD_EXPOSURETIME)->EnableWindow(!m_aestate);
	GetDlgItem(IDC_SD_CCD_AETARGET)->EnableWindow(m_aestate);
	GetDlgItem(IDC_LB_CCD_AETARGET)->EnableWindow(m_aestate);
	if(!m_aestate)
	{
		CameraGetExposureTime((int *)&m_exposuretime);
		UpdateExposureTimeText();
		((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSURETIME))->SetPos(m_exposuretime);

		CameraGetAnalogGain((USHORT *)&m_analoggain);
		UpdateExposureGainText();
		((CSliderCtrl *)GetDlgItem(IDC_SD_CCD_EXPOSURETIME))->SetPos(m_analoggain);
	}

}


void CCamSettingDlg::OnBnClickedBnCcdRestartexposure()
{
	// TODO: Add your control notification handler code here
	CameraRestartLongExposure(TRUE);
}


void CCamSettingDlg::OnBnClickedRbCcdImageJpg()
{
	// TODO: Add your control notification handler code here
	m_image_type=FILE_JPG;
	theApp.m_CCD.m_image_type=FILE_JPG;
}


void CCamSettingDlg::OnBnClickedRbCcdImageBmp()
{
	// TODO: Add your control notification handler code here
	m_image_type=FILE_BMP;
	theApp.m_CCD.m_image_type=FILE_BMP;
}


void CCamSettingDlg::OnBnClickedRbCcdImageRaw()
{
	// TODO: Add your control notification handler code here
	m_image_type=FILE_RAW;
	theApp.m_CCD.m_image_type=FILE_RAW;
}


void CCamSettingDlg::OnBnClickedRbCcdLine()
{
	// TODO: Add your control notification handler code here
	CameraSetB2RGBMode(B2RGB_MODE_LINE);
	m_b2rgb_mode=B2RGB_MODE_LINE;
	theApp.m_CCD.m_b2rgb_mode=B2RGB_MODE_LINE;
}


void CCamSettingDlg::OnBnClickedRbCcdHamilton()
{
	// TODO: Add your control notification handler code here
	CameraSetB2RGBMode(B2RGB_MODE_HAMILTON);
	m_b2rgb_mode=B2RGB_MODE_HAMILTON;
	theApp.m_CCD.m_b2rgb_mode=B2RGB_MODE_HAMILTON;
}


void CCamSettingDlg::OnBnClickedRbCcdLaroche()
{
	// TODO: Add your control notification handler code here
	CameraSetB2RGBMode(B2RGB_MODE_LAROCHE);
	m_b2rgb_mode=B2RGB_MODE_LAROCHE;
	theApp.m_CCD.m_b2rgb_mode=B2RGB_MODE_LAROCHE;
}


void CCamSettingDlg::OnBnClickedRbCcdDw8()
{
	// TODO: Add your control notification handler code here
	CameraSetDataWide(FALSE);
}


void CCamSettingDlg::OnBnClickedRbCcdDw16()
{
	// TODO: Add your control notification handler code here
	CameraSetDataWide(TRUE);
}


void CCamSettingDlg::OnBnClickedRbCcdIdataSelHigh()
{
	// TODO: Add your control notification handler code here
	CameraSetDataSel(DATA_SEL_HIGH);
}


void CCamSettingDlg::OnBnClickedRbCcdIdataSelMid()
{
	// TODO: Add your control notification handler code here
	CameraSetDataSel(DATA_SEL_MID);
}


void CCamSettingDlg::OnBnClickedRbCcdIdataSelLow()
{
	// TODO: Add your control notification handler code here
	CameraSetDataSel(DATA_SEL_LOW);
}


void CCamSettingDlg::OnCbnSelchangeCbCcdFramespeed()
{
	// TODO: Add your control notification handler code here
	BYTE btmp =0;
	CameraGetFrameSpeed(&btmp);

	CComboBox *pcb=(CComboBox *)GetDlgItem(IDC_CB_CCD_FRAMESPEED);
	DS_FRAME_SPEED frmspeed=(DS_FRAME_SPEED)pcb->GetCurSel();
	if(btmp!=frmspeed)
	{
		if(frmspeed==FRAME_SPEED_NORMAL)
		{
			BOOL bDataWide = FALSE;
			CameraGetDataWide(&bDataWide);
			if (bDataWide)
			{
				CameraSetDataWide(FALSE); 
				CheckDlgButton(IDC_RB_CCD_DW_16, BST_UNCHECKED);
				CheckDlgButton(IDC_RB_CCD_DW_8,  BST_CHECKED);
			}
			GetDlgItem(IDC_RB_CCD_DW_16)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_RB_CCD_DW_16)->EnableWindow(TRUE);
		}
		CameraSetFrameSpeed((DS_FRAME_SPEED)(frmspeed));
		UpdateExposureTimeText();
	}
}


void CCamSettingDlg::OnBnClickedRbCcdParamA()
{
	// TODO: Add your control notification handler code here
	CameraReadParameter(PARAMETER_TEAM_A);
	m_param_team=PARAMETER_TEAM_A;
	theApp.m_CCD.m_param_team=PARAMETER_TEAM_A;

	updateDlg();
}


void CCamSettingDlg::OnBnClickedRbCcdParamB()
{
	// TODO: Add your control notification handler code here
	CameraReadParameter(PARAMETER_TEAM_B);
	m_param_team=PARAMETER_TEAM_B;
	theApp.m_CCD.m_param_team=PARAMETER_TEAM_B;

	updateDlg();
}


void CCamSettingDlg::OnBnClickedRbCcdParamC()
{
	// TODO: Add your control notification handler code here
	CameraReadParameter(PARAMETER_TEAM_C);
	m_param_team=PARAMETER_TEAM_C;
	theApp.m_CCD.m_param_team=PARAMETER_TEAM_C;

	updateDlg();
}


void CCamSettingDlg::OnBnClickedRbCcdParamD()
{
	// TODO: Add your control notification handler code here
	CameraReadParameter(PARAMETER_TEAM_D);
	m_param_team=PARAMETER_TEAM_D;
	theApp.m_CCD.m_param_team=PARAMETER_TEAM_D;

	updateDlg();
}


void CCamSettingDlg::OnBnClickedBnCcdParamSave()
{
	// TODO: Add your control notification handler code here
	CameraSaveParameter(m_param_team);

	updateDlg();
}
