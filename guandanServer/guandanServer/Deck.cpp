#include "stdafx.h"

#include "Deck.h"
#include <algorithm>
void Deck::fill()
{
	cards.clear();
	Card c;
	for(int i=1;i<=2;i++)
	{
		for (int f=Card::FirstFace; f <= Card::LastFace; f++)
		{
			for (int s=Card::FirstSuit; s <= Card::LastSuit; s++)
			{
				c.setValue((Card::Suit)s,(Card::Face)f );
				push(c);
			}
		}
		c.setValue((Card::Suit)5,(Card::Face)16 );
		push(c);
		c.setValue((Card::Suit)5,(Card::Face)17);
		push(c);
	}


}

void Deck::empty()
{
	cards.clear();
}

int Deck::count() const
{
	return cards.size();
}

bool Deck::push(Card card)
{
	cards.push_back(card);
	return true;
}

bool Deck::pop(Card &card)
{
	if (!count())
		return false;

	card = cards.back();
	cards.pop_back();
	return true;
}

void Deck::pop(vector<Card> card)
{
	for (vector<Card>::iterator it=card.begin();it!=card.end();++it)
	{
		for (vector<Card>::iterator hand=cards.begin();hand!=cards.end();++hand)
		{
			if (*it==(*hand)&&(*it).getSuit()==(*hand).getSuit())
			{
				cards.erase(hand);
			}
		}
	}
}

bool Deck::shuffle()
{
	random_shuffle(cards.begin(), cards.end());
	return true;
}

void Deck::deal(CClientSocket & p1,CClientSocket & p2,CClientSocket & p3,CClientSocket & p4)
{
	this->fill();
	this->shuffle();
	for (unsigned int i=0;i<cards.size();i++)
	{
		(*p1.handcards).push(cards[i]);
		(*p2.handcards).push(cards[++i]);
		(*p3.handcards).push(cards[++i]);
		(*p4.handcards).push(cards[++i]);
	}
}
int Deck::get_cards_length()
{
	return cards.size()*2;
}
char * Deck::convert_to_Char()
{
	int i,j;
	int n=sizeof(cards)/sizeof(char);
	char * cardchar =new char[get_cards_length()+1];
	memset(cardchar,0,get_cards_length());
	for(i=0,j=0;i<cards.size();i++,j++)
	{
		cardchar[j]=cards[i].getSuitSymbol();
		cardchar[++j]=cards[i].getFaceSymbol();
	}
	cardchar[j]='\0';
	return cardchar;
}

void Deck::convert_to_card(char * buff,int len)
{
	Card card;
	for (int i=0;i<len;i+=2)
	{
		card.convertCardSymbol(buff[i],buff[i+1]);
		cards.push_back(card);
	}
}
//void Deck::debugRemoveCard(Card card)
//{
//	for (vector<Card>::iterator e = cards.begin(); e != cards.end(); e++)
//	{
//		if (e->getFace() == card.getFace() && e->getSuit() == card.getSuit()) {
//			cards.erase(e);
//			break;
//		}
//	}
//}
//
//void Deck::debugPushCards(const vector<Card> *cardsvec)
//{
//	for (vector<Card>::const_iterator e = cardsvec->begin(); e != cardsvec->end(); e++)
//		push(*e);
//}