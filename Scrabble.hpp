// Scrabble.hpp: interface for the Scrabble class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	01/10/2001													 **
**		File	:	Scrabble.hpp												 **
**		Purpose	:	This is the main control of game play and inputs			 **
**		Version	:	0.86 beta 28/10/2001										 **
**														 **
**		History	:	Added bubble sort to display winners in order				 **
**					Added a status bar for the tile bag better then bag			 **
**					0.85 added tile bag may turn into status bar				 **
**					0.84 fixed exception handlers								 **
 *********************************************************************************/
#if !defined(AFX_SCRABBLE_HPP__41E908EB_68D5_47C1_A0A5_70571E4886EE__INCLUDED_)
#define AFX_SCRABBLE_HPP__41E908EB_68D5_47C1_A0A5_70571E4886EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <string>
#include <iostream>
#include <vector>
#include "Player.hpp"
#include "TileBag.hpp"
#include "Rack.hpp"
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "concol.hpp"
#include "Board.hpp"

using namespace std;

class Scrabble
{
private:
	int numPlayers;	//number of players
	string moveXY;	//coordinates
	char direction;	//directon of word to be placed
	string playWord; //the word the player wants to play
	string xchword;	//the letters that wish to be exchanges
	bool mistake;	//flag for a mistake
public:
	concol con;
	int turn;
	int skip;
	int col;
	int row;
	vector<Player> players;
	Scrabble();
	void setTurn(int i){turn=i;} //set the players turn
	int getTurn(){return turn;}	 //get whos turn it is
	void setNumPlayers(int i){numPlayers = i;};	//set number of players
	int getNumPlayers(){return numPlayers;}
	void menuItems(Scrabble *ps,Board * boa, TileBag *tileBag);
	void setMove(Scrabble *ps,Board * boa);
	void validatePos();
	void exchangeTile(Scrabble *ps, TileBag *tileBag);
	void validateDir();
	void validateWord( Scrabble *ps, Board * boa);
	void addPlayer(Player newPlayer);
	void setSkip(){skip++;}
	void resetSkip(){skip=0;}
	void rules();
	void Farewell(Scrabble *ps);
	void diplayScoreBoard(Scrabble *ps, TileBag *tileBag);
	void dispTbag(TileBag *tileBag);

	virtual ~Scrabble();

};

#endif // !defined(AFX_SCRABBLE_HPP__41E908EB_68D5_47C1_A0A5_70571E4886EE__INCLUDED_)
