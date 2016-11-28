
// guandanServer.cpp : 定义应用程序的类行为。
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


// CguandanServerApp 构造

CguandanServerApp::CguandanServerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CguandanServerApp 对象

CguandanServerApp theApp;


// CguandanServerApp 初始化

BOOL CguandanServerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//初始化winSock库
	WSAData wsData;
	if(!AfxSocketInit(&wsData))
	{
		AfxMessageBox(_T("Socket 库初始化出错！"));
		return false;
	}

	//创建服务器端Socket、采用TCP
	m_iSocket = new CServerSocket();
	if(!m_iSocket)
	{
		AfxMessageBox(_T("动态创建服务器套接字出错！"));
		return false;
	}
	if(!m_iSocket->Create(8989))
	{
		AfxMessageBox(_T("创建套接字错误！"));
		m_iSocket->Close();
		return false;
	}

	if(!m_iSocket->Listen())
	{
		AfxMessageBox(_T("监听失败！"));
		m_iSocket->Close();
		return false;
	}

	CguandanServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
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