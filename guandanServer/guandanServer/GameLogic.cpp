#include "stdafx.h"

#include <algorithm>

#include "GameLogic.h"

using namespace std;

GameLogic::GameLogic()
{
	ranking=GameLogic::none;
	maxcard=0;
	bomb_count=0;
}

GameLogic::GameLogic(Ranking rk,Card cd)
{
	ranking=rk;
	maxcard=cd.getFace();
}

void GameLogic::reset()
{
	ranking=GameLogic::none;
	maxcard=0;
	bomb_count=0;
}

int GameLogic::getChangecard_count(const Deck * deck)
{
	int changecard_count=0;
	Card cc=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
	for (int i=4;i<6;i++)
	{
		if (deck->cards[i]==cc&&deck->cards[i].getSuit()==Card::Hearts)
		{
			changecard_count++;
		}
	}
	return changecard_count;
}
//---------------------------牌型判断------------------

bool GameLogic::IsSingleCard(const Deck * deck)
{
	return deck->cards.size()==1?true:false;
}

bool GameLogic::IsPair(const Deck * deck)
{
	if (deck->cards.size()==2)
	{
		if (deck->cards[0]==deck->cards[1])
		{
			return true;
		}
		else
		{
			Card cc=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
			if (deck->cards[1]==cc&&deck->cards[1].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
	}
	return false;
}

bool GameLogic::IsThreeOfAKind(const Deck * deck)
{
	if (deck->cards.size()==3)
	{
		if (deck->cards[0]==deck->cards[1]&&deck->cards[0]==deck->cards[3])
		{
			return true;
		}
		else
		{
			Card cc=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
			if (deck->cards[0]==deck->cards[1]&&deck->cards[2]==cc&&deck->cards[2].getSuit()==Card::Hearts)
			{
				return true;
			}
			if (deck->cards[1]==cc&&deck->cards[2]==cc&&deck->cards[1].getSuit()==Card::Hearts&&deck->cards[2].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
	}
	return false;
}

bool GameLogic::IsDoubleThree(const Deck * deck)
{
	if (deck->cards.size()==6)
	{
		int c1=0,c2=0,i;
		Card c=deck->cards[0];
		Card cc=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
		for (i=0;i<6;i++)
		{
			if (c==deck->cards[i])
			{
				c1++;
			}
			else
			{
				if (c.getFace()==(Card::Face)(deck->cards[i].getFace()-1)&&deck->cards[i]!=cc)
				{
					c=deck->cards[i];
					for (;i<6;i++)
					{
						if (c==deck->cards[i])
						{
							c2++;
						}
					}
				}
				break;
			}
		}
		if (c1==3&&c2==3)
		{
			return true;
		}
		if (c1==2&&c2==3||c1==3&&c2==2)
		{
			if (deck->cards[5]==cc&&deck->cards[5].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
		if (c1==1&&c2==3||c1==3&&c2==1||c1==2&&c2==2)
		{
			if (deck->cards[4]==cc&&deck->cards[5]==cc&&deck->cards[4].getSuit()==Card::Hearts&&deck->cards[5].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
	}
	return false;
}

bool GameLogic::IsThreeWithTwo(const Deck * deck)
{
	if (deck->cards.size()==5)
	{
		int c1=0,c2=0,i;
		Card c=deck->cards[0];
		for (i=0;i<5;i++)
		{
			if (c==deck->cards[i])
			{
				c1++;
			}
			else
			{
				c=deck->cards[i];
				for (;i<5;i++)
				{
					if (c==deck->cards[i])
					{
						c2++;
					}
				}
				break;
			}
		}
		if (c1==3&&c2==2||c1==2&&c2==3)
		{
			return true;
		}
		Card cc=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
		if (c1==2&&c2==2)
		{
			if (deck->cards[4]==cc&&deck->cards[4].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
		if (c1==1&&c2==2||c1==2&&c2==1)
		{
			if (deck->cards[3]==cc&&deck->cards[4]==cc&&deck->cards[3].getSuit()==Card::Hearts&&deck->cards[4].getSuit()==Card::Hearts)
			{
				return true;
			}
		}
	}
	return false;
}

bool GameLogic::IsThreeOfPair(const Deck * deck)
{
	if (deck->cards.size()==6)
	{
		int changecard_count=getChangecard_count(deck);
		int c1=0,c2=0,c3=0;
		Card c=deck->cards[0];
		for (int i=0;i<6-changecard_count;i++)
		{
			if (c==deck->cards[i])
			{
				c1++;
			}
			else
			{
				if ((Card::Face)(c.getFace()+1)==deck->cards[i].getFace()&&c1<=2)
				{
					c=deck->cards[i];
					for (;i<6-changecard_count;i++)
					{
						if (c==deck->cards[i])
						{
							c2++;
						}
						else
						{
							if ((Card::Face)(c.getFace()+1)==deck->cards[i].getFace()&&c2<=2)
							{
								c=deck->cards[i];
								for (;i<6-changecard_count;i++)
								{
									if (c==deck->cards[i])
									{
										c3++;
									}
								}
							}
							break;
						}
					}
				}
				//eg:33,55,2百搭牌
				if ((Card::Face)(c.getFace()+2)==deck->cards[i].getFace())
				{
					if (c1==2&&deck->cards[i]==deck->cards[i+1]&&changecard_count==2)
					{
						return true;
					}
				}
				break;
			}
		}
		if (c1<=2&&c2<=2&&c3<=2&&c1+c2+c3+changecard_count==6)
		{
			return true;
		}
	}
	return false;
}

bool GameLogic::IsStraight(const Deck * deck)
{
	if (deck->cards.size()==5)
	{
		int changecard_count=getChangecard_count(deck);
		for (int i=0;i<5-changecard_count-1;i++)
		{
			if ((Card::Face)(deck->cards[i].getFace()+1)!=deck->cards[i+1].getFace())
			{
				if ((Card::Face)(deck->cards[i].getFace()+2)==deck->cards[i+1].getFace())
				{
					changecard_count--;
				}
				else if ((Card::Face)(deck->cards[i].getFace()+3)!=deck->cards[i+1].getFace())
				{
					changecard_count-=2;
				}
				else
					return false;
			}
		}
		if (changecard_count>=0)
		{
			return true;
		}
	}
	return false;
}

bool GameLogic::IsBomb(const Deck * deck)
{
	if (deck->cards.size()>=4)
	{
		int count=0;
		Card c=Card(Card::Hearts,(Card::Face)GameState::Gamelevel);
		for (unsigned int i=0;i<deck->cards.size()-1;i++)
		{
			if (deck->cards[0]!=deck->cards[i])
			{
				if(deck->cards[i]==c&&deck->cards[i].getSuit()==Card::Hearts)
				{
					count++;
					continue;
				}
				else
					break;
			}
			else
				count++;
		}
		if (count>=4)
		{
			return true;
		}
	}
	return false;	
}

bool GameLogic::IsFlush(const Deck * deck)
{
	if (deck->cards.size()==5)
	{
		int changecard_count=getChangecard_count(deck);
		Card c=deck->cards[0];
		for (int i=0;i<5-changecard_count;i++)
		{
			if (c.getSuit()!=deck->cards[i].getSuit())
			{
				return false;
			}
		}
		IsStraight(deck);
	}
	return false;
}
//独特牌型的判断

//----------------------牌信息获取------------------------
bool GameLogic::GetCardInfo(const Deck * deck)
{
	if (IsSingleCard(deck))
	{
		ranking=GameLogic::SingleCard;
		maxcard=deck->cards[0].getFace();
		return true;
	}
	if (IsPair(deck))
	{
		ranking=GameLogic::SingleCard;
		maxcard=deck->cards[0].getFace();
		return true;
	}
	if (IsThreeOfAKind(deck))
	{
		ranking=GameLogic::ThreeOfAKind;
		maxcard=deck->cards[0].getFace();
		return true;
	}
	if (IsDoubleThree(deck))
	{
		ranking=GameLogic::DoubleThree;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[6-changecard_count-1].getFace();
		return true;
	}
	if (IsThreeWithTwo(deck))
	{
		ranking=GameLogic::ThreeWithTwo;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[5-changecard_count-1].getFace();
		return true;
	}
	if (IsThreeOfPair(deck))
	{
		ranking=GameLogic::ThreeOfPair;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[6-changecard_count-1].getFace();
		return true;
	}
	if (IsStraight(deck))
	{
		ranking=GameLogic::Straight;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[5-changecard_count-1].getFace();
		return true;
	}
	if (IsStraight(deck))
	{
		ranking=GameLogic::Straight;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[5-changecard_count-1].getFace();
		bomb_count=deck->cards.size();
		return true;
	}
	if (IsFlush(deck))
	{
		ranking=GameLogic::Flush;
		int changecard_count=getChangecard_count(deck);
		maxcard=deck->cards[5-changecard_count-1].getFace();
		return true;
	}
	return false;
}

bool GameLogic::Is_Legal(GameLogic A)
{
	if (A.getRanking()!=GameLogic::Bomb&&A.getRanking()==ranking&&maxcard>A.getMaxcard())
	{
		return true;
	}
	if (A.getRanking()!=GameLogic::Bomb&&A.getRanking()!=GameLogic::Flush&&ranking==GameLogic::Bomb)
	{
		return true;
	}
	if (A.getRanking()==GameLogic::Bomb&&ranking==GameLogic::Bomb&&bomb_count>A.getBomb_count()||maxcard>A.getMaxcard())
	{
		return true;
	}
	if (A.getRanking()==GameLogic::Bomb&&A.getBomb_count()<6&&ranking==GameLogic::Flush)
	{
		return true;
	}
	if (A.getRanking()==GameLogic::Flush&&ranking==GameLogic::Bomb&&bomb_count>=6)
	{
		return true;
	}
	return false;
}