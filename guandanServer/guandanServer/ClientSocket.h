#pragma once

#include "stdafx.h"
#include "Deck.h"
#include "GameLogic.h"
#define HandcardsNumber 27
/*----------------------------------------*/
class GameLogic;
class Deck;
class CClientSocket : public CSocket
{
public:
	typedef enum {
		None,
		Pass,
		turn,
		Hand
	} PlayerAction;
public:
	CClientSocket(CPtrList* pList);
	virtual ~CClientSocket();
public:
	CPtrList* m_pList;//���������Socket��List�Ķ���
	CString m_strName; //��������
	int player_number;
	bool m_ready;//׼��
	Deck * handcards;
	Deck * showcards;
	PlayerAction action;
	GameLogic * gamelogic;
	int rankplace;//����
	double goal;//�÷�
	


public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void OnLogoIN(char* buff,int nlen);
	void OnMSGTranslate(char* buff,int nlen);
	void OnReady();//׼��
	void Deal();//����
	void NameSend();//���������
	void JudgeShowCards(char * buff,int nlen);
	void Playcards(Deck * scards);//����
	void PlayerPass();//����
	void Gamestate_judgement();
	void OnEnd();
	CString UpdateServerLog();
	void UpdateAllUser(CString strUserInfo,CString type=_T(""));
	//void Display_handcards();

private:
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);
};