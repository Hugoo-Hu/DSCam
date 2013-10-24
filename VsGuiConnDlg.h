#pragma once


extern vector<string> getCommPort();

// CVsGuiConnDlg dialog

class CVsGuiConnDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVsGuiConnDlg)

public:
	CVsGuiConnDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CVsGuiConnDlg();

// Dialog Data
	enum { IDD = IDD_VSGUI_CONNECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	HICON m_hIcon;

	string m_port;

	virtual BOOL OnInitDialog();

	afx_msg virtual void OnOK();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnComautodetect();
};
