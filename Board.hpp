// Board.hpp: interface for the Board class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	Board.hpp													 **
**		Purpose	:	Playing board and functions									 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Made sq private, switched to std::array						 **
 *********************************************************************************/
#pragma once

#include <iostream>
#include <array>
#include "Tile.hpp"
#include "concol.hpp"
#include "Square.hpp"
#include <vector>

class Board
{
private:
	std::array<std::array<Square, 15>, 15> sq_;
	int tmpScore_ = 0;
	bool firstMove_ = false;
	bool poschek_ = false;
	bool touchHorz_ = false;
	bool touchVertz_ = false;
	bool firsttile_ = false;
	static const int BONUS = 50;
	concol con;

	void placeTileV(int row, int col, Square place, char direction);
	bool checkPos(int row, int col, int size, char direction);
	void scoreNorth(int row, int col);
	void scoreSouth(int row, int col);
	void scoreEast(int row, int col);
	void scoreWest(int row, int col);
	void touching(int row, int col);

public:
	Board() = default;

	void displayBoard();
	bool placeTile(int ro, int co, char direction, std::vector<Tile>& tiles);

	void resetScore() { tmpScore_ = 0; }
	void addScore(int tscore) { tmpScore_ += tscore; }
	int getScore() const { return tmpScore_; }

	void resetFlags() {
		touchVertz_ = false;
		touchHorz_ = false;
		firsttile_ = false;
	}
	void tripFirstMove() { firstMove_ = true; }
	bool getFirstMove() const { return firstMove_; }
};
