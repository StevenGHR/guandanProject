#pragma once

#include "stdafx.h"
#include "Deck.h"
#define HandcardsNumber 27
class Deck;
class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();

public:
	Deck * handcards;
	Deck * showcards;
public:
	virtual void OnReceive(int nErrorCode);
	BOOL SendMSG(LPSTR lpBuff, int nlen);
	BOOL LogoIn(LPSTR lpBuff, int nlen);
	BOOL Ready(LPSTR lpBuff, int nlen);
	char * Sort(char * lpBuff, int nlen);
	CString m_strUserName;
};


