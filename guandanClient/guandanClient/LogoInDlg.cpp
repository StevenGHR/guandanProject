// LogoInDlg.cpp : implementation file
//

#include "stdafx.h"
#include "guandanClient.h"
#include "LogoInDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"

// CLogoInDlg dialog

IMPLEMENT_DYNAMIC(CLogoInDlg, CDialogEx)

CLogoInDlg::CLogoInDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogoInDlg::IDD, pParent), m_strUser(_T(""))
{
	//初始化IP地址
	//DWORD 就是unSigned long
	m_dwIP = ntohl(inet_addr("127.0.0.1"));
}

CLogoInDlg::~CLogoInDlg()
{
}

void CLogoInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IP_ADDR, m_dwIP);
	DDX_Text(pDX, IDC_ET_NAME, m_strUser);
}


BEGIN_MESSAGE_MAP(CLogoInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_LOGOIN, &CLogoInDlg::OnBnClickedBtnLogoin)
	ON_BN_CLICKED(IDOK, &CLogoInDlg::OnBnClickedOk)
END_MESSAGE_MAP()



void CLogoInDlg::OnBnClickedBtnLogoin()
{
	//登录	
	UpdateData();
	if(m_strUser.IsEmpty())
	{
		AfxMessageBox(_T("用户名不能为空！"));
		return;
	}

	if(m_dwIP==0)
	{
		AfxMessageBox(_T("无效IP地址"));
		return;
	}

	CClientSocket* pSock = theApp.GetMainSocket();
	IN_ADDR addr ;
	addr.S_un.S_addr = htonl(m_dwIP);
	CString strIP(inet_ntoa(addr));
	if(!pSock->Connect(strIP.GetBuffer(0),8989))
	{
		AfxMessageBox(_T("连接服务器失败！"));
		return ;
	}
	//发送
	pSock->m_strUserName = m_strUser;
	char* pBuff = new char[m_strUser.GetLength()*4];
	memset(pBuff, 0, m_strUser.GetLength()*4);
	WChar2MByte(m_strUser.GetBuffer(0), pBuff, m_strUser.GetLength()*4);
	pSock->LogoIn(pBuff, m_strUser.GetLength()*4);
	delete pBuff;
	CDialogEx::OnCancel();
}


void CLogoInDlg::OnBnClickedOk()
{
	//退出
	CClientSocket* pSock = theApp.GetMainSocket();
	pSock->Close();
	CDialogEx::OnOK();
}


BOOL CLogoInDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}
