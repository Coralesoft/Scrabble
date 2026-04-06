// board.cpp: implementation of the board class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		File	:	Board.cpp													 **
**		Purpose	:	Provide playing board and functions for scrabble game		 **
**		Version	:	0.87 beta 31/10/2001										 **
**		History	:	31/10/2001 Added new function touching to make the program   **
**					more efficent and reduce the amount of lines of code.		 **
**					30/10/2001 Fixed again, found it was not scoring any letters **
**					after the last letter was placed and more letters where 	 **
**					connected.													 **
**																				 **
**					0.8.5.5 have made this version more generalised and fixed 	 **
**					scoring problem	now all scores are correct;					 **
**					0.85 scoring problem error on jump;							 **
 *********************************************************************************/

#include "Board.hpp"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//===============================================================================
//		   DISPLAYBOARD() does exactly that displays the board
//		   This draw to the screen the board and any letters
//		   Contained in it.
//===============================================================================
void Board::displayBoard()
{
	char l;	//used to output the oards letters
	int rowa=6;//formatting

	con.setBackground(bLtBlue);//Seting colours with my package
	con.setForeground(LtGreen);
	con.ClearScreen();			//these should be obvious
	con.setBackground(bBlue);
	con.ClearSect(0,20);
	con.setBackground(bLtBlue);
	con.goto_XY(5,2);
//-------------------------------------------------------------
	//the next section draws the board in the correct position
	cout<<"  |A_B_C_D_E_F_G_H_I_J_K_L_M_N_O|";

	for (int num=0; num<15;num++)
	{	 //draw left hand vertical line and put numbers
		con.goto_XY(rowa,num+3);//(col row)
		cout <<num<<"|";
		if(num ==9)
			rowa--;
	}

	for(int li=0; li<15;li++)
	{	//draw right hand line
		con.goto_XY(37,li+3);
		cout<<"|";
	}
	con.goto_XY(6,18);
	cout<<" -------------------------------";


//--------------------------------------------------------------
	//This section will output the letters from the board
	int row=2;	// start positions
	int col=6;
	for (int ro=0; ro < 15; ro++)	//outer loop (row)
	{
		row++;						// step down one row
		col=6;						//go back to first col
		for (int co=0; co<15;co++)	//inner  loop(column)
		{
			col+=2;					//step across two places
			l = sq_[ro][co].getLetter();	//set output variable
			con.goto_XY(col,row);	// goto position
			if(l!=' ')				//if not black
			cout <<l;				//output letter
		}//for column
	}//for row
}

//===============================================================================
//		   PLACETILEV() This function takes in the postion (row,column)
//		   				the direction the word must be placed and the
//		   				tile to be placed on the board. all moves are valid
//						one they reach this fuction
//                      The tiles are scored at the time of placement
//                      and any additional scores from connected tiles are
//                      also scored. If a blank tile is played its new letter
//						value is set.
//===============================================================================


void Board::placeTileV(int row,int col, Square place, char direction)
{
	char let;				  //holds new letter value
	if(place.getLetter()=='@')// IF A BLANK TILE SET NEW LETTER VALUE;
	{						  //SCORE STILL = ZERO;
		cout<<"please enter the new letter value for the blank:";
		cin>>let;//input new letter value
		let=toupper(let);		//convert it
		place.setLetter(let);	//set new value
	}
	sq_[row][col]= place;		//place tile on the board
	addScore(place.getScore());	//add its score to the tally

	if(firsttile_==false)//If First Tile check all directions
	{
		scoreEast(row,col+1);
		scoreWest(row,col-1);
		scoreSouth(row+1,col);
		scoreNorth(row-1,col);
		firsttile_=true;	//let the scoring algorithm know
						//first tile has been played
	}
	else //If not first Tile check only two directiond
	{

	if(direction=='V')	 //If tile played vertically check EAST WEST
	{
		if(sq_[row][col+1].isTaken()==true) //if touching east score it
			scoreEast(row,col+1);
		if(sq_[row][col-1].isTaken()==true) //if touching west score it
			scoreWest(row,col-1);
	}//end direction V

	if(direction=='H')// If tile played horizontal check NORTH SOUTH
	{
		if(sq_[row+1][col].isTaken()==true)	//if touching south score it
			scoreSouth(row+1,col);
		if(sq_[row-1][col].isTaken()==true) //if touching North score it
			scoreNorth(row-1,col);
	}
	}
}

//===============================================================================
//		   ScoreEast,West,North south() These 4 funtions all do the same thing
//		   			but in different directions. search and score until they
//					find a square not taken. latter i will remove the if and
//					add the condtion to the while satement. i have done it this
//					way for readability for now.
//===============================================================================

void Board::scoreEast(int row,int col)
{
	Square temp;
	while(col <= 14 && sq_[row][col].isTaken()==true)
	{
		temp=sq_[row][col];				//asssign temp the current tile
		addScore(temp.getScore());		// get its score
		col++;							// go to next square EAST
	}
}
//===============================================================================

void Board::scoreWest(int row,int col)
{
	Square temp;
	while(col >= 0 && sq_[row][col].isTaken()==true)
	{
		temp=sq_[row][col];			    //asssign temp the current tile
		addScore(temp.getScore());		// get its score
		col--;							// go to next square WEST
	}
}
//===============================================================================

void Board::scoreNorth(int row,int col)
{
	Square temp;
	while(row >= 0 && sq_[row][col].isTaken()==true)
	{
		temp=sq_[row][col];				//asssign temp the current tile
		addScore(temp.getScore());		// get its score
		row--;							// go to next square NORTH
	}
}
//===============================================================================

void Board::scoreSouth(int row,int col)
{
	Square temp;
	while(row <= 14 && sq_[row][col].isTaken()==true)
	{
		temp=sq_[row][col];				//asssign temp the current tile
		addScore(temp.getScore());		// get its score
		row++;							// go to next square SOUTH
	}
}

//===============================================================================
//		   CHECKPOS()   This function takes in the postion (row,column)
//		   				the direction the word must be placed and the
//		   				size of the word to be placed. It then checks the validity
//						of the played word as in if it is touching another tile
//						then will check the bounds of the word to be place to
//						see if it stays within the bounds of the board.
//						I will move the four direction checking into its own
//						function
//===============================================================================

bool Board::checkPos(int row, int col,int size, char direction)
{
	bool legal=false;		//set legal to false
	if (direction =='H')		//if direction horizontal
	{
	//check the boundaries. first test
		for (int hPos=0; hPos<size; hPos++)
		{
			while(sq_[row][col].isTaken()==true)
				col++;
			if(col>14)	 //checking the boundaries
			{
				legal= false; //if exceeds the bounds set false
				break;		  // and exit
			}
				else
					legal= true; //if within bound set true
	//------------------------------------------------------------
				//second test, if first move of the game make
				//sure it is centred.

				if(firstMove_==false)  //check first move placement
				if((row==7)&&(col==7)&&(firstMove_==false))
					poschek_=true; //if touches set true

				if(firstMove_==true) // if first move has been played
					touching(row,col);// all following words must touch
				 col++; //goto next postion
		}
	}
	if (direction =='V')	//if direction vertical
	{//check the boundaries. first test
		for (int vPos=0; vPos<size; vPos++)
		{
			    while(sq_[row][col].isTaken()==true)
					row++;
				if(row>14)	    //checking the boundaries
				{
					legal= false; //if exceeds the bounds set false
					break;		  // and exit
				}
				else
					legal= true; //if within bound set true
				//second test, if first move of the game make
				//sure it is centred.
				if(firstMove_==false)   //check first move placement
				if((row==7)&&(col==7)&&(firstMove_==false))
					poschek_=true;

				if(firstMove_==true)// if first move has been played
					touching(row,col);// all following words must touch

				row++; //goto next postion
		}//end for loop
	} //end if

	if(firstMove_==false)  // set legal if this is first move
		legal=poschek_;

	return legal; //if all is valid will return true else false;
}

//===============================================================================
//		   TOUCHING()	This function check to see if the new word touches an
//						existing word and trips the correct flag.
//						add this to reduce the lines of code a bit.
//===============================================================================
void Board::touching(int row, int col)
{
	if((col < 14 && sq_[row][col+1].isTaken()==true) ||
	   (col > 0  && sq_[row][col-1].isTaken()==true))
		touchHorz_=true;	//if EAST or WEST touches set true
	if((row < 14 && sq_[row+1][col].isTaken()==true) ||
	   (row > 0  && sq_[row-1][col].isTaken()==true))
		touchVertz_=true; // if NORTH or SOUTH touches set true
}
//===============================================================================
//		   PLACETILE()  This function takes in the postion (row,column)
//		   				the direction the word must be placed and the the
//						vector of tiles that the player wishes to play
//		   				if all checks return true(legal move)
//===============================================================================
bool Board::placeTile(int row, int col, char direction, vector<Tile>& tiles)
{
	vector<Square> temp; //holds the word to be placed
	Square Stemp;		 //temperary square,used to operate on the tile info
	bool legal=false;	 // set the legal boolean
	resetScore();		 // reset the score
	resetFlags();		 //reset all the boolean flags
	legal=checkPos(row,col,tiles.size(),direction); // check to see if move is legal

	//if first move has been played check to see if the new word touches an existing word
	if(legal==true)
	{
		if(firstMove_==true)
		{
			if((touchVertz_==true) || (touchHorz_==true))	//check variable
				legal=true;		//make choice
			else
				legal=false;
		}
	}
	if(legal==true)	 //if all legal then proceed to place the word
	{
		if(tiles.size()==7)	// check to see how many letters if 7 give 50point bonus
			Board::addScore(BONUS);
//----------------------------------------------------------------------------------
		//transfer tiles to squares
		for (std::vector<int>::size_type xyz =0; xyz<tiles.size(); xyz++)
		{
			Stemp.setScore(tiles[xyz].getScore());
			Stemp.setLetter(tiles[xyz].getLetter());
			Stemp.setTaken(true); //set boolean
			temp.push_back(Stemp); //add to the vector
		}
  		if (direction =='H')//if direction is horizontal
		{					// place word on the board
			for (std::vector<int>::size_type hPos=0; hPos<temp.size();hPos++)
			{
				while(sq_[row][col].isTaken()==true)//if finds a tile in the way
				{								   //jump over it and get its score;
					addScore(sq_[row][col].getScore());
					col++;						   //move to next square
				}
				placeTileV(row,col,temp[hPos],direction); //if blank square place tile
				col++;//move to next square;
				if(hPos+1==temp.size())//&& row<14)
				{//if last letter is placed check the end
					while(sq_[row][col].isTaken()==true)// && row<14)
					{// if have a tile touching score it
						addScore(sq_[row][col].getScore());
						col++ ;
					}
				} //end if
			} //end for
		} //end if
		if (direction =='V') // if direction is vetical
		{					 // place word on the board
			for (std::vector<int>::size_type vPos=0; vPos<temp.size();vPos++)
			{
				while(sq_[row][col].isTaken()==true) //if finds a tile set over
				{
					addScore(sq_[row][col].getScore());
					row++; //move next square
				}
				placeTileV(row,col,temp[vPos],direction);
				row++; //if the square is blank place tile
				 	  //move next square
				if(vPos+1==temp.size()&& row<14)
				{	 //if last letter is placed check the end
					while(sq_[row][col].isTaken()==true && row<14)
					{// if have a tile touching score it
						addScore(sq_[row][col].getScore());
						row++ ;
					} //end while
				} //end if

			}  //end for loop (vertical)
		} //end if (direction V)

	} //end if (legal==true);
//-----------------------------------------------------------------------------
	//if it is the first move, double the score and trip the first move flag;
	if(Board::firstMove_==false && Board::poschek_==true)
	{	//but only if first move was legal
		Board::addScore(Board::tmpScore_);
		Board::tripFirstMove();
	}
	return legal; //return the outcome of the function true /false
}
//===============================================================================
