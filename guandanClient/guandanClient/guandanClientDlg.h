
// NetChatClientDlg.h : ͷ�ļ�
//

#pragma once


// CNetChatClientDlg �Ի���
class CguandanClientDlg : public CDialogEx
{
// ����
public:
	CguandanClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GUANDANCLIENT_DIALOG };
	void UpdateUserInfo(CString strInfo);
	void UpdateText(CString& strText);  //���������¼
	void UpdateHandcards(CString& strText);
	void UpdateReady(CString strInfo);
	void UpdateUserName(CString strInfo,CString myname);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	
	//CString m_strSend;
// ʵ��ee
protected:
	HICON m_hIcon;
	BOOL WChar2MByte(LPCTSTR lpSrc, LPSTR lpDest, int nlen);
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedBtnSend();
	CString m_strSend;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnReady();
	afx_msg void OnLbnSelchange0Handcards();
};
