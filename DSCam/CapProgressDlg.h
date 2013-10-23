#pragma once

#define IDLE_EVENT			100

// CCapProgressDlg dialog

class CCapProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCapProgressDlg)

public:
	CCapProgressDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCapProgressDlg();

// Dialog Data
	enum { IDD = IDD_CAP_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
};
