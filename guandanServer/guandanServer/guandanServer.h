
// guandanServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "ServerSocket.h"


// CguandanServerApp:
// �йش����ʵ�֣������ guandanServer.cpp
//

class CguandanServerApp : public CWinApp
{
public:
	CguandanServerApp();

// ��д
private:
	CServerSocket* m_iSocket;//������Socket
	// ��д
public:
	virtual BOOL InitInstance();
	// ʵ��
	CServerSocket* GetServerSocket() const;
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CguandanServerApp theApp;