
// guandanClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "guandanClient.h"
#include "guandanClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNetChatClientDlg 对话框




CguandanClientDlg::CguandanClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CguandanClientDlg::IDD, pParent)
	, m_strSend(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CguandanClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ET_SEND, m_strSend);
}

BEGIN_MESSAGE_MAP(CguandanClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND, &CguandanClientDlg::OnBnClickedBtnSend)
	ON_BN_CLICKED(IDCANCEL, &CguandanClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_Play, &CguandanClientDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_Ready, &CguandanClientDlg::OnBnClickedBtnReady)
	ON_LBN_SELCHANGE(IDC_0_Handcards, &CguandanClientDlg::OnLbnSelchange0Handcards)
END_MESSAGE_MAP()


// CNetChatClientDlg 消息处理程序

BOOL CguandanClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CguandanClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CguandanClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CguandanClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CguandanClientDlg::OnBnClickedBtnSend()
{
	//发送消息
	UpdateData();
	if(m_strSend.IsEmpty())
	{
		AfxMessageBox(_T("发送类容不能为空！"));
		return ;
	}

	CString temp ;
	CTime time = CTime::GetCurrentTime();
	temp = time.Format("%H:%M:%S");
	//姓名 +_T("\n\t") 时间
	m_strSend = theApp.GetMainSocket()->m_strUserName+_T("  ") + temp +_T("\r\n   ") + m_strSend +_T("\r\n");

	char* pBuff = new char[m_strSend.GetLength()*2];
	memset(pBuff, 0, m_strSend.GetLength()*2);
	//转换为多字节
	WChar2MByte(m_strSend.GetBuffer(0), pBuff, m_strSend.GetLength()*2);
	//
	theApp.GetMainSocket()->SendMSG(pBuff, m_strSend.GetLength()*2);

	delete pBuff;

	m_strSend.Empty();
	UpdateData(0);
	
}

BOOL CguandanClientDlg::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}

void CguandanClientDlg::OnBnClickedCancel()
{
	//退出
	CDialogEx::OnCancel();
}

void CguandanClientDlg::UpdateUserInfo(CString strInfo)
{
	CString strTmp;
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_LB_ONLINE);
	pBox->ResetContent();
	while(!strInfo.IsEmpty())
	{
		int n = strInfo.Find('#');
		if(n==-1)
			break;
		strTmp = strInfo.Left(n);
		pBox->AddString(strTmp);
		strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	}
}

void CguandanClientDlg::UpdateText(CString &strText)
{
	((CEdit*)GetDlgItem(IDC_ET_TEXT))->ReplaceSel(strText);
}

void CguandanClientDlg::UpdateHandcards(CString &strText)
{
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_0_Handcards);
	pBox->ResetContent();
	pBox->AddString(strText);
}

void CguandanClientDlg::UpdateReady(CString strInfo)
{
	CString strTmp;
	CListBox* pBox = (CListBox*)GetDlgItem(IDC_LB_Gamestate);
	pBox->ResetContent();
	while(!strInfo.IsEmpty())
	{
		int n = strInfo.Find('#');
		if(n==-1)
			break;
		strTmp = strInfo.Left(n);
		pBox->AddString(strTmp);
		strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	}
}

void CguandanClientDlg::OnBnClickedBtnPlay()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CguandanClientDlg::OnBnClickedBtnReady()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送消息
	UpdateData();

	CString temp,msg ;
	CTime time = CTime::GetCurrentTime();
	temp = time.Format("%H:%M:%S");
	//姓名 +_T("\n\t") 时间
	msg = theApp.GetMainSocket()->m_strUserName+_T("  ") + temp +_T("\r\n   ") + _T("已准备。。。") +_T("\r\n");
	
	char* pBuff = new char[msg.GetLength()*2];
	memset(pBuff, 0, msg.GetLength()*2);
	//转换为多字节
	WChar2MByte(msg.GetBuffer(0), pBuff, msg.GetLength()*2);
	//
	theApp.GetMainSocket()->Ready(pBuff, msg.GetLength()*2);

	delete pBuff;

	UpdateData(0);
}

void CguandanClientDlg::UpdateUserName(CString strInfo,CString myname)
{
	CString strTmp,Infotemp=strInfo;
	int player_number,number_change=0;
	while(!Infotemp.IsEmpty())
	{
		int n = Infotemp.Find('#');
		if(n==-1)
			break;
		strTmp = Infotemp.Left(n);
		if(strTmp.Mid(1)==myname)
		{
			strTmp=strTmp.Left(1);
			number_change=_ttoi(strTmp);
			break;
		}
		Infotemp = Infotemp.Right(Infotemp.GetLength()-n-1);
	}

	while(!strInfo.IsEmpty())
	{
		int n = strInfo.Find('#');
		if(n==-1)
			break;
		strTmp = strInfo.Left(n);
		player_number=(_ttoi(strTmp.Left(1))+4-number_change)%4;//玩家视角永远为0
		strTmp=strTmp.Mid(1);
		switch(player_number)
		{
		case 1:
			{
				((CEdit*)GetDlgItem(IDC_1_Name))->ReplaceSel(strTmp);
				break;
			}
		case 2:
			{
				((CEdit*)GetDlgItem(IDC_2_Name))->ReplaceSel(strTmp);
				break;
			}
		case 3:
			{
				((CEdit*)GetDlgItem(IDC_3_Name))->ReplaceSel(strTmp);
				break;
			}

		default: break;

		}
		strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	}
}


void CguandanClientDlg::OnLbnSelchange0Handcards()
{
	// TODO: 在此添加控件通知处理程序代码
}
