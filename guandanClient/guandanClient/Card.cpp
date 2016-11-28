#include "stdafx.h"
#include "Card.h"


static const char face_symbols[] = {
	'2', '3', '4', '5', '6', '7', '8', '9',
	'T', 'J', 'Q', 'K', 'A','t','B','R'
};

static const char suit_symbols[] = {
	'c', 'd', 'h', 's','j'
};


Card::Card()
{
	face = Card::FirstFace;
	suit = Card::FirstSuit;
}

Card::Card(Suit s,Face f )
{
	face = f;
	suit = s;
}

Card::Card(const char *str)
{
	suit = convertSuitSymbol(str[0]);
	face = convertFaceSymbol(str[1]);
}

void Card::setValue(Suit s, Face f)
{
	face = f;
	suit = s;
}

void Card::getValue(Suit *s, Face *f) const
{
	if (f)
		*f = face;

	if (s)
		*s = suit;
}

char Card::getFaceSymbol() const
{	
	return face_symbols[face - Card::FirstFace];
}

char Card::getSuitSymbol() const
{
	return suit_symbols[suit - Card::FirstSuit];
}

const char* Card::getName() const
{
	static char card_name[2];

	card_name[0] = getSuitSymbol();
	card_name[1] = getFaceSymbol();

	return card_name;
}

Card::Face Card::convertFaceSymbol(char fsym)
{
	for (unsigned int i=Card::FirstFace; i <= Card::Red; i++)
		if (fsym == face_symbols[i - Card::FirstFace])
			return (Card::Face)i;

	return Card::FirstFace;
}

Card::Suit Card::convertSuitSymbol(char ssym)
{
	for (unsigned int i=Card::FirstSuit; i <= Card::Joker; i++)
		if (ssym == suit_symbols[i - Card::FirstSuit])
			return (Card::Suit)i;

	return Card::FirstSuit;
}

void Card::convertCardSymbol(char suit,char face)
{
	this->setValue(convertSuitSymbol(suit),convertFaceSymbol(face));
}