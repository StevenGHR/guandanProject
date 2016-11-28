
#include "stdafx.h"
#include "ServerSocket.h"

CServerSocket::CServerSocket()
{
	number=0;
	m_listSockets.RemoveAll();
}

CServerSocket::~CServerSocket()
{

}

void CServerSocket::OnAccept(int nErrorCode)
{
	if (m_listSockets.GetCount()==4)
	{
		AfxMessageBox(_T("人数已满，请另创房间！！！"));
		return;
	}
	CClientSocket * client(0);
	client = new CClientSocket(&m_listSockets);
	if (!client)
	{
		AfxMessageBox(_T("内存不足,客户连接服务器失败！"));
		return;
	}
	client->player_number=number;
	number=(number+1)%4;
	Accept(*client);
	//添加到末尾
	m_listSockets.AddTail(client);
	CSocket::OnAccept(nErrorCode);
}