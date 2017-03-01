#pragma once
#include "stdafx.h"
#include <vector>

#include "Card.h"
#include "ClientSocket.h"
using namespace std;
class CClientSocket;
class Deck
{
public:
	/*void fill();*/
	void empty();
	int count() const;
	void sort();

	//vector<Card> getCards(){return cards;};
	bool push(Card card);
	bool pop(Card &card);
	void pop(vector<Card> card);
	bool contain(Card card);
	bool contain(vector<Card> card);
	/*bool shuffle();

	void deal(CClientSocket & p1,CClientSocket & p2,CClientSocket & p3,CClientSocket & p4);*/

	/*void debugRemoveCard(Card card);
	void debugPushCards(const std::vector<Card> *cardsvec);*/
	int get_cards_length();
	char * convert_to_Char();
	void convert_to_card(char * buff,int len);
public:
	vector<Card> cards;
};
