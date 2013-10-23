#pragma once


// CDevInfoDlg dialog

class CDevInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDevInfoDlg)

public:
	CDevInfoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDevInfoDlg();

// Dialog Data
	enum { IDD = IDD_DEV_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
