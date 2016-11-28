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
	CPtrList* m_pList;//保存服务器Socket中List的东西
	CString m_strName; //连接名称
	int player_number;
	bool m_ready;//准备
	Deck * handcards;
	Deck * showcards;
	PlayerAction action;
	GameLogic * gamelogic;
	int rankplace;//名次
	double goal;//得分
	


public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	void OnLogoIN(char* buff,int nlen);
	void OnMSGTranslate(char* buff,int nlen);
	void OnReady();//准备
	void Deal();//发牌
	void NameSend();//玩家名发送
	void JudgeShowCards(char * buff,int nlen);
	void Playcards(Deck * scards);//出牌
	void PlayerPass();//过牌
	void Gamestate_judgement();
	void OnEnd();
	CString UpdateServerLog();
	void UpdateAllUser(CString strUserInfo,CString type=_T(""));
	//void Display_handcards();

private:
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen);
};