#pragma once


class GameState
{
public:
	static int Gamelevel;

	static void setGamelevel(int level){Gamelevel=level;}

	static void reset(){Gamelevel=2;}
};