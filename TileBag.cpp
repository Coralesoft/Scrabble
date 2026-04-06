// TileBag.cpp: implementation of the TileBag class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	TileBag.cpp													 **
**		Purpose	:	Hold and distribute tiles									 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Replaced rand() with <random>								 **
 *********************************************************************************/
#include "TileBag.hpp"

TileBag::TileBag()
	: rng_(std::random_device{}())
{
}

//=======================================================================
//		 RANDGRAB() This function grabs a tile at random from the bag
//=======================================================================

std::optional<Tile> TileBag::randGrab()
{
	if (bag_.empty()) {
		return std::nullopt;
	}

	std::uniform_int_distribution<size_t> dist(0, bag_.size() - 1);
	size_t pos = dist(rng_);

	Tile tile = bag_[pos];
	bag_.erase(bag_.begin() + pos);

	return tile;
}

//=======================================================================
//		 LOADBAG() This function loads the tile bag from external file
//=======================================================================

void TileBag::loadBag()
{
	std::ifstream in("letfil.bin");

	if (!in.is_open()) {
		std::cout << "Unable to open file letfil.bin\n";
		std::cout << "Press any key to exit...";
		while (!_kbhit());
		return;
	}

	std::string line;
	while (std::getline(in, line)) {
		std::istringstream lineStream(line);
		unsigned char letter;
		int score;

		if (lineStream >> letter >> score) {
			Tile temp;
			temp.setLetter(letter);
			temp.setScore(score);
			bag_.push_back(temp);
		}
	}
}

//=======================================================================
//		 ADDTILE() Adds tiles back to the bag (for exchanging)
//=======================================================================

void TileBag::addTile(const std::vector<Tile>& tiles)
{
	bag_.insert(bag_.end(), tiles.begin(), tiles.end());
}
