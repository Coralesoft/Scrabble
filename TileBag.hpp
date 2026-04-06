// TileBag.hpp: interface for the TileBag class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	TileBag.hpp													 **
**		Purpose	:	Hold and distribute tiles									 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Replaced old rand() with <random>, cleaned up pointers		 **
 *********************************************************************************/
#pragma once

#include <vector>
#include <random>
#include <fstream>
#include <optional>
#include "Tile.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <conio.h>

class TileBag
{
private:
	std::vector<Tile> bag_;
	std::mt19937 rng_;

public:
	TileBag();

	void loadBag();
	size_t numTiles() const { return bag_.size(); }
	bool isEmpty() const { return bag_.empty(); }

	std::optional<Tile> randGrab();
	void addTile(const std::vector<Tile>& tiles);
};
