
// NetChatClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "LogoInDlg.h"
#include "ClientSocket.h"

class CguandanClientApp : public CWinApp
{
public:
	CguandanClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	DECLARE_MESSAGE_MAP()
public: 
	CClientSocket* GetMainSocket() const;
private:
	CClientSocket* m_pSocket;

	
public:
	virtual int ExitInstance();
};

extern CguandanClientApp theApp;