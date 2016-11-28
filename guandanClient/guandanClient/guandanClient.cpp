
// guandanClient.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "guandanClient.h"
#include "guandanClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CguandanClientApp

BEGIN_MESSAGE_MAP(CguandanClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CguandanClientApp ����

CguandanClientApp::CguandanClientApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CguandanClientApp ����

CguandanClientApp theApp;


// CguandanClientApp ��ʼ��

BOOL CguandanClientApp::InitInstance()
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
	
	//��ʼ��Socket
	if(!AfxSocketInit())
	{
		AfxMessageBox(_T("��ʼ��Socket��ʧ�ܣ�"));
		return false;
	}

	m_pSocket = new CClientSocket();
	if(!m_pSocket)
	{
		AfxMessageBox(_T("�ڴ治�㣡"));
		return false;
	}

	if(!m_pSocket->Create())
	{
		AfxMessageBox(_T("�����׽���ʧ�ܣ�"));
		return false;
	}

	CLogoInDlg* pLogoinDlg;
	pLogoinDlg = new CLogoInDlg();
	
	if(pLogoinDlg->DoModal()==IDOK)
	{
		//����¼
		delete pLogoinDlg;
		m_pSocket->Close();
		return false;
	}
	else
	{
		delete pLogoinDlg;
	}

	CguandanClientDlg dlg;
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

int CguandanClientApp::ExitInstance()
{
	if(m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}

	return CWinApp::ExitInstance();
}

CClientSocket* CguandanClientApp::GetMainSocket() const
{
	return m_pSocket;
}
