// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "guandanClient.h"
#include "ClientSocket.h"
#include "Header.h"
#include "guandanClientDlg.h"
// CClientSocket

CClientSocket::CClientSocket()
	:m_strUserName(_T(""))
{
	handcards=new Deck[HandcardsNumber];
	showcards=new Deck[HandcardsNumber];
}

CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	//首先接受head头
	HEADER head ;
	char* pHead = NULL;
	pHead =  new char[sizeof(head)];
	memset(pHead, 0, sizeof(head));
	Receive(pHead, sizeof(head));

	head.type =((LPHEADER)pHead)->type;
	head.nContentLen = ((LPHEADER)pHead)->nContentLen;
	delete pHead;
	pHead = NULL;

	char* pBuff = NULL;
	pBuff = new char[head.nContentLen];
	if(!pBuff)
	{
		AfxMessageBox(_T("内存不足！"));
		return;
	}
	memset(pBuff, 0 , sizeof(char)*head.nContentLen);
	if(head.nContentLen!=Receive(pBuff, head.nContentLen))
	{
		AfxMessageBox(_T("收到数据有误！"));
		delete pBuff;
		return;
	}
	CString strText(pBuff);
	switch(head.type)
	{
	case MSG_UPDATE: 
		{
			CString strText(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateUserInfo(strText);
			break;
		}
	case MSG_READY:
		{ 
			//准备消息
			CString strText(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateReady(strText);
			break;
		}
	case MSG_SEND:
		{ 
			//显示接收到的消息
			CString str(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateText(str);
			break;
		}
	case MSG_HANDCARDS:
		{ 
			//显示接收到的消息
			CString str(Sort(pBuff,head.nContentLen));
			//CString str(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateHandcards(str);
			break;
		}
	case MSG_USERNAME:
		{
			CString str(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateUserName(str,this->m_strUserName);
			break;
		}
	case MSG_CARDINFO:
		{
			CString str(pBuff);
			((CguandanClientDlg*)(AfxGetApp()->GetMainWnd()))->UpdateShowcards(str,this->m_strUserName);
			break;
		}
	
	default: break;
	}

	delete pBuff;
	CSocket::OnReceive(nErrorCode);
}

BOOL CClientSocket::SendMSG(LPSTR lpBuff, int nlen)
{
	//生成协议头
	HEADER head;
	head.type = MSG_SEND;
	head.nContentLen = nlen;

	if(Send(&head, sizeof(HEADER))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	if(Send(lpBuff, nlen)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	 
	return  TRUE;
}

BOOL CClientSocket::LogoIn(LPSTR lpBuff, int nlen)
{
	HEADER _head;
	_head.type = MSG_LOGOIN;
	_head.nContentLen = nlen;
	int _nSnd= 0;
	if((_nSnd = Send((char*)&_head, sizeof(_head)))==SOCKET_ERROR)
		return false;
	if((_nSnd = Send(lpBuff, nlen))==SOCKET_ERROR)
		return false;

	return TRUE;
}

BOOL CClientSocket::Ready(LPSTR lpBuff, int nlen)
{
	HEADER _head;
	_head.type = MSG_READY;
	_head.nContentLen = nlen;
	int _nSnd= 0;
	if((_nSnd = Send((char*)&_head, sizeof(_head)))==SOCKET_ERROR)
		return false;
	if((_nSnd = Send(lpBuff, nlen))==SOCKET_ERROR)
		return false;

	return TRUE;
}

BOOL CClientSocket::SendCards(LPSTR lpBuff, int nlen)
{
	//生成协议头
	HEADER head;
	head.type = MSG_CARDINFO;
	head.nContentLen = nlen;

	if(Send(&head, sizeof(HEADER))==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	if(Send(lpBuff, nlen)==SOCKET_ERROR)
	{
		AfxMessageBox(_T("发送错误！"));
		return FALSE;
	};
	 
	return  TRUE;
}

char * CClientSocket::Sort(char * lpBuff, int nlen)
{
	handcards->convert_to_card(lpBuff,nlen-1);//包含‘\0’
	handcards->sort();
	return handcards->convert_to_Char();
}