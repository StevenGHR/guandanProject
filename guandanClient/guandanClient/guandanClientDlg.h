
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
	void UpdateShowcards(CString strInfo,CString myname);
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
