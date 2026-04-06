// Tile.hpp: interface for the Tile class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	Tile.hpp													 **
**		Purpose	:	Hold tile information										 **
**		Version	:	0.86 beta 28/10/2001										 **
 *********************************************************************************/
#pragma once

class Tile
{
private:
	char letter_ = ' ';
	int	score_ = 0;

public:
	Tile() = default;

	void setLetter(char let) { letter_ = let; }
	void setScore(int score) { score_ = score; }

	int getScore() const { return score_; }
	char getLetter() const { return letter_; }
};
