#pragma once

#include "stdafx.h"

class Card
{
public:
	typedef enum {
		Two=2,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace,

		trump,//主牌
		Black,//小王
		Red,//大王

		FirstFace=Two,
		LastFace=Ace
	} Face;

	typedef enum {
		Clubs=1,
		Diamonds,
		Hearts,
		Spades,//黑桃

		Joker,//王


		FirstSuit=Clubs,
		LastSuit=Spades
	} Suit;

	Card();
	Card(Suit s, Face f);
	Card(const char *str);

	void setValue(Suit s,Face f);
	void getValue(Suit *s,Face *f ) const;
	Face getFace() const { return face; };
	Suit getSuit() const { return suit; };


	char getFaceSymbol() const;
	char getSuitSymbol() const;
	const char* getName() const;

	bool operator <  (const Card &c) const { return (getFace() < c.getFace()); };
	bool operator >  (const Card &c) const { return (getFace() > c.getFace()); };
	bool operator == (const Card &c) const { return (getFace() == c.getFace()); };
	bool operator != (const Card &c) const { return (getFace() != c.getFace()); };
	void operator = (const Card &c) {face=c.getFace();suit=c.getSuit();};

	static Face convertFaceSymbol(char fsym);
	static Suit convertSuitSymbol(char ssym);
	void convertCardSymbol(char suit,char face);
private:
	Face face;
	Suit suit;
};