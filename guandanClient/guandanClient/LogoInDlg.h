#pragma once


class CLogoInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogoInDlg)

public:
	CLogoInDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLogoInDlg();

// Dialog Data
	enum { IDD = IDD_DLG_LOGOIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnLogoin();
	afx_msg void OnBnClickedOk();
	
	DWORD m_dwIP;
	CString m_strUser;
};
