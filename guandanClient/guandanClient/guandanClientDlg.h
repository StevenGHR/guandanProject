
// NetChatClientDlg.h : 头文件
//

#pragma once


// CNetChatClientDlg 对话框
class CguandanClientDlg : public CDialogEx
{
// 构造
public:
	CguandanClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GUANDANCLIENT_DIALOG };
	void UpdateUserInfo(CString strInfo);
	void UpdateText(CString& strText);  //跟新聊天记录
	void UpdateHandcards(CString& strText);
	void UpdateReady(CString strInfo);
	void UpdateUserName(CString strInfo,CString myname);
	void UpdateShowcards(CString strInfo,CString myname);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	
	//CString m_strSend;
// 实现ee
protected:
	HICON m_hIcon;
	BOOL WChar2MByte(LPCTSTR lpSrc, LPSTR lpDest, int nlen);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedBtnSend();
	CString m_strSend;
	CString m_showedcards;
	CString name_1;
	CString name_2;
	CString name_3;
	CString m_showcards;
	CString showcards_1;
	CString showcards_2;
	CString showcards_3;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnReady();
	afx_msg void OnLbnSelchange0Handcards();

};
