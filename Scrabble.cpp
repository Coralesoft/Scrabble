// Scrabble.cpp: implementation of the Scrabble class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	01/10/2001													 **
**		File	:	Scrabble.cpp												 **
**		Purpose	:	This is the main control of game play and inputs			 **
**		Version	:	0.86 beta 28/10/2001										 **
**		 													 **
**		History	:	Added bubble sort to display winners in order				 **
**					Added a status bar for the tile bag better then bag			 **
**					0.85 added tile bag may turn into status bar				 **
**					0.84 fixed exception handlers								 **
 *********************************************************************************/
#include "Scrabble.hpp"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Scrabble::Scrabble():mistake(false),turn(0),skip(0)
{

}

//=======================================================================
//		 MENUITEMS() This function is used to display the various choices
//					 to the player when it is their turn
//=======================================================================

void Scrabble::menuItems(Scrabble *ps, Board * boa, TileBag *tileBag)
{
	char choice;		//used to ge the input choice
	bool correct=false;	//used for error correction
	while(!correct)		//error handler
	{
		mistake=false;
		boa->displayBoard(); //call display the board
		diplayScoreBoard(ps,tileBag);//call display score board
		con.goto_XY(40,3);
		con.setForeground(LtCyan);
		cout<<"NAME";
		con.setForeground(LtGreen);
		con.setBackground(Black);
		con.goto_XY(40,4);
		ps->players[ps->turn].displayName();//display players name
		con.goto_XY(40,6);
		cout << " Select choice    ";
		con.goto_XY(40,7);
		cout <<" 1. move          ";
		con.goto_XY(40,8);
		cout <<" 2. exchange tile ";
		con.goto_XY(40,9);
		cout <<" 3. Skip turn     ";
		con.goto_XY(40,10);
		cout <<" 4. Rules!        ";
		con.goto_XY(40,11);
		cout <<" 5. Quit!         ";
		con.goto_XY(40,13);
		con.setForeground(LtCyan);
		con.setBackground(bLtBlue);
		cout<<"TILES";
		con.goto_XY(40,14);
		con.setBackground(Black);
		con.setForeground(LtMagenta);
		players[ps->turn].getRack().displayRack(); //display players rack
		con.setBackground(bLtBlue) ;
		con.setForeground(LtGreen);
		con.goto_XY(5,20);
		con.setBackground(bBlue);
		con.setForeground(Yellow);
		cout<<"Please enter choice: ";
		cin  >> choice;		  //get choice
	switch(choice)
	{
	case '1':
		correct =true;	   //trip the error handler
		resetSkip();	   // reset the skip counter
		setMove(ps,boa);	//call setmove
		if(mistake==true)	//incase mistake is made onthe choice
			correct=false;
		break;
	case '2':
		correct=true;
		resetSkip();
		exchangeTile(ps,tileBag);	//call exchange tile routine
		if(mistake==true)	//incase mistake is made onthe choice
			correct=false;
		break;
	case '3':
		correct=true;
		setSkip();//increment skip counter
		break;
	case '4':
		rules();		   //call display rules
		break;
	case '5':
		ps->skip=ps->players.size();
		correct=true;
		break;
	default:
		break;
	}
  }//end correct (error handler)
}

//=======================================================================
//	DISPLAY-SCORE-BOARD()This function is used to display the score board
//						 the score board will display players name and
//						 current score;
//=======================================================================

void Scrabble::diplayScoreBoard(Scrabble *ps, TileBag *tileBag)
{
	int col=61;	 //output positioning
	int row=0;
	con.setForeground(Yellow);//set text colour
//------------------------------------------------------
	//used to display a vertical line on the screen
	for(int line=0;line<20;line++)
	{
		con.goto_XY(60,line);

		cout<<"|";
	}

	con.goto_XY(61,12);
	cout<<"=======================";
	con.goto_XY(65,13);
	cout<<"Tile Bag";
	dispTbag(tileBag);
//------------------------------------------------------
	//diplay the players information()
	for(std::vector<int>::size_type dsb=0; dsb<ps->players.size(); dsb++)
	{
		con.setForeground(LtGreen);
		con.goto_XY(col,row);//set postion
		cout<<"Name:";
		cout<<" ";
		con.setForeground(Yellow);
		ps->players[dsb].displayName();	//display name
		row++;							//move down one row
		con.setForeground(LtGreen);
		con.goto_XY(col,row);
		cout<<"Score:";				   //display players score
		cout<<" ";
		con.setForeground(Yellow);
		ps->players[dsb].displayScore();
		row++;							//move down one row
		con.goto_XY(col,row);
		cout<<"-----------------------";
		row++;							//move down one row
	}

  con.setForeground(LtGreen);	 //put colours back to normal
}


//=======================================================================
//	EXCHANGETILE()This function is used to allow a player to change
//				  any tiles they wish from their rack.
//=======================================================================

void Scrabble::exchangeTile(Scrabble *ps, TileBag *tileBag)
{
	vector<Tile> temp;	//temp tile holder
	bool corect=false;	// error handler variable
	Tile tile; 			// temp tile;
	con.setBackground(bBlue);
	con.goto_XY(2,20);

	while(!corect)// error handler
	{
		char buffer[8]={0,0,0,0,0,0,0,0};	//create char buffer
		con.ClearSect(2,20);   //screen manipulation
		con.goto_XY(2,20);
		cout<<"To go back to the menu enter ( 1 ) or";
		con.goto_XY(2,21);
		cout<<"Please enter the letters you wish to exchange: ";
		cin >> xchword;	  //get the stirng of letters to be changed
		istringstream LineStream(xchword);	//convert string to char
		LineStream >> buffer;				//put chars into buffer
		if(buffer[0]=='1')
		{
			mistake=true;
			break;
		}
//------------------------------------------------------------------------
		//convet characters to uppercase
		for(std::vector<int>::size_type uper=0; uper<strlen(buffer);uper++)
		{	//check each char convet to uppercase
			buffer[uper]=toupper(buffer[uper]);
		}
//------------------------------------------------------------------------
		 //search the players rack for the tile to be exchanged
		int bufPos=0;
		for(std::vector<int>::size_type  c =0; c<strlen( buffer ); c++)//lol
		{
			for(std::vector<int>::size_type pos=0; pos<(*ps).players[ps->turn].getRack().getTiles().size();pos++)
			{
				char tmp;//hold the tiles char for comparison
				tile=players[ps->turn].getRack().getTiles()[pos]; //get tile info
				tmp = tile.getLetter();//set char value
				if(buffer[bufPos]==tmp)//compare buffer pos with char
				{ 	//if the same put tile into temp vector
					temp.push_back(tile);
					(*ps).players[ps->turn].getRack().eraseTile(tmp);//del rack item
					break;//get out else will delete all instances of that tile
				}
			}  //end inner loop
			bufPos++;//next buffer positon(forgoten why put this here)
		}//end outer loop
//--------------------------------------------------------------------------------
		//check buffer and temp vector size size
	if(strlen( buffer )!=temp.size())
	{	//if not put it all back
		for(std::vector<int>::size_type rtn=0; rtn<temp.size(); rtn++)
		 {
			 tile=temp[rtn]; //put all tiles back
			 (*ps).players[ps->turn].getRack().getTiles().push_back(tile);
		 }
		temp.clear(); //error message

		con.setForeground(LtRed);
		cout<<"sorry but you have made a mistake"<<endl;
		cout << "You have enterd letters you do not have"<<endl
			<<"please try again"<< flush;
		con.setForeground(Yellow);
		Sleep(4000);
		 cout<<flush;
	}
	else //success, tile have been swapped
	{
		tileBag->addTile(temp);
		corect=true;

	}
	} //end error handler
}

//=======================================================================
//	SETMOVE()This function is used to call all the inputs from the player
//		will add more features to this section latter;(if wrong choice)
//=======================================================================

void Scrabble::setMove(Scrabble *ps, Board * boa)
{
	con.setBackground(bBlue);  //screen formatting
	con.setForeground(Yellow);
	con.ClearSect(0,20);
	con.goto_XY(2,20);
	validatePos();//call validate pos
	con.goto_XY(2,21);
	validateDir();//call validate dir
	validateWord( ps, boa);//call validate word

}


//=======================================================================
//	VALIDATEWORD()This function is used to validate the word the player
//				  wishes to play
//=======================================================================


void Scrabble::validateWord(Scrabble *ps ,Board *boa)
{
	vector<Tile> temp; //temp vector
	Tile tile; 		   //temp tile
	bool legal;		   // boolean for leagal moves
	bool corect=false; //error handler loop
	while(!corect)	   //start error handler
	{
		con.ClearSect(0,22);
		con.goto_XY(2,22);
		cout<<"To go back to the menu enter ( 1 ) or";
		con.goto_XY(2,23);
		cout<<"Please enter the word you wish to play: ";
		cin >> playWord;	  //get the entered word
		char buffer[8]={0,0,0,0,0,0,0,0};	  //set and clear buffer
		istringstream LineStream(playWord);	//convert input
		LineStream >> buffer;				//put it in the buffer
		if(buffer[0]=='1')
		{
			mistake=true;
			break;
		}

		for(std::vector<int>::size_type uper=0; uper<strlen(buffer);uper++)
		{	//convert to upper case letters
			buffer[uper]=toupper(buffer[uper]);
		}

		int i=0; //buffer varialbe
	//---------------------------------------------------------------------------------
	for(std::vector<int>::size_type c =0; c<strlen( buffer ); c++)
	{	 	// loop through the buffer
		for(std::vector<int>::size_type pos=0; pos<(*ps).players[ps->turn].getRack().getTiles().size();pos++)
		{ 	 //search the rack
			char tmp;// hold tiles letter
			tile=players[ps->turn].getRack().getTiles()[pos];
			tmp = tile.getLetter();
			if(buffer[i]==tmp)	 //compare the characters
			{ 	 //if same add it to the temp vector
				temp.push_back(tile);
				(*ps).players[ps->turn].getRack().eraseTile(tmp);//del racks tile
				break; //get out or will del all instances
			}
		}  //end inner

		i++; //step through the buffer
	}//end outer

	//---------------------------------------------------------------------------------
	if(strlen( buffer )!=temp.size() )// || (legal!=true))
	{	 //if mistake
		for(std::vector<int>::size_type rtn=0; rtn<temp.size(); rtn++)
		 {	 //return tiles to the players rack
			 tile=temp[rtn];
			 (*ps).players[ps->turn].getRack().getTiles().push_back(tile);

		 }
		//error message
		con.setForeground(LtRed);
		cout<<"sorry but you have mad a mistake"<<endl;
		cout << "You have enterd letters you do not have"<<endl
			<<"please try again"<< flush;
		con.setForeground(Yellow);
		Sleep(4000);//timer
		cout<<flush;

		temp.clear(); //clear temp vector
	} //end if
	else
	{	 //if all is good
		corect=true;  //switch error flag

		 legal=boa->placeTile(row, col, direction,temp);
		 //set to the board for validation
		 if(legal==false)
		 {	//if returns false, invalid
			for(std::vector<int>::size_type rtn=0; rtn<temp.size(); rtn++)
			{	//return tiles to the players rack
				tile=temp[rtn];
				(*ps).players[ps->turn].getRack().getTiles().push_back(tile);
			}
			 //error message   may move latter to error class:-)
			con.setForeground(LtRed);
			cout<<"you have made an error the word you wish to play ILLEGAL!!"
				<<endl<<"YOU LOSE A TURN"<<flush;
			con.setForeground(Yellow);
			Sleep(4000);
			cout<<flush;
		 }// end if
//--------------------------------------------------------------------------------
		 //if all goes well add to the player score
		(*ps).players[ps->turn].setScore(boa->getScore());
		boa->displayBoard(); //display the board
		temp.clear(); //clear the temp vector

	} //end else
  }	 //end error handler
}  //end function

//=======================================================================
//	VALIDATEDIR()This function is used to validate direction the player
//				wishes to lay thier word
//=======================================================================

void Scrabble::validateDir()
{
	bool correct=false;//error handler flag
	while(!correct)	   //start error handler
	{	con.ClearSect(2,21);
		con.goto_XY(2,21);
		cout<<"please enter [V]ertical or [H]orizontal: ";
		cin >> direction;  //get direction
		direction = toupper(direction);	//set to uppercase

		if(direction=='H'|| direction=='V')
		{ //check direction
			correct=true;
		}

		if(correct==false)	//if invalid input
		{	con.setForeground(LtRed);// error message
			cout<<endl<<"you have entered a non existing direction"<<endl;
			cout<<"Please only enter [H] or [V]"<< flush;
			con.setForeground(Yellow);
			Sleep(2000);
			cout<<flush;
		}
	}//end error handler correct
}

//=======================================================================
//	VALIDATEPOS()This function is used to validate the position the
//				player wishes to place their word. it makes sure they
//				stay within the board, and the input is in the correct
//				format.
//=======================================================================

void Scrabble::validatePos()
{
	unsigned int hor;		//holds horizontal pos
	unsigned char vert;		// hold vertical pos
	bool correct=false;		// error flag
	while(!correct)			//start error handler
	{
		con.ClearSect(0,20);
		con.goto_XY(2,20);
		cout<<"please enter start Postion eg[7H]: ";
		cin >>moveXY;		 //get input
		istringstream LineStream(moveXY);
		LineStream >>hor>> vert;  //split the input
		row=hor;				 //assign h pos
		vert=toupper(vert);		 //convert and assign v pos
		col=vert-65;			 //convert to integer and make bounds
	//------------------------------------------------------------------
		//check bounds of the input
		if((row <= 14) && (col <=14) && (row >= 0)&&(col >= 0))
			correct =true;

		if(correct==false) //if bad input disp error message
		{
			con.setForeground(LtRed);
			cout<<endl<<"you have entered a NON existing position OR WRONG FORMAT"<<endl;
			cout<<"please only enter direction in the shown format"<<endl;
			cout<<"thanks"<< flush;
			con.setForeground(Yellow);
			Sleep(3000);
		}

	}//end correct
}

//=======================================================================
//	RULES()	This function is used to display the playing rules to the
//			player.
//=======================================================================
void Scrabble::rules()
{	 //display the rules
	con.setBackground(bWhite);
	con.setForeground(LtBlue);
	con.ClearScreen();
	con.goto_XY(40,2);
	cout<<"RULES"<<endl;
	cout<<" Here are the rules of Scrable";
	con.goto_XY(5,5);
	cout<<"1. The player with a tile that is closest to 'A' goes first";
	con.goto_XY(5,6);
	cout<<"2. Each player recieves seven tiles to use in their rack";
	con.goto_XY(5,7);
	cout<<"3. The first word played gets double the score";
	con.goto_XY(5,8);
	cout<<"4. The first word played must touch the centre square.";
	con.goto_XY(5,9);
	cout<<"5. All other words must make contact with another word";
	con.goto_XY(5,10);
	cout<<"6. If an illeagal move is detected the player will lose their current turn";
	con.goto_XY(5,11);
	cout<<"7. The computers decision is final!!";
	con.goto_XY(5,12);
	cout<<"8. If all players skip a turn it will end the game.";
	con.goto_XY(5,13);
	cout<<"9. Any tiles remaining in the players rack will be";
	con.goto_XY(9,14);
	cout<<"deducted from thier final score";
	con.goto_XY(5,15);
	cout<<"10. The game ends when all tiles are used from the bag and";
	con.goto_XY(9,16);
	cout<<"none of the players can move";
	con.goto_XY(25,20);
	con.setBackground(Black);
	con.setForeground(LtCyan);
	cout<<" PRESS ANY KEY TO CONTINUE ";
	cout<<flush;
	while ( !_kbhit() ) {  //wait for keyboard input
		// Busy wait
	}
	_getch();  //consume the keypress
}

//=======================================================================
//	FAREWELL()	This function is used to display farewell message to the
//				players and show thier final scores minus penalty
//=======================================================================

void Scrabble::Farewell(Scrabble *ps)
{	int col=15;	  //screen formatting
	int row=6;

	concol con;
	con.setBackground(bLtCyan);
	con.setForeground(LtBlue);
	con.ClearScreen();
	con.goto_XY(35,2);
	cout<<"GAME RESULTS"<<endl;
	con.goto_XY(25,4);
	cout<<"Thanks for playing I hope you had fun";
	con.goto_XY(15,6);
	//--------------------------------------------------------------
	//my dreaded bubble sort agin	puts players in order of score
	if(ps->players.size()==2)
	{ //if only 2 players check and swap if necaeesary
		if(ps->players[0].getScore() < ps->players[1].getScore())
		swap(ps->players[0],ps->players[1]);
	}
	else
	{//go sort them all.
		for(int out = ps->players.size()-1; out > 0; out-- )  // FIXED: was out > 1 (caused last pass to be skipped!)
		{
			for (int in=0; in<out;in++)//inner loop runs forward
			{
				if(ps->players[in].getScore() < ps->players[in+1].getScore())
					swap(ps->players[in],ps->players[in+1]);//if out of order
														//swap them
			}
		}
	}
	//display the stats
	for(std::vector<int>::size_type disp=0; disp<ps->players.size();disp++)
	{
		int temp=0; //used to hold penalty amount
		temp=ps->players[disp].getRack().returnScore();//get score left in players rack
		ps->players[disp].penalty(temp); //apply penalty to the player
		//this next bit is self explanitory
		con.goto_XY(col,row);
		cout <<"Players Name:";
		ps->players[disp].displayName();
		row++;
		con.goto_XY(col,row);
		cout << "final score:";
		ps->players[disp].displayScore();
		row+=2;//move down two places
	}
		con.goto_XY(25,20);
		con.setBackground(Black);
		con.setForeground(LtGreen);
		cout<<" PRESS ANY KEY TO EXIT ";
	  	while ( !_kbhit() );   //wait for key press and exit

}
//=======================================================================
//	ADDPLAYER()	This function is used to add a new player to the
//				player vector.
//=======================================================================

void Scrabble::addPlayer(Player newPlayer)
{
	players.push_back(newPlayer);
}


//=======================================================================
//	DISPTBAG()	This function is used to display a poor looking ASCII
//				bag on to the screen and indicate how many tiles are
//				left in the bag.
//=======================================================================
void Scrabble::dispTbag(TileBag *tileBag)
{
	con.goto_XY(68,14);
	cout<<tileBag->numTiles();//get amount tiles left in the bag
	con.setForeground(LtMagenta);
	int row=15;
	/*con.goto_XY(65,15);
	cout<<"__________";
	con.goto_XY(65,17);
	cout<<"----------";	*/
	con.goto_XY(65,18);
	cout<<"Status Bar";
	con.goto_XY(63, 16);
	cout<<"F|          |E";

	con.setBackground(bLtCyan);
	row=16;	// start positions
	int length=75;

	for(size_t draw=0; draw<tileBag->numTiles(); draw++)
	{
		if(draw%10 ==0)
		{
			length--; 	//reduce bar length
			con.goto_XY(length,row);
			cout<<" ";
		}
	}
	con.setBackground(bLtBlue);//reset colour
}
Scrabble::~Scrabble()
{

}

