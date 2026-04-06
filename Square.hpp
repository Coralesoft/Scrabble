// Square.hpp: interface for the Square class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	Square.hpp													 **
**		Purpose	:	Hold square information										 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Fixed bad inheritance, now uses composition					 **
 *********************************************************************************/
#pragma once

#include "Tile.hpp"

class Square
{
private:
	bool taken_ = false;
	char letter_ = ' ';
	int	score_ = 0;

public:
	Square() = default;

	void setLetter(char let) { letter_ = let; }
	void setScore(int score) { score_ = score; }
	void setTaken(bool taken) { taken_ = taken; }

	int getScore() const { return score_; }
	char getLetter() const { return letter_; }
	bool isTaken() const { return taken_; }
};
