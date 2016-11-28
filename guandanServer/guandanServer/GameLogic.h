#pragma once

#include <vector>
#include "Deck.h"
#include "GameState.h"
using namespace std;
class Deck;
class GameLogic
{
public:

	typedef enum {
		SingleCard=0,
		Pair,
		ThreeOfAKind,//3уе
		DoubleThree,//3+3
		ThreeWithTwo,//3+2
		ThreeOfPair,//2+2+2
		Straight,
		Bomb,
		Flush,

		none

	} Ranking;

	GameLogic();
	GameLogic(Ranking rk,Card cd);

	int getChangecard_count(const Deck * deck);

	bool IsSingleCard(const Deck * deck);
	bool IsPair(const Deck * deck);
	bool IsThreeOfAKind(const Deck * deck);
	bool IsDoubleThree(const Deck * deck);
	bool IsThreeWithTwo(const Deck * deck);
	bool IsThreeOfPair(const Deck * deck);
	bool IsStraight(const Deck * deck);
	bool IsBomb(const Deck * deck);
	bool IsFlush(const Deck * deck);

	bool GetCardInfo(const Deck * deck);

	bool Is_Legal(GameLogic A);

	GameLogic::Ranking getRanking(){return ranking;};
	int getMaxcard(){return maxcard;};
	int getBomb_count(){return bomb_count;};
	void setRanking(GameLogic::Ranking rk){ranking=rk;};
	void setMaxcard(int value){maxcard=value;};
	void setBomb_count(int count){bomb_count=count;};
	void reset();
private:
	Ranking ranking;
	int maxcard;
	int bomb_count;
};