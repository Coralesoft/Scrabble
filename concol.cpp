// concol.cpp: implementation of the concol class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		Purpose	:	Provide GUI function for C/C++ Programs						 **
**		Version	:	1.2															 **
**		St_num	:	     														 **
**		History	:   have made this version more generalised and					 **
**					improved naming conventions. Still would like to improve the **
**					colour selection choice and should be improved next version  **
**					Added Orange to the color scheme( ugly)						 **
**					FIXED warnings when using light background colours			 **
**					I have not commented this file as it is only for screen		 **
**					manipulation and has is not part of the assignment 			 **
**					requirements												 **
 *********************************************************************************/
#include "concol.hpp"
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

concol::concol()
{

}
//===============================================================================
short concol::getPosY()
	{	 //gets screen info and returns the Y coordinate
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hCon;
		hCon = getBufferOut();
		GetConsoleScreenBufferInfo(hCon, &csbi);
		return(csbi.dwSize.Y);
	}
//===============================================================================
short concol::getPosX()
	{	//gets screen info and returns the X coordinate
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		HANDLE hCon =getBufferOut();
		GetConsoleScreenBufferInfo(hCon, &csbi);
		return(csbi.dwSize.X);
	}
//===============================================================================
void concol::resizeWindow(short xSize, short ySize)
{	// gets the screen buffer information
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT srWindowRect;
	COORD coordScreen;
	HANDLE hConsole=getBufferOut();
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	coordScreen = GetLargestConsoleWindowSize(hConsole);
	srWindowRect.Right = (SHORT) (std::min((int)xSize, (int)coordScreen.X) - 1);
	srWindowRect.Bottom = (SHORT) (std::min((int)ySize, (int)coordScreen.Y) - 1);
	srWindowRect.Left = srWindowRect.Top = (SHORT) 0;
	coordScreen.X = xSize;	//reset size measurements
	coordScreen.Y = ySize;

	if ((DWORD) csbi.dwSize.X * csbi.dwSize.Y > (DWORD) xSize * ySize)
    {	//if size different reset
		SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
		SetConsoleScreenBufferSize(hConsole, coordScreen);
    }
	if ((DWORD) csbi.dwSize.X * csbi.dwSize.Y < (DWORD) xSize * ySize)
    {
		SetConsoleScreenBufferSize(hConsole, coordScreen);
		SetConsoleWindowInfo(hConsole, TRUE, &srWindowRect);
    }
  return;
}
//===============================================================================
void concol::ClearScreen()
{		//clear screeen
		COORD coordScreen = { 0, 0 }; //start top left hand
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;
		HANDLE hConsole= getBufferOut();
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',//fill screen with blanks
		dwConSize, coordScreen, &cCharsWritten);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(hConsole, coordScreen); //reset cursor pos

}
//===============================================================================
void concol::ClearSect(short X, short Y)
{		//i wrote this to create a panneled feel to the game
		COORD coordScreen= { X, Y };//set your start pos,
		DWORD cCharsWritten;		//clear all after it
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		DWORD dwConSize;
		HANDLE hConsole= getBufferOut();
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
		FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);
		SetConsoleCursorPosition(hConsole, coordScreen);

}
//===============================================================================
void concol::setColour(int fore, int back)
{	//seting the screen colors
	HANDLE  hConsole;
	static int BackGround; //used static because it allowed me
	static int ForeGround; // to change which ever element i wanted
	if(back==-1)		   //without effecting the other
	back = BackGround;
	BackGround=back;
	if (fore ==-1)
	fore =ForeGround;
	ForeGround=fore;
	hConsole = CreateFile(
        "CONOUT$", GENERIC_WRITE | GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);
		SetConsoleTextAttribute( hConsole, (WORD) ( (BackGround) |
                               ForeGround) );
}
//===============================================================================

void concol::goto_XY(short X_in, short Y_in)
	{
		//simple goto to set cursor positon
		COORD coordScreen;
		HANDLE hCon= getBufferOut();
		coordScreen.X = X_in;
		coordScreen.Y = Y_in;
		SetConsoleCursorPosition(hCon,coordScreen);
	}

//===============================================================================

void concol::setBackground(int back)
{	//as the name says
	int fore=-1;
	setColour(fore,back);
}
//===============================================================================

void concol::setForeground(int fore)
{
	int back=-1;
	setColour(fore,back);
}
//===============================================================================

concol::~concol()
{

}
