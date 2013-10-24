#pragma once


// CVsGuiSettingDlg dialog

class CVsGuiSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVsGuiSettingDlg)

public:
	CVsGuiSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVsGuiSettingDlg();

// Dialog Data
	enum { IDD = IDD_VSGUI_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	HICON m_hIcon;

	double m_wl_curr;
	double m_wl_step;
	double m_wl_max;
	double m_wl_min;

	double m_wl_min_cap;
	double m_wl_max_cap;

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnKillfocusEdWlCurrent();
	afx_msg void OnEnKillfocusEdWlSweepstep();
	//afx_msg void OnBnClickedOk();

	virtual void OnOK();
	afx_msg void OnEnKillfocusEdWlMinCap();
	afx_msg void OnEnKillfocusEdWlMaxCap();
	afx_msg void OnBnClickedBnWlSetCurr();
	afx_msg void OnNMCustomdrawSdWlrange(NMHDR *pNMHDR, LRESULT *pResult);
};
