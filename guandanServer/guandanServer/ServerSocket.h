#pragma once

#include "ClientSocket.h"

class CServerSocket : public CSocket
{
public:
	int number;
	CServerSocket();
	virtual ~CServerSocket();
public : 

	CPtrList m_listSockets;//用来保存服务器与所有客户端连接成功后的Socket


public : 
	virtual void OnAccept(int nErrorCode);
};