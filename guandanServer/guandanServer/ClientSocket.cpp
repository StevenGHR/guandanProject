
#include "stdafx.h"
#include "guandanServer.h"
#include "ClientSocket.h"
#include "Header.h"
#include "guandanServerDlg.h"

CClientSocket::CClientSocket(CPtrList* pList)
	:m_pList(pList),m_strName(_T(""))
{
	goal=0;
	rankplace=0;
	m_ready=false;
	handcards=new Deck[HandcardsNumber];
	showcards=new Deck[HandcardsNumber];
}

CClientSocket::~CClientSocket()
{
	delete [] handcards;
	delete [] showcards;
}

/////////////////////////////////////////////////////////////////////
void CClientSocket::OnReceive(int nErrorCode)
{
	//有消息接收
	//先得到信息头
	HEADER head;
	int nlen = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive 内存不足！");
		return;
	}
	memset(pHead,0, sizeof(char)*nlen );
	Receive(pHead,nlen);
	head.type = ((LPHEADER)pHead)->type;
	head.nContentLen = ((LPHEADER)pHead)->nContentLen;
	delete pHead;
	pHead = NULL;

	//再次接收,这次是数据类容
	pHead = new char[head.nContentLen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnRecive 内存不足！");
		return;
	}
	if( Receive(pHead, head.nContentLen)!=head.nContentLen)
	{
		AfxMessageBox(_T("接收数据有误！"));
		delete pHead;
		return;
	}
	////////////根据消息类型，处理数据////////////////////
	switch(head.type)
	{
	case MSG_LOGOIN: 
		OnLogoIN(pHead, head.nContentLen);
		break;
	case MSG_SEND: 
		OnMSGTranslate(pHead, head.nContentLen);
		break;
	case MSG_READY:
		OnReady();
		break;
	case MSG_CARDINFO:
		JudgeShowCards(pHead,head.nContentLen);
		break;
	case MSG_PASS:
		PlayerPass();
		break;
	default : break;
	}

	delete pHead;
	CSocket::OnReceive(nErrorCode);
}

//关闭连接
void CClientSocket::OnClose(int nErrorCode)
{
	CTime time; 
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d  %H:%M:%S  ");
	strTime = strTime + this->m_strName + _T("  离开...\r\n");
	((CguandanServerDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_pList->RemoveAt(m_pList->Find(this));
	//更改服务器在线名单
	CString str1 = this->UpdateServerLog();
	//通知客户端刷新在线名单
	this->UpdateAllUser(str1);
	this->Close();
	//销毁该套接字
	delete this;
	CSocket::OnClose(nErrorCode);
}

//登录
void CClientSocket::OnLogoIN(char* buff, int nlen)
{
	//可以添加身份认证
	CTime time; 
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S  ");

	CString strTemp(buff);
	strTime = strTime + strTemp + _T("  登录...\r\n");
	//记录日志
	((CguandanServerDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_strName = strTemp;
	//更新服务列表
	CString str1 = this->UpdateServerLog();
	//更新在线所有客服端
	this->UpdateAllUser(str1);
	//告知编号
	//HEADER head;
	//head.type=MSG_PLAYERINFO;
	////head.number=player_number;
	//this->Send(&head,sizeof(HEADER));
	//this->Send(buff,nlen);

}

//转发消息
void CClientSocket::OnMSGTranslate(char* buff, int nlen)
{
	HEADER head;
	head.type = MSG_SEND;
	head.nContentLen = nlen;
	POSITION ps = m_pList->GetHeadPosition();

	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		pTemp->Send(&head,sizeof(HEADER));
		pTemp->Send(buff, nlen);
	}
}


BOOL CClientSocket::WChar2MByte(LPCWSTR lpSrc, LPSTR lpDest, int nlen)
{
	int n = 0;
	n = WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, 0, 0, FALSE);
	if(nlen<n)
		return FALSE;
	WideCharToMultiByte(CP_OEMCP, 0, lpSrc, -1, lpDest, nlen, 0, FALSE);
	return TRUE;
}


//跟新所有在线用户
void CClientSocket::UpdateAllUser(CString strUserInfo,CString  type)
{
	HEADER _head;
	if(type==_T("Ready"))
	{
		_head.type = MSG_READY;
	}
	else
		_head.type = MSG_UPDATE;
	_head.nContentLen = strUserInfo.GetLength()*4;
	char *pSend = new char[_head.nContentLen];
	memset(pSend, 0, _head.nContentLen);
	if( !WChar2MByte(strUserInfo.GetBuffer(0), pSend, _head.nContentLen))
	{
		AfxMessageBox(_T("字符转换失败"));
		delete pSend;
		return;
	}
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		//发送协议头
		pTemp->Send((char*)&_head, sizeof(_head));
		pTemp->Send(pSend,_head.nContentLen );
	}	

	delete pSend;

}

//跟新服务器在线名单  
// 返回在线用户列表的String
CString CClientSocket::UpdateServerLog()
{
	CString strUserInfo = _T("");

	POSITION ps = m_pList->GetHeadPosition();

	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		strUserInfo += pTemp->m_strName + _T("#");
	}
	((CguandanServerDlg*)theApp.GetMainWnd())->UpdateUserInfo(strUserInfo);

	return strUserInfo;
}


void CClientSocket::OnReady()
{
	bool ready[4]={false};
	int i=0;
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		if (pTemp->m_strName==this->m_strName)
		{
			if(pTemp->m_ready)//已准备，对于重复点击
			{
				return;
			}
			else
			{
				pTemp->m_ready=true;
			}
		}
		ready[i++]=pTemp->m_ready;
	}	

	if (ready[0]&&ready[1]&&ready[2]&&ready[3])
	{
		Deal();
	}
	CString strTime = this->m_strName + _T("  is  Ready! \r\n");
	//记录日志
	((CguandanServerDlg*)theApp.GetMainWnd())->DisplayLog(strTime);

	CString strUserInfo = _T("");
	ps = m_pList->GetHeadPosition();

	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		if(pTemp->m_ready&&pTemp->player_number!=this->player_number)
		{
			strUserInfo+=pTemp->m_strName + _T("  is  Ready!")+_T("# \n");
		}
	}
	strUserInfo+=strTime+ _T("#");
	//更新在线所有客服端
	this->UpdateAllUser(strUserInfo,_T("Ready"));
}

void CClientSocket::Deal()
{
	Deck deck;
	POSITION ps = m_pList->GetHeadPosition();
	CClientSocket * player[4];
	for(int i=0;ps!=NULL;i++)
	{
		player[i] = (CClientSocket*)m_pList->GetNext(ps);
	}
	deck.deal(*player[0],*player[1],*player[2],*player[3]);

	HEADER _head;
	_head.type = MSG_HANDCARDS;
	char * pSend;
	for (int i=0;i<4;i++)
	{
		_head.nContentLen = player[i]->handcards->get_cards_length()+1;

	    pSend=new char[_head.nContentLen];
		memset(pSend,0,_head.nContentLen);
		CString temp(player[i]->handcards->convert_to_Char());
		WChar2MByte(temp.GetBuffer(0),pSend,_head.nContentLen);

		player[i]->Send((char*)&_head, sizeof(_head));
		player[i]->Send(pSend,_head.nContentLen);

		memset(pSend,0,_head.nContentLen);
	}
	//发送玩家姓名
	NameSend();

	//出牌顺序
	CString ptemp;
	for (int i=0;i<4;i++)
	{
		if (player[i]->player_number==0)
		{
			player[i]->action=CClientSocket::turn;
			ptemp=player[i]->m_strName+_T("  先出。。。#");
			break;
		}
	}
	UpdateAllUser(ptemp,_T("Ready"));
}

void CClientSocket::NameSend()
{
	CString temp,strInfo;
	POSITION ps = m_pList->GetHeadPosition();
	CClientSocket* player[4];
	for(int i=0;ps!=NULL;i++)
	{
		player[i] = (CClientSocket*)m_pList->GetNext(ps);
		temp.Format(_T("%d"),player[i]->player_number);
		strInfo+=temp+player[i]->m_strName+_T("#");
	}
	HEADER _head;
	_head.type = MSG_USERNAME;
	char * pSend;
	_head.nContentLen = strInfo.GetLength()*4;
	pSend=new char[_head.nContentLen];
	memset(pSend,0,_head.nContentLen);
	WChar2MByte(strInfo.GetBuffer(0),pSend,_head.nContentLen);
	for (int i=0;i<4;i++)
	{
		player[i]->Send((char*)&_head, sizeof(_head));
		player[i]->Send(pSend,_head.nContentLen);
	}
	delete pSend;
}

void CClientSocket::JudgeShowCards(char * buff,int nlen)
{
	if (this->action!=turn)
	{
		return;
	}
	showcards->empty();//清空
	showcards->convert_to_card(buff,nlen);//转换为card
	
	if (!gamelogic->GetCardInfo(showcards))//得到牌型信息，是否为规则牌
	{
		return ;
	}
	//
	POSITION ps = m_pList->GetHeadPosition();
	CClientSocket* player[4];
	for(int i=0;ps!=NULL;i++)
	{
		player[i] = (CClientSocket*)m_pList->GetNext(ps);
	}
	bool actionflag=true;
	for (int i=player_number;i!=player_number;i--)
	{
		if (i<0)
		{
			i=3;
		}
		if (player[i]->action==CClientSocket::Hand)
		{
			actionflag=false;
			if (gamelogic->Is_Legal((*player[i]->gamelogic)))
			{
				Playcards(showcards);
			}
			break;
		}
	}
	if (actionflag)//任意出
	{
		Playcards(showcards);
	}
	//牌局判断
	Gamestate_judgement();
}

void CClientSocket::Playcards(Deck * scards)
{
	handcards->pop(scards->cards);
	action=CClientSocket::Hand;
	//
	HEADER head;
	head.type=MSG_CARDINFO;
	head.nContentLen=scards->get_cards_length();
	//head.number=player_number;
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		pTemp->Send((char*)&head, sizeof(head));
		pTemp->Send(scards->convert_to_Char(),head.nContentLen);
	}

	//下家出
	int plnum=(player_number+1)%4;
	ps = m_pList->GetHeadPosition();
	CClientSocket* player[4];
	for(int i=0;ps!=NULL;i++)
	{
		player[i] = (CClientSocket*)m_pList->GetNext(ps);
		if (player[i]->player_number==plnum)//下家
		{
			player[i]->action=CClientSocket::turn;
		}
	}


}

void CClientSocket::PlayerPass()
{
	CString info=this->m_strName+_T("  不要...\r\n");
	UpdateAllUser(info);
	this->action=CClientSocket::Pass;
	//下家出
	int playerturn=player_number+1;
	if (playerturn==4)
	{
		playerturn=0;
		POSITION ps = m_pList->GetHeadPosition();
		while(ps!=NULL)
		{
			CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
			if (pTemp->player_number==playerturn)
			{
				pTemp->action=turn;
				break;
			}
		}
	}
}

void CClientSocket::Gamestate_judgement()
{
	if (handcards->cards.size()==0)
	{
		action=CClientSocket::None;
		CString ptemp=m_strName+_T(" 已经出完。。。");
		UpdateAllUser(ptemp);

		POSITION ps = m_pList->GetHeadPosition();
		CClientSocket* player[4];
		for(int i=0;ps!=NULL;i++)
		{
			player[i] = (CClientSocket*)m_pList->GetNext(ps);
		}

		//设置名次
		int maxplace=rankplace;
		for(int i=0;i<4;i++)
		{
			if (maxplace<player[i]->rankplace)
			{
				maxplace=player[i]->rankplace;
			}
		}
		rankplace=maxplace+1;
		
		//判断是否结束
		int partner=(player_number+2)%4;
		for(int i=0;i<4;i++)
		{
			if (player[i]->player_number==partner)
			{
				if (player[i]->rankplace+rankplace==3)
				{
					goal+=3;
					player[i]->goal+=3;
					OnEnd();
				}
				else if (player[i]->rankplace+rankplace==4)
				{
					goal+=2;
					player[i]->goal+=2;
					OnEnd();
				}
				else
				{
					if (rankplace==1)
					{
						goal+=2;
						player[i]->goal+=2;
						OnEnd();
					}
				}
			}
		}
	}
}

void CClientSocket::OnEnd()
{
	CString str=_T("本局结束。。。");
	HEADER _head;
	_head.type = MSG_END;
	_head.nContentLen = str.GetLength()+1;
	char *pSend = new char[_head.nContentLen];
	memset(pSend, 0, _head.nContentLen*sizeof(char));
	if( !WChar2MByte(str.GetBuffer(0), pSend, _head.nContentLen))
	{
		AfxMessageBox(_T("字符转换失败"));
		delete pSend;
		return;
	}
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		//发送协议头
		pTemp->Send((char*)&_head, sizeof(_head));
		pTemp->Send(pSend,_head.nContentLen );
	}	

	delete pSend;

	UpdateAllUser(str);
}
//void CClientSocket::Display_handcards()
//{
//
//}