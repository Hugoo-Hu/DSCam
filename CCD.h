#pragma once
class CCCD
{
public:
	CCCD(void);
	~CCCD(void);

	//‘› ±Œ¥”√µΩ
	BOOL isCCDopen();
	string getport();

	//DS_RUNMODE getCCDstatus();

	DS_RESOLUTION m_resolution;
	DS_RUNMODE m_runstatus;

	string m_path2save;

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
	DS_FILE_TYPE m_image_type;

	BOOL m_ismono;

	int m_videocnt;
	BOOL m_isinit;

private:
	BOOL m_bisCCDopen;
	string m_sport;

	//DS_RUNMODE m_ccdstatus;
};

