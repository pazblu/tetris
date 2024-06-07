#pragma once

//takes cursore to x,y position of screen
void gotoxy(const int x, const int y);

//clears screen
void clrscr();

//hides the cursor
void ShowConsoleCursor(const bool showFlag);

//sets color for printing
void setColor(const int backcolor, const bool activeColors);