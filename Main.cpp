/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	01/10/2001													 **
**		File	:	Main.cpp													 **
**		Purpose	:	This is the main controll of the program,					 **
**		Version	:	0.86 beta 28/10/2001										 **
**														 **
**		History	:	have made this version more generalised and	fixed bubble sort**
**																				 **
 *********************************************************************************/

#include "Player.hpp"
#include "Rack.hpp"
#include "Scrabble.hpp"
#include "Tile.hpp"
#include "TileBag.hpp"
#include "Board.hpp"
#include "concol.hpp"
#include <iostream>
#include <string>
using namespace std;

//===============================================================================
//		   SETUPGAME() This function displays welcome message, sets up
//						the number of players and gets their name;
//===============================================================================

void setUpGame(Scrabble *ps)//, TileBag *tileBag)
{	concol con;  //my console library for screen manipulation

	unsigned int nplay=0;// hold number of players
	Player player;		//new player object
	string name;		//new player name
	char  input[30];	//new dummy input
	bool correct=false;	// error handler variable
	while(!correct)		//start of the error handler
	{
	con.goto_XY(15,8); //this next section is just screen formating and titles
	con.setForeground(Yellow);
	cout<< "WELCOME to My Scarbble game !!!";
	con.goto_XY(15,9);
	cout<<"(c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED";
	con.setForeground(LtGreen);
	con.setBackground(bBlue);
	con.ClearSect(0,20);
	con.goto_XY(5,20);

	cout<<"How many players: ";
	cin.getline(input,80);	 //get the numbers of players as char
	nplay=atoi(input);		 //convert to integer
	if(nplay >=1 && nplay <=4) {	//no more then 4 players altho can be unlimited
		correct=true;			//if no more than 4 set flag to true
	} else {		// if bad input	display msg
		con.setForeground(LtRed);
		cout<<endl<<"You have made an invalid input"<<endl;
		cout<<"There is a maximum of 4 players"<< flush;
		Sleep(4000);   //wait 4 seconds
		cout<<flush;   //clear buffers and reset
	}

	}//end setnumplayers error handeler

	ps->setNumPlayers(nplay);  //set number of players varialbe

	for (std::vector<int>::size_type k = 0; k<nplay; k++)  //for each player add their name
		{
			cout <<"please enter name of player no " << k+1 <<" :";
			cin >> name;
			player.setName(name);
			ps->addPlayer(player);

		}
}
//===============================================================================
//		   MYSORT() This is my version of the bubble sort.
//					it is used to decide who shall go play first
//					The one with the lowest tile will be put first in the vector
//===============================================================================

void mySort(Scrabble *ps)//my version of the bubble sort easyest to implement
{
	if(ps->players.size()==2)
	{	//if only 2 players just check and swap if necessary
		if(ps->players[0].getRack().getFirstLetter() > ps->players[1].getRack().getFirstLetter())
			swap(ps->players[0],ps->players[1]);
	}
	else
	{ //more then 2 players, go sort them
		for(int out = ps->players.size()-1; out > 0; out-- )  // FIXED: was out > 1 (caused last pass to be skipped!)
		{
			for (int in=0; in<out;in++)//inner loop runs forward
			{
				if(ps->players[in].getRack().getFirstLetter() > ps->players[in+1].getRack().getFirstLetter())
					swap(ps->players[in],ps->players[in+1]);//if out of order
														//swap them
			}
		}
	}
}



//===============================================================================
//		   MAIN() control program
//===============================================================================

int main()
{
	concol con;					//Myconsole package
	con.setBackground(bLtBlue);	//formatting
	con.setForeground(LtGreen);
	con.ClearScreen();
	con.resizeWindow(84,30);  //setting the console window size
	SetConsoleTitle("Scarble.. (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED");
	TileBag tileBag;			//create new tile bag object
	Board board;				//create new board object
	Scrabble ps;				//create new input control object
	tileBag.loadBag();			//load the tilebag from external file
	int turn=0;
	char choice;			//set local variable
	setUpGame(&ps);				//call function to setup the game
//----------------------------------------------------------------------
	//load each of the players tilebag
	for(std::vector<int>::size_type load=0;load <ps.players.size();load++ )
	{
		ps.players[load].getRack().addNewTile(tileBag);
	}
//----------------------------------------------------------------------
	//sort the players to see who goes first
	 mySort(&ps);

//----------------------------------------------------------------------
	//main control, loop until the bag is empty or player quit Bag.empty()
	while(tileBag.isEmpty() || ps.skip != static_cast<int>(ps.players.size()))
	{
		//if bag is empty check if all racks are empty too
		if(tileBag.isEmpty())
		{
			bool allEmpty=true;
			for(std::vector<int>::size_type chk=0; chk<ps.players.size(); chk++)
			{
				if(ps.players[chk].getRack().size() > 0)
					allEmpty=false;
			}
			if(allEmpty)
			{
				con.setBackground(bBlue);
				con.setForeground(Yellow);
				con.ClearSect(0,20);
				con.goto_XY(15,20);
				cout<<"GAME COMPLETE! All tiles have been played.";
				con.goto_XY(15,22);
				cout<<"PRESS ANY KEY to see the results";
				while(!_kbhit());
				_getch();
				break;
			}
		}
		ps.setTurn(turn);			//set turn variable
		board.displayBoard();		//display the board
		con.setBackground(bLtBlue) ; //screen settings
		con.setForeground(LtGreen);
		ps.menuItems(&ps, &board, &tileBag);//call the menu screen and pass the game
											//information and pass the board;
		ps.players[turn].getRack().addNewTile(tileBag);	//pass the player the
													//tilebag to reload from
		turn++;			//rotate to next player
		if (turn == static_cast<int>(ps.players.size()))	//if all players have been serviced
			turn=0;						//start again
		if(ps.skip == static_cast<int>(ps.players.size()))
		{
			cout<<"do you wish to end the game? Y/N: ";
			cin>>choice;
			choice=toupper(choice);
			if(choice=='Y')
				break;	 //if the players all skip a turn end the game
			else
				ps.resetSkip();
		}
	}
	ps.Farewell(&ps);//call farrewell message and display scores
	return 0;
} // END OF MAIN
