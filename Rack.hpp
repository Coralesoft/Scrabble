// Rack.hpp: interface for the Rack class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	03/10/2001													 **
**		File	:	Rack.hpp													 **
**		Purpose	:	Holds tiles for player										 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Made playerRack private, added accessors						 **
 *********************************************************************************/
#pragma once

#include "Tile.hpp"
#include "TileBag.hpp"
#include <vector>
#include <iostream>

class Rack
{
private:
	static const int RACK_MAX_ITEMS = 7;
	std::vector<Tile> playerRack_;

public:
	Rack() = default;

	void addNewTile(TileBag& tileBag);
	void displayRack() const;
	int returnScore() const;
	void eraseTile(char letter);
	char getFirstLetter() const;

	const std::vector<Tile>& getTiles() const { return playerRack_; }
	std::vector<Tile>& getTiles() { return playerRack_; }
	size_t size() const { return playerRack_.size(); }
};
