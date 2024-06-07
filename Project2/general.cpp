#include "general.h"
#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "gameConfig.h"



//takes cursore to x,y position of screen
void gotoxy(const int x, const int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

//clears screen
void clrscr()
{
	system("cls");
}

//hides the cursor
void ShowConsoleCursor(const bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

//sets color for printing
void setColor(const int backcolor, const bool activeColors)
{
	if (activeColors)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backcolor);
	}
}