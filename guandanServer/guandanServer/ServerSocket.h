#pragma once

#include "ClientSocket.h"

class CServerSocket : public CSocket
{
public:
	int number;
	CServerSocket();
	virtual ~CServerSocket();
public : 

	CPtrList m_listSockets;//������������������пͻ������ӳɹ����Socket


public : 
	virtual void OnAccept(int nErrorCode);
};