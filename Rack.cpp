// Rack.cpp: implementation of the Rack class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	03/10/2001													 **
**		File	:	Rack.cpp													 **
**		Purpose	:	Holds tiles for player										 **
**		Version	:	0.86 beta 28/10/2001										 **
 *********************************************************************************/
#include "Rack.hpp"

using namespace std;

//=======================================================================
//		   ADDNEWTILE() Loads the player's rack from tile bag
//=======================================================================
void Rack::addNewTile(TileBag& tileBag)
{
	while (playerRack_.size() != RACK_MAX_ITEMS && !tileBag.isEmpty()) {
		auto tile = tileBag.randGrab();
		if (tile.has_value()) {
			playerRack_.push_back(*tile);
		}
	}
}

//=======================================================================
//		   getFirstLetter() Gets first letter in rack (for sorting)
//=======================================================================
char Rack::getFirstLetter() const
{
	if (!playerRack_.empty()) {
		return playerRack_[0].getLetter();
	}
	return 'Z';
}

//=======================================================================
//		   DISPLAYRACK() Displays tiles in the player's rack
//=======================================================================
void Rack::displayRack() const
{
	for (const auto& tile : playerRack_) {
		cout << tile.getLetter() << " ";
	}
}

//=======================================================================
//		   ERASETILE() Deletes tile from rack matching the letter
//=======================================================================
void Rack::eraseTile(char letter)
{
	for (size_t pos = 0; pos < playerRack_.size(); ++pos) {
		if (letter == playerRack_[pos].getLetter()) {
			playerRack_.erase(playerRack_.begin() + pos);
			return;
		}
	}
}

//=======================================================================
//		  returnScore() Returns total score left in rack (for penalty)
//=======================================================================
int Rack::returnScore() const
{
	int total = 0;
	for (const auto& tile : playerRack_) {
		total += tile.getScore();
	}
	return total;
}
