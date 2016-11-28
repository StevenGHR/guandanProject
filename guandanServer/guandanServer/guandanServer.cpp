
// guandanServer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "guandanServer.h"
#include "guandanServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguandanServerApp

BEGIN_MESSAGE_MAP(CguandanServerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CguandanServerApp ����

CguandanServerApp::CguandanServerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CguandanServerApp ����

CguandanServerApp theApp;


// CguandanServerApp ��ʼ��

BOOL CguandanServerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//��ʼ��winSock��
	WSAData wsData;
	if(!AfxSocketInit(&wsData))
	{
		AfxMessageBox(_T("Socket ���ʼ������"));
		return false;
	}

	//������������Socket������TCP
	m_iSocket = new CServerSocket();
	if(!m_iSocket)
	{
		AfxMessageBox(_T("��̬�����������׽��ֳ���"));
		return false;
	}
	if(!m_iSocket->Create(8989))
	{
		AfxMessageBox(_T("�����׽��ִ���"));
		m_iSocket->Close();
		return false;
	}

	if(!m_iSocket->Listen())
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
		m_iSocket->Close();
		return false;
	}

	CguandanServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


int CguandanServerApp::ExitInstance()
{
	if(m_iSocket)
	{
		delete m_iSocket;
		m_iSocket = NULL;
	}

	return CWinApp::ExitInstance();
}


CServerSocket* CguandanServerApp::GetServerSocket() const
{
	ASSERT(m_iSocket);
	return m_iSocket;
}