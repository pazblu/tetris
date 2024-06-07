#include "point.h"
#include "gameConfig.h"
#include "general.h"

#include <iostream>
#include <Windows.h>



// Set the initial position and direction of the point
void point::set(int x, int y)
{
	this->x = x;
	this->y = y;
}


int point::getX() const
{
	return x;
}


int point::getY() const
{
	return y;
}

// Draw the point at a specified position with a given background color and character
void point::draw(const int Xval, const int Yval, const int backcolor, const bool activeColors, const char ch) const
{
	backcolor + 1;
	setColor(backcolor, activeColors);
	gotoxy(x + Xval + 1, (gameConfig::GAME_HEIGHT - y) + Yval);
	std::cout << ch;
}

// Move the point based on the specified key (LEFT, RIGHT, or DOWN)
void point::move(const gameConfig::eKeys key)
{
	switch (key)
	{
	case gameConfig::eKeys::LEFT:
		diff_x = -1;
		diff_y = 0;
		break;
	case gameConfig::eKeys::RIGHT:
		diff_x = 1;
		diff_y = 0;
		break;
	case gameConfig::eKeys::DOWN:
		diff_x = 0;
		diff_y = -1;
		break;
	}

	x += diff_x;

	y += diff_y;
}