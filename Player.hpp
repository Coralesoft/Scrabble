// Player.hpp: interface for the Player class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	03/10/2001													 **
**		File	:	Player.hpp													 **
**		Purpose	:	Hold player information										 **
**		Version	:	0.86 beta 28/10/2001										 **
**		History	:	Made rack private, added accessors							 **
 *********************************************************************************/
#pragma once

#include <string>
#include <iostream>
#include "Rack.hpp"

class Player
{
private:
	std::string name_;
	int score_ = 0;
	Rack rack_;

public:
	Player() = default;

	void setName(const std::string& pname) { name_ = pname; }
	void setScore(int newScore) { score_ += newScore; }
	void penalty(int subtract) { score_ -= subtract; }

	void displayName() const { std::cout << name_; }
	void displayScore() const { std::cout << score_; }
	int getScore() const { return score_; }
	const std::string& getName() const { return name_; }

	Rack& getRack() { return rack_; }
	const Rack& getRack() const { return rack_; }
};
