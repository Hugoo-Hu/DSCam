// VsGuiSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DSCam.h"
#include "settings.h"
#include "VsGuiSettingDlg.h"
#include "afxdialogex.h"


// CVsGuiSettingDlg dialog

IMPLEMENT_DYNAMIC(CVsGuiSettingDlg, CDialogEx)

CVsGuiSettingDlg::CVsGuiSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVsGuiSettingDlg::IDD, pParent)
{
	m_wl_curr=0.0F;
	m_wl_step=0.0F;
	m_wl_max=0.0F;
	m_wl_min=0.0F;
	m_wl_min_cap=0.0F;
	m_wl_max_cap=0.0F;
}

CVsGuiSettingDlg::~CVsGuiSettingDlg()
{
}

void CVsGuiSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVsGuiSettingDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_EN_KILLFOCUS(IDC_ED_WL_CURRENT, &CVsGuiSettingDlg::OnEnKillfocusEdWlCurrent)
	ON_EN_KILLFOCUS(IDC_ED_WL_SWEEPSTEP, &CVsGuiSettingDlg::OnEnKillfocusEdWlSweepstep)
	//ON_BN_CLICKED(IDOK, &CVsGuiSettingDlg::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_ED_WL_MIN_CAP, &CVsGuiSettingDlg::OnEnKillfocusEdWlMinCap)
	ON_EN_KILLFOCUS(IDC_ED_WL_MAX_CAP, &CVsGuiSettingDlg::OnEnKillfocusEdWlMaxCap)
	ON_BN_CLICKED(IDC_BN_WL_SET_CURR, &CVsGuiSettingDlg::OnBnClickedBnWlSetCurr)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SD_WLRANGE, &CVsGuiSettingDlg::OnNMCustomdrawSdWlrange)
END_MESSAGE_MAP()


// CVsGuiSettingDlg message handlers
BOOL CVsGuiSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	if(theApp.m_vsgui.m_isopen)
	{
		double wl_min=0.0F,wl_max=0.0F;
		wl_min=theApp.m_vsgui.m_vsinfo.minWl;
		wl_max=theApp.m_vsgui.m_vsinfo.maxWl;
		m_wl_curr=theApp.m_vsgui.m_wl_curr;
		m_wl_step=theApp.m_vsgui.m_wl_step;
		m_wl_min=theApp.m_vsgui.m_vsinfo.minWl;
		m_wl_max=theApp.m_vsgui.m_vsinfo.maxWl;
		m_wl_min_cap=theApp.m_vsgui.m_wl_min_cap;
		m_wl_max_cap=theApp.m_vsgui.m_wl_max_cap;
		CString cstr(_T(""));
		cstr.Format(_T("%.2lf"),wl_min);
		SetDlgItemText(IDC_LB_WL_MIN,cstr.GetBuffer());
		cstr.Format(_T("%.2lf"),wl_max);
		SetDlgItemText(IDC_LB_WL_MAX,cstr.GetBuffer());
		cstr.Format(_T("%.2lf"),m_wl_step);
		SetDlgItemText(IDC_ED_WL_SWEEPSTEP,cstr.GetBuffer());
		cstr.Format(_T("%.2lf"),m_wl_min_cap);
		SetDlgItemText(IDC_ED_WL_MIN_CAP,cstr);
		cstr.Format(_T("%.2lf"),m_wl_max_cap);
		SetDlgItemText(IDC_ED_WL_MAX_CAP,cstr);

		CSliderCtrl *wl_slider=(CSliderCtrl *) GetDlgItem(IDC_SD_WLRANGE);
			wl_slider->SetRange((int)(wl_min+0.5),(int)(wl_max+0.5));
			
		double wl_range=wl_max-wl_min;
		int wl_step=0;
		if(wl_range<20)
			wl_step=2;
		else if(wl_range<100)
			wl_step=10;
		else if(wl_range<500)
			wl_step=20;
		else
			wl_step=50;

		wl_slider->SetPageSize(wl_step);
		
		if(m_wl_curr>=theApp.m_vsgui.m_vsinfo.minWl&&m_wl_curr<=theApp.m_vsgui.m_vsinfo.maxWl)
		{
			cstr.Format(_T("%.2lf"),m_wl_curr);
			SetDlgItemText(IDC_ED_WL_CURRENT,cstr.GetBuffer());
			
			wl_slider->SetPos(int(m_wl_curr+0.5));
		}

		cstr.Format(_T("%.2f"),m_wl_step);
		SetDlgItemText(IDC_ED_WL_SWEEPSTEP,cstr.GetBuffer());
	}
	else
	{
		SetDlgItemText(IDC_LB_WL_MIN,_T("---"));
		SetDlgItemText(IDC_LB_WL_MAX,_T("---"));
	}
	

	return TRUE;// return TRUE  unless you set the focus to a control
}


void CVsGuiSettingDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl *pslider = (CSliderCtrl *) GetDlgItem(IDC_SD_WLRANGE);
	double wl_curr=pslider->GetPos();

	if(wl_curr!=m_wl_curr)
	{
		m_wl_curr=wl_curr;
		CString cstr(_T(""));
		cstr.Format(_T("%.2lf"),m_wl_curr);
		SetDlgItemText(IDC_ED_WL_CURRENT,cstr.GetBuffer());
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CVsGuiSettingDlg::OnEnKillfocusEdWlCurrent()
{
	// TODO: Add your control notification handler code here
	CString cstr(_T(""));
	GetDlgItemText(IDC_ED_WL_CURRENT,cstr);
	if(cstr==_T(""))
		return;

	double wl_curr=_tstof(cstr.GetBuffer());
	if(wl_curr<0)
	{
		MessageBox(_T("当前波长值不能小于0."),_T("错误"),MB_ICONERROR);
		cstr.Format(_T("%.2lf"),m_wl_curr);
		SetDlgItemText(IDC_ED_WL_CURRENT,cstr);
	}
	if(wl_curr<m_wl_min||wl_curr>m_wl_max)
	{
		MessageBox(_T("当前波长值超出范围."),_T("错误"),MB_ICONERROR);
		cstr.Format(_T("%.2lf"),m_wl_curr);
		SetDlgItemText(IDC_ED_WL_CURRENT,cstr.GetBuffer());
	}

	m_wl_curr=wl_curr;
	CSliderCtrl *pslider = (CSliderCtrl *) GetDlgItem(IDC_SD_WLRANGE);
	pslider->SetPos(int(m_wl_curr+0.5));

	VsSetWavelength(theApp.m_vsgui.m_vshwnd,m_wl_curr,TRUE);
	theApp.m_vsgui.m_wl_curr=m_wl_curr;
}


void CVsGuiSettingDlg::OnEnKillfocusEdWlSweepstep()
{
	// TODO: Add your control notification handler code here
	CString cstr(_T(""));
	GetDlgItemText(IDC_ED_WL_SWEEPSTEP,cstr);
	if(cstr==_T(""))
		return;

	double wl_sweepstep=_tstof(cstr.GetBuffer());
	if(wl_sweepstep<0)
	{
		MessageBox(_T("扫描步进不能小于0."),_T("错误"),MB_ICONERROR);
		cstr.Format(_T("%.2lf"),m_wl_step);
		SetDlgItemText(IDC_ED_WL_SWEEPSTEP,cstr);
	}
	if(wl_sweepstep>m_wl_max_cap-m_wl_min_cap)
	{
		MessageBox(_T("扫描步进超出波长范围."),_T("错误"),MB_ICONERROR);
		cstr.Format(_T("%.2lf"),m_wl_step);
		SetDlgItemText(IDC_ED_WL_SWEEPSTEP,cstr);
	}

	VsSetWavelengthStep(theApp.m_vsgui.m_vshwnd,wl_sweepstep,TRUE);
	m_wl_step=wl_sweepstep;
	theApp.m_vsgui.m_wl_step=m_wl_step;

	Csettings *settings=Csettings::getInstance();
#ifdef XMLDOM
	settings->set_wl_step_dom(m_wl_step);
#else
	settings->set_wl_step(m_wl_step);
#endif

}


//void CVsGuiSettingDlg::OnBnClickedOk()
//{
//	// TODO: Add your control notification handler code here
//	if(m_wl_step!=theApp.m_vsgui.m_dsweepstep)
//	{
//		if(theApp.m_vsgui.set_wavelength_step(m_wl_step))
//			theApp.m_vsgui.m_dsweepstep=m_wl_step;
//		else
//		{
//			MessageBox(_T("设置扫描步进出错, 请稍后再试."),_T("错误"),MB_ICONERROR);
//			return;
//		}
//	}
//	if(m_wl_curr!=theApp.m_vsgui.m_wl_curr)
//	{
//		if(theApp.m_vsgui.set_wavelength(m_wl_curr))
//			theApp.m_vsgui.m_wl_curr=m_wl_curr;
//		else
//		{
//			MessageBox(_T("设置波长出错,请稍后再试."),_T("错误"),MB_ICONERROR);
//			return;
//		}
//	}
//
//	CDialogEx::OnOK();
//}

void CVsGuiSettingDlg::OnOK()
{
	if(m_wl_step!=theApp.m_vsgui.m_wl_step)
	{
		if(VsSetWavelengthStep(theApp.m_vsgui.m_vshwnd,m_wl_step,TRUE))
			theApp.m_vsgui.m_wl_step=m_wl_step;
		else
		{
			MessageBox(_T("设置扫描步进出错, 请稍后再试."),_T("错误"),MB_ICONERROR);
			return;
		}
	}
	CDialogEx::OnOK();
}


void CVsGuiSettingDlg::OnEnKillfocusEdWlMinCap()
{
	// TODO: Add your control notification handler code here
	CString cstr(_T(""));
	GetDlgItemText(IDC_ED_WL_MIN_CAP,cstr);
	double wl_min_cap=_tstof(cstr.GetBuffer());
	if(wl_min_cap<m_wl_min)
	{
		cstr.Format(_T("%.2lf"),m_wl_min);
		SetDlgItemText(IDC_ED_WL_MIN_CAP,cstr.GetBuffer());
		wl_min_cap=m_wl_min;
	}
	m_wl_min_cap=wl_min_cap;
	theApp.m_vsgui.m_wl_min_cap=m_wl_min_cap;
}


void CVsGuiSettingDlg::OnEnKillfocusEdWlMaxCap()
{
	// TODO: Add your control notification handler code here
	CString cstr(_T(""));
	GetDlgItemText(IDC_ED_WL_MAX_CAP,cstr);
	double wl_max_cap=_tstof(cstr.GetBuffer());
	if(wl_max_cap>m_wl_max)
	{
		cstr.Format(_T("%.2lf"),m_wl_max);
		SetDlgItemText(IDC_ED_WL_MIN_CAP,cstr.GetBuffer());
		wl_max_cap=m_wl_max;
	}
	m_wl_max_cap=wl_max_cap;
	theApp.m_vsgui.m_wl_max_cap=m_wl_max_cap;
}


void CVsGuiSettingDlg::OnBnClickedBnWlSetCurr()
{
	// TODO: Add your control notification handler code here
	if(m_wl_curr!=theApp.m_vsgui.m_wl_curr)
	{
		if(!VsSetWavelength(theApp.m_vsgui.m_vshwnd,m_wl_curr,TRUE))
		{
			MessageBox(_T("设置波长出错,请稍后再试."),_T("错误"),MB_ICONERROR);
			return;
		}
		theApp.m_vsgui.m_wl_curr=m_wl_curr;
	}
}


void CVsGuiSettingDlg::OnNMCustomdrawSdWlrange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CSliderCtrl *pslider=(CSliderCtrl *) GetDlgItem(IDC_SD_WLRANGE);
	m_wl_curr=pslider->GetPos();
	VsSetWavelength(theApp.m_vsgui.m_vshwnd,m_wl_curr,TRUE);
	theApp.m_vsgui.m_wl_curr=m_wl_curr;
	CString cstr;
	cstr.Format(_T("%.2f"),m_wl_curr);
	SetDlgItemText(IDC_ED_WL_CURRENT,cstr.GetBuffer());

}
