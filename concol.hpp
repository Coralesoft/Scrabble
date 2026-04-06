// concol.hpp: interface for the concol class.
//
//////////////////////////////////////////////////////////////////////
/*********************************************************************************
**		Author	:	C.Brown	  (c)COPYRIGHT C.Brown 2001-2026 ALL RIGHTS RESERVED	 **
**		Date	:	19/09/2001													 **
**		Purpose	:	Provide GUI function for C/C++ Programs						 **
**		Version	:	1.2 														 **
**		St_num	:	        													 **
**		History	:	have made this version more generalised and					 **
**					improved naming conventions. Still would like to improve the **
**					colour selection choice and should be improved next version  **
**					Added Orange to the color scheme(bloody ugly)				 **
**					FIXED warnings when using light background colours			 **
 *********************************************************************************/
#if !defined(AFX_CONCOL_HPP__763B0EF1_655E_402B_9E8F_7DED1AE186B4__INCLUDED_)
#define AFX_CONCOL_HPP__763B0EF1_655E_402B_9E8F_7DED1AE186B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Include Windows headers first to avoid std::byte conflicts
#define _HAS_STD_BYTE 0
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#define  Black		0
#define  Blue		FOREGROUND_BLUE
#define  Red		FOREGROUND_RED
#define  Green		FOREGROUND_GREEN
#define  Cyan		FOREGROUND_GREEN | FOREGROUND_BLUE
#define  Magenta	FOREGROUND_RED | FOREGROUND_BLUE
#define  Orange		FOREGROUND_GREEN | FOREGROUND_RED
#define  DkGray		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define  LtGray		FOREGROUND_INTENSITY
#define  LtRed		FOREGROUND_INTENSITY | FOREGROUND_RED
#define  LtGreen	FOREGROUND_INTENSITY | FOREGROUND_GREEN
#define  LtBlue		FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define  LtCyan		FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE
#define  LtMagenta	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE
#define  Yellow	    FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN
#define  White  	FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#define  bBlue		BACKGROUND_BLUE
#define  bRed		BACKGROUND_RED
#define  bGreen		BACKGROUND_GREEN
#define  bCyan		BACKGROUND_GREEN | BACKGROUND_BLUE
#define  bMagenta	BACKGROUND_RED | BACKGROUND_BLUE
#define  bOrange	BACKGROUND_RED | BACKGROUND_GREEN
#define  bDkGray	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define  bLtGray	BACKGROUND_INTENSITY
#define  bLtRed		BACKGROUND_INTENSITY | BACKGROUND_RED
#define  bLtGreen	BACKGROUND_INTENSITY | BACKGROUND_GREEN
#define  bLtBlue	BACKGROUND_INTENSITY | BACKGROUND_BLUE
#define  bLtCyan	BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE
#define  bLtMagenta	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE
#define  bYellow  BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN
#define  bWhite  	BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE

class concol
{

public:
	concol();
	short getPosX();
	short getPosY();
	void setBackground (int back);
	void setForeground(int fore);
	void setColour(int fore, int back);
	void goto_XY(short X_in, short Y_in);
	void ClearSect(short X, short Y);
	void ClearScreen();
	void resizeWindow(short xSize, short ySize);

	HANDLE getBufferOut()
	{	//this is used in each section put it here for speed
		HANDLE hCon;
		hCon =  GetStdHandle(STD_OUTPUT_HANDLE);
		return hCon;
	}
	virtual ~concol();

};

#endif //
