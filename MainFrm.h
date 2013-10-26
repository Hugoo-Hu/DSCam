
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);

	afx_msg void on_dev_open_ccd();
	afx_msg void on_dev_open_vs();
	afx_msg void on_dev_open_all();
	afx_msg void on_dev_close_ccd();
	afx_msg void on_dev_close_vs();
	afx_msg void on_dev_close_all();

	afx_msg void on_dev_info();
	afx_msg void on_dev_setting_vs();
	afx_msg void on_dev_setting_ccd();

	afx_msg void on_video_play();
	afx_msg void on_video_pause();
	afx_msg void on_video_cap();
	afx_msg void on_video_cap_consecutive();
	afx_msg void on_video_mono();
	afx_msg void on_video_mono_update(CCmdUI* pCmdUI);

	afx_msg long on_ccd_video_msg(WPARAM wP, LPARAM lP);

	DECLARE_MESSAGE_MAP()

};


