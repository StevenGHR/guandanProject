
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
		AfxMessageBox(_T("�����������������䣡����"));
		return;
	}
	CClientSocket * client(0);
	client = new CClientSocket(&m_listSockets);
	if (!client)
	{
		AfxMessageBox(_T("�ڴ治��,�ͻ����ӷ�����ʧ�ܣ�"));
		return;
	}
	client->player_number=number;
	number=(number+1)%4;
	Accept(*client);
	//��ӵ�ĩβ
	m_listSockets.AddTail(client);
	CSocket::OnAccept(nErrorCode);
}