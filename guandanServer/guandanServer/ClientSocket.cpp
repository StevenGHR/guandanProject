
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
	//����Ϣ����
	//�ȵõ���Ϣͷ
	HEADER head;
	int nlen = sizeof HEADER;
	char *pHead = NULL;
	pHead = new char[nlen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnReceive �ڴ治�㣡");
		return;
	}
	memset(pHead,0, sizeof(char)*nlen );
	Receive(pHead,nlen);
	head.type = ((LPHEADER)pHead)->type;
	head.nContentLen = ((LPHEADER)pHead)->nContentLen;
	delete pHead;
	pHead = NULL;

	//�ٴν���,�������������
	pHead = new char[head.nContentLen];
	if(!pHead)
	{
		TRACE0("CClientSocket::OnRecive �ڴ治�㣡");
		return;
	}
	if( Receive(pHead, head.nContentLen)!=head.nContentLen)
	{
		AfxMessageBox(_T("������������"));
		delete pHead;
		return;
	}
	////////////������Ϣ���ͣ���������////////////////////
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

//�ر�����
void CClientSocket::OnClose(int nErrorCode)
{
	CTime time; 
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d  %H:%M:%S  ");
	strTime = strTime + this->m_strName + _T("  �뿪...\r\n");
	((CguandanServerDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_pList->RemoveAt(m_pList->Find(this));
	//���ķ�������������
	CString str1 = this->UpdateServerLog();
	//֪ͨ�ͻ���ˢ����������
	this->UpdateAllUser(str1);
	this->Close();
	//���ٸ��׽���
	delete this;
	CSocket::OnClose(nErrorCode);
}

//��¼
void CClientSocket::OnLogoIN(char* buff, int nlen)
{
	//������������֤
	CTime time; 
	time = CTime::GetCurrentTime();
	CString strTime = time.Format("%Y-%m-%d %H:%M:%S  ");

	CString strTemp(buff);
	strTime = strTime + strTemp + _T("  ��¼...\r\n");
	//��¼��־
	((CguandanServerDlg*)theApp.GetMainWnd())->DisplayLog(strTime);
	m_strName = strTemp;
	//���·����б�
	CString str1 = this->UpdateServerLog();
	//�����������пͷ���
	this->UpdateAllUser(str1);
	//��֪���
	//HEADER head;
	//head.type=MSG_PLAYERINFO;
	////head.number=player_number;
	//this->Send(&head,sizeof(HEADER));
	//this->Send(buff,nlen);

}

//ת����Ϣ
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


//�������������û�
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
		AfxMessageBox(_T("�ַ�ת��ʧ��"));
		delete pSend;
		return;
	}
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		//����Э��ͷ
		pTemp->Send((char*)&_head, sizeof(_head));
		pTemp->Send(pSend,_head.nContentLen );
	}	

	delete pSend;

}

//���·�������������  
// ���������û��б��String
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
			if(pTemp->m_ready)//��׼���������ظ����
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
	//��¼��־
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
	//�����������пͷ���
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
	//�����������
	NameSend();

	//����˳��
	CString ptemp;
	for (int i=0;i<4;i++)
	{
		if (player[i]->player_number==0)
		{
			player[i]->action=CClientSocket::turn;
			ptemp=player[i]->m_strName+_T("  �ȳ�������#");
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
	showcards->empty();//���
	showcards->convert_to_card(buff,nlen);//ת��Ϊcard
	
	if (!gamelogic->GetCardInfo(showcards))//�õ�������Ϣ���Ƿ�Ϊ������
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
	if (actionflag)//�����
	{
		Playcards(showcards);
	}
	//�ƾ��ж�
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

	//�¼ҳ�
	int plnum=(player_number+1)%4;
	ps = m_pList->GetHeadPosition();
	CClientSocket* player[4];
	for(int i=0;ps!=NULL;i++)
	{
		player[i] = (CClientSocket*)m_pList->GetNext(ps);
		if (player[i]->player_number==plnum)//�¼�
		{
			player[i]->action=CClientSocket::turn;
		}
	}


}

void CClientSocket::PlayerPass()
{
	CString info=this->m_strName+_T("  ��Ҫ...\r\n");
	UpdateAllUser(info);
	this->action=CClientSocket::Pass;
	//�¼ҳ�
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
		CString ptemp=m_strName+_T(" �Ѿ����ꡣ����");
		UpdateAllUser(ptemp);

		POSITION ps = m_pList->GetHeadPosition();
		CClientSocket* player[4];
		for(int i=0;ps!=NULL;i++)
		{
			player[i] = (CClientSocket*)m_pList->GetNext(ps);
		}

		//��������
		int maxplace=rankplace;
		for(int i=0;i<4;i++)
		{
			if (maxplace<player[i]->rankplace)
			{
				maxplace=player[i]->rankplace;
			}
		}
		rankplace=maxplace+1;
		
		//�ж��Ƿ����
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
	CString str=_T("���ֽ���������");
	HEADER _head;
	_head.type = MSG_END;
	_head.nContentLen = str.GetLength()+1;
	char *pSend = new char[_head.nContentLen];
	memset(pSend, 0, _head.nContentLen*sizeof(char));
	if( !WChar2MByte(str.GetBuffer(0), pSend, _head.nContentLen))
	{
		AfxMessageBox(_T("�ַ�ת��ʧ��"));
		delete pSend;
		return;
	}
	POSITION ps = m_pList->GetHeadPosition();
	while(ps!=NULL)
	{
		CClientSocket* pTemp = (CClientSocket*)m_pList->GetNext(ps);
		//����Э��ͷ
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