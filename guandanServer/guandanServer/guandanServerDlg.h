
// guandanServerDlg.h : ͷ�ļ�
//

#pragma once


// CguandanServerDlg �Ի���
class CguandanServerDlg : public CDialogEx
{
// ����
public:
	CguandanServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void DisplayLog(CString &strInfo) const;
	void UpdateUserInfo(CString strUserInfo) const;
// �Ի�������
	enum { IDD = IDD_GUANDANSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
