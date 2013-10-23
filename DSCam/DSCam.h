
// DSCam.h : main header file for the DSCam application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDSCamApp:
// See DSCam.cpp for the implementation of this class
//

class CDSCamApp : public CWinAppEx
{
public:
	CDSCamApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	CVsGui m_vsgui;
	CCCD m_CCD;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDSCamApp theApp;
