#pragma once

#include "gameConfig.h"

// Class representing a point in the game
class point
{
private:
	int x = -1;
	int y = -1;
	int diff_x;  // Difference in the X-coordinate for movement
	int diff_y;  // Difference in the Y-coordinate for movement

public:
	// Set the initial position and direction of the point
	void set(int x, int y);

	int getX() const;
	int getY() const;

	// Draw the point at a specified position with a given background color and character
	void draw(const int Xval = 0, const int Yval = 0, const int backcolor = 0, const bool activeColors = true, const char ch = gameConfig::POINT_CHAR) const;

	// Move the point based on the specified key (LEFT, RIGHT, or DOWN)
	void move(const gameConfig::eKeys key);
};