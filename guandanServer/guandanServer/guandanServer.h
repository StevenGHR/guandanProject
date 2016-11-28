
// guandanServer.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "ServerSocket.h"


// CguandanServerApp:
// 有关此类的实现，请参阅 guandanServer.cpp
//

class CguandanServerApp : public CWinApp
{
public:
	CguandanServerApp();

// 重写
private:
	CServerSocket* m_iSocket;//服务器Socket
	// 重写
public:
	virtual BOOL InitInstance();
	// 实现
	CServerSocket* GetServerSocket() const;
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CguandanServerApp theApp;