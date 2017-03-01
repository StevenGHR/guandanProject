
// guandanClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "guandanClient.h"
#include "guandanClientDlg.h"
#include "Deck.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CNetChatClientDlg �Ի���




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
	DDX_Text(pDX, IDC_CardShow, m_showedcards);
	DDX_Text(pDX, IDC_1_Name, name_1);
	DDX_Text(pDX, IDC_2_Name, name_2);
	DDX_Text(pDX, IDC_3_Name, name_3);
	DDX_Text(pDX, IDC_0_Showcards, m_showcards);
	DDX_Text(pDX, IDC_1_Showcards, showcards_1);
	DDX_Text(pDX, IDC_2_Showcards, showcards_2);
	DDX_Text(pDX, IDC_3_Showcards, showcards_3);

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


// CNetChatClientDlg ��Ϣ�������

BOOL CguandanClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CguandanClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CguandanClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CguandanClientDlg::OnBnClickedBtnSend()
{
	//������Ϣ
	UpdateData();
	if(m_strSend.IsEmpty())
	{
		AfxMessageBox(_T("�������ݲ���Ϊ�գ�"));
		return ;
	}

	CString temp ;
	CTime time = CTime::GetCurrentTime();
	temp = time.Format("%H:%M:%S");
	//���� +_T("\n\t") ʱ��
	m_strSend = theApp.GetMainSocket()->m_strUserName+_T("  ") + temp +_T("\r\n   ") + m_strSend +_T("\r\n");

	char* pBuff = new char[m_strSend.GetLength()*2];
	memset(pBuff, 0, m_strSend.GetLength()*2);
	//ת��Ϊ���ֽ�
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
	//�˳�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	char* pBuff = new char[m_showedcards.GetLength()+1];
	memset(pBuff, 0, m_showedcards.GetLength()+1);
	//ת��Ϊ���ֽ�
	WChar2MByte(m_showedcards.GetBuffer(0), pBuff, m_showedcards.GetLength()+1);

	Deck * show=new Deck;
	show->convert_to_card(pBuff,m_showedcards.GetLength());

	if(m_showedcards.IsEmpty()||!theApp.GetMainSocket()->handcards->contain(show->cards))
	{
		AfxMessageBox(_T("��������ȷ���ƣ�"));
		return ;
	}
	theApp.GetMainSocket()->SendCards(pBuff, m_showedcards.GetLength());

	delete pBuff,show;

	m_showedcards.Empty();
	UpdateData(0);
}


void CguandanClientDlg::OnBnClickedBtnReady()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//������Ϣ
	UpdateData();

	CString temp,msg ;
	CTime time = CTime::GetCurrentTime();
	temp = time.Format("%H:%M:%S");
	//���� +_T("\n\t") ʱ��
	msg = theApp.GetMainSocket()->m_strUserName+_T("  ") + temp +_T("\r\n   ") + _T("��׼��������") +_T("\r\n");
	
	char* pBuff = new char[msg.GetLength()*2];
	memset(pBuff, 0, msg.GetLength()*2);
	//ת��Ϊ���ֽ�
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
		player_number=(_ttoi(strTmp.Left(1))+4-number_change)%4;//����ӽ���ԶΪ0
		strTmp=strTmp.Mid(1);
		switch(player_number)
		{
		case 1:
			{
				name_1=strTmp;
				break;
			}
		case 2:
			{
				name_2=strTmp;
				break;
			}
		case 3:
			{
				name_3=strTmp;
				break;
			}

		default: break;

		}
		strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	}
	UpdateData(0);
}

void CguandanClientDlg::UpdateShowcards(CString strInfo,CString myname)
{
	UpdateData();
	CString strTmp;

	int n = strInfo.Find('#');
	strTmp = strInfo.Left(n);
	strInfo = strInfo.Right(strInfo.GetLength()-n-1);
	if(myname==strTmp)
	{
		m_showcards+=strInfo;
	}
	if(name_1==strTmp)
	{
		showcards_1+=strInfo;
	}
	if(name_2==strTmp)
	{
		showcards_2+=strInfo;
	}
	if(name_3==strTmp)
	{
		showcards_3+=strInfo;
	}
	UpdateData(0);

	//��������handcards
	char * temp=new char[strInfo.GetLength()*2];
	WChar2MByte(strInfo.GetBuffer(0),temp,strInfo.GetLength()*2);
	Deck * showtemp=new Deck();
	showtemp->convert_to_card(temp,strInfo.GetLength());
	theApp.GetMainSocket()->handcards->pop(showtemp->cards);
	//��ʾ
	CString handcards_temp(theApp.GetMainSocket()->handcards->convert_to_Char());
	UpdateHandcards(handcards_temp);
	delete temp,showtemp;
}

void CguandanClientDlg::OnLbnSelchange0Handcards()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
