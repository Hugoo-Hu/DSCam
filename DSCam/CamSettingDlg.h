#pragma once


// CCamSettingDlg dialog

class CCamSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCamSettingDlg)

public:
	CCamSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCamSettingDlg();

// Dialog Data
	enum { IDD = IDD_CCD_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	HICON m_hIcon;

	UINT m_rgain;
	UINT m_ggain;
	UINT m_bgain;
	UINT m_gamma;
	UINT m_contrast;
	UINT m_saturation;
	UINT m_aetarget;
	UINT m_exposuretime;
	UINT m_analoggain;

	BOOL m_aestate;
	BOOL m_color_enhance;
	BOOL m_data_wide;

	DS_B2RGB_MODE m_b2rgb_mode;
	DS_DATA_SEL m_data_sel;
	DS_PARAMETER_TEAM m_param_team;
	DS_FRAME_SPEED m_frame_speed;

	string m_path2save;
	DS_FILE_TYPE m_image_type;


protected:
	virtual BOOL OnInitDialog();
	virtual void OnOK();

	void UpdateExposureGainText();
	void UpdateExposureTimeText();
	void updateDlg();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnPathSearch();

	afx_msg void oncustomdraw_color_rgb(UINT id,NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_color_gamma(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_color_contrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_color_saturation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_aetarget(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_exposuregain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void oncustomdraw_exposuretime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedChbCcdColorenhance();
	afx_msg void OnBnClickedBnCcdAwbone();
	afx_msg void OnBnClickedChbCcdAe();
	afx_msg void OnBnClickedBnCcdRestartexposure();
	afx_msg void OnBnClickedRbCcdImageJpg();
	afx_msg void OnBnClickedRbCcdImageBmp();
	afx_msg void OnBnClickedRbCcdImageRaw();
	afx_msg void OnBnClickedRbCcdLine();
	afx_msg void OnBnClickedRbCcdHamilton();
	afx_msg void OnBnClickedRbCcdLaroche();
	afx_msg void OnBnClickedRbCcdDw8();
	afx_msg void OnBnClickedRbCcdDw16();
	afx_msg void OnBnClickedRbCcdIdataSelHigh();
	afx_msg void OnBnClickedRbCcdIdataSelMid();
	afx_msg void OnBnClickedRbCcdIdataSelLow();
	afx_msg void OnCbnSelchangeCbCcdFramespeed();
	afx_msg void OnBnClickedRbCcdParamA();
	afx_msg void OnBnClickedRbCcdParamB();
	afx_msg void OnBnClickedRbCcdParamC();
	afx_msg void OnBnClickedRbCcdParamD();
	afx_msg void OnBnClickedBnCcdParamSave();
};
