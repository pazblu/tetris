#pragma once

#include "board.h"
#include "general.h"
#include <iostream>
#include "gameConfig.h"
#include "point.h"
#include <Windows.h>




void board::setActiveColor(const bool isActive)
{
	activeColors = isActive;
}

// Set the starting coordinates of the board
void board::setBorderStart(const int x, const int y)
{
	start_x = x;
	start_y = y;
}

// Get the starting X-coordinate of the board
int board::getStartX() const
{
	return start_x;
}

// Get the starting Y-coordinate of the board
int board::getStartY() const
{
	return start_y;
}

// Draw the border around the game board according to X,Y placement of board
void board::drawBorderSomwhere() const
{
	setColor((int)gameConfig::COLORS::WHITE, activeColors);

	for (int col = start_x; col <= gameConfig::GAME_WIDTH + start_x + 1; col++)
	{
		gotoxy(col, start_y);
		std::cout << "-";

		gotoxy(col, gameConfig::GAME_HEIGHT + start_y + 1);
		std::cout << "-";
	}

	for (int row = start_y + 1; row <= gameConfig::GAME_HEIGHT + start_y; row++)
	{
		gotoxy(start_x, row);
		std::cout << "|";

		gotoxy(gameConfig::GAME_WIDTH + start_x + 1, row);
		std::cout << "|";
	}
}

// Draw the points on the board
void board::drawPointsSomwhere() const
{
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < gameConfig::GAME_WIDTH; j++)
		{
			// Set the cursor position on the console
			gotoxy(start_x + j + 1, start_y + gameConfig::GAME_HEIGHT - i);

			// Check if the point is empty
			if (this->board[i][j] == gameConfig::EMPTY_POINT)
			{
				// Set the color to black for an empty point and print the empty point character
				setColor((int)gameConfig::COLORS::BLACK, activeColors);
				std::cout << (char)gameConfig::EMPTY_POINT;
			}
			else
			{
				// Print the point character and set the color based on the point's color
				setColor(this->board[i][j], activeColors);
				std::cout << (char)gameConfig::POINT_CHAR;
			}
		}
	}
}

// Clear the entire game board by setting all points to empty and resetting pixelRowCount
void board::cleanBoard()
{
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < gameConfig::GAME_WIDTH; j++)
		{
			this->board[i][j] = gameConfig::EMPTY_POINT;
		}
		this->pixelRowCount[i] = 0;
	}
}

// Check if a point can move to the right
bool board::checkIfPointCanGoRight(const point& p) const
{
	if (p.getX() + 1 < gameConfig::GAME_WIDTH)
	{
		if (this->board[p.getY()][p.getX() + 1] == gameConfig::EMPTY_POINT) //if one spot right is clear it can move
			return true; //continue - can move
		else
			return false; //stop - can not move
	}
	else
	{
		return false; //point reached right edge of board
	}
}

// Check if a shape can move to the left
bool board::checkIfShapeCanGoRight(const shape& s) const
{
	bool checkRight = true;
	for (int i = 0; i < 4; i++)
	{
		// If any point cannot move down, set checkRight to false
		if (checkIfPointCanGoRight(s.getPointsArr()[i]) == false)
		{
			checkRight = false;
		}
	}
	return checkRight;
}

// Move a shape to the right if all constituent points can move to the right
bool board::shapeGoRight(shape& S)
{
	bool checkRight = checkIfShapeCanGoRight(S);
	
	if (checkRight)
	{
		S.move(gameConfig::eKeys::RIGHT); // moves the shape if it can move
		return true;
	}
	else
	{
		return false;
	}
}

// Check if a point can move to the left
bool board::checkIfPointCanGoLeft(const point& p) const
{
	if (p.getX() - 1 >= 0)
	{
		if (this->board[p.getY()][p.getX() - 1] == gameConfig::EMPTY_POINT) //if one spot left is clear it can move
			return true; //continue - can move
		else
			return false; //stop - can not move
	}
	else
	{
		return false; //point reached left edge of board
	}
}

// Check if a shape can move to the left
bool board::checkIfShapeCanGoLeft(const shape& s) const
{
	bool checkLeft = true;
	for (int i = 0; i < 4; i++)
	{
		// If any point cannot move down, set checkLeft to false
		if (checkIfPointCanGoLeft(s.getPointsArr()[i]) == false)
		{
			checkLeft = false;
		}
	}
	return checkLeft;
}

// Move a shape to the left if all constituent points can move to the left
bool board::shapeGoLeft(shape& S)
{
	// Check each point of the shape if it can move to the down
	bool checkLeft = checkIfShapeCanGoLeft(S);
	if (checkLeft)
	{
		S.move(gameConfig::eKeys::LEFT); //moves the shape if it can move
		return true;
	}
	else
	{
		return false;
	}
}

//For cube to know when to stop while free falling, and also used by down arrow to know to stop
bool board::checkIfPointCanGoDown(const point& p) const
{
	// Check if the next row below is within the board bounds
	if (p.getY() - 1 >= 0)
	{
		if (this->board[p.getY() - 1][p.getX()] == gameConfig::EMPTY_POINT)
			return true; //can go down
		else
			return false; // stop - a block is there
	}
	else
	{
		return false; // stop - reached bottom of board
	}
}

// Move a shape down if all constituent points can move down
bool board::shapeGoDown(shape& S)
{
	bool checkDown = true;
	for (int i = 0; i < 4; i++)
	{
		if (checkIfPointCanGoDown(S.getPointsArr()[i]) == false)
		{
			checkDown = false;
		}
	}
	if (checkDown)
	{
		S.move(gameConfig::eKeys::DOWN);
	}
	return checkDown; //true if went down by one false if blocked and stopped
}

// Check if a point is within the board boundaries and the corresponding spot is empty
bool board::CheckifPointAvaliableOnBoard(const point& p) const
{
	// Check if the point is within the horizontal and vertical bounds of the board
	if (p.getX() > 0 && p.getX() < gameConfig::GAME_WIDTH && p.getY() > 0 && p.getY() < gameConfig::GAME_HEIGHT)
	{
		// Check if the spot on the board corresponding to the point is empty
		if (this->board[p.getY()][p.getX()] == gameConfig::EMPTY_POINT)
			return true; // space avaliable
		else
			return false; //stop - space is taken
	}
	else
	{
		return false; //point out of board
	}
}

// Check if an entire shape can fit within the board boundaries
bool board::CheckifShapeFitOnBoard(const shape& s) const
{
	bool isOk = true;
	for (int i = 0; i < 4; i++)
	{
		if (CheckifPointAvaliableOnBoard(s.getPointsArr()[i]) == false) //checks if one of the points doesnt fit and changes to not ok
		{
			isOk = false;
		}
	}
	return isOk;
}

// Add a shape to the board by updating the corresponding spots with the shape's color
void board::addShape(const shape& S)
{

	for (int i = 0; i < 4; i++)
	{
		this->board[S.getPointsArr()[i].getY()][S.getPointsArr()[i].getX()] = (char)S.getColor();
		this->pixelRowCount[S.getPointsArr()[i].getY()] += 1;
	}

}


// remove a shape to the board by updating the corresponding spots with blank
void board::removeShape(const shape& S)
{
	for (int i = 0; i < 4; i++)
	{
		this->board[S.getPointsArr()[i].getY()][S.getPointsArr()[i].getX()] = gameConfig::EMPTY_POINT;
		this->pixelRowCount[S.getPointsArr()[i].getY()] -= 1;
	}
}

// Clear full rows on the board and update the score based on the number of cleared rows
int board::clearFullRows()
{
	int numofcleardrows = 0;
	int read;
	int write = 0;

	// Iterate through each row on the board
	for (read = 0; read < gameConfig::GAME_HEIGHT; read++)
	{
		// Check if the current row is full
		if (pixelRowCount[read] == gameConfig::GAME_WIDTH)
		{
			numofcleardrows += 1; //updates the num of full rows found by read index that runs on rows one time
		}

		// Shift the non-full rows down in the board and update pixelRowCount
		if (pixelRowCount[write] != gameConfig::GAME_WIDTH)
		{
			write++; //write can continue it is not full
		}
		else //if write position row is full and needs to be swiched
		{
			if (pixelRowCount[read] != gameConfig::GAME_WIDTH)
			{
				// Shift the pixel count and row content to fill the cleared row, takes the full row up
				pixelRowCount[write] = pixelRowCount[read];
				pixelRowCount[read] = gameConfig::GAME_WIDTH;

				for (int i = 0; i < gameConfig::GAME_WIDTH; i++)
				{
					board[write][i] = board[read][i];
				}

				write++;
			}
		}
	}

	// If there are cleared rows, clean the rest of the board with the filled rows that are now above the other rows, and then prints board
	if (numofcleardrows != 0)
	{
		while (write < gameConfig::GAME_HEIGHT)
		{
			for (int i = 0; i < gameConfig::GAME_WIDTH; i++)
			{
				board[write][i] = gameConfig::EMPTY_POINT; //cleans the full rows
			}
			pixelRowCount[write] = 0;

			write++;
		}

		//prints board again ONLY if it was updated to avoid unneccecery printing
		PrintClearBoard();
		drawPointsSomwhere();
	}

	// Return the score based on the number of cleared rows
	switch (numofcleardrows)
	{
	case 0:
		return 0;
	case 1:
		return 100;
	case 2:
		return 250;
	case 3:
		return 450;
	case 4:
		return 750;
	default:
		break;
	}


}

// Print an empty board with black spaces to clear the display
void board::PrintClearBoard() const
{
	for (int i = 0; i < gameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < gameConfig::GAME_WIDTH; j++)
		{
			setColor((int)gameConfig::COLORS::BLACK, activeColors);
			gotoxy(start_x + j + 1, start_y + gameConfig::GAME_HEIGHT - i);
			std::cout << (char)gameConfig::EMPTY_POINT;
		}
	}
}

// Check if the top row of the board is clear (no blocks)
bool board::topIsClear() const
{
	if (pixelRowCount[gameConfig::GAME_HEIGHT - 1] != 0)
		return false;
	return true;
}

// Move the shape on the board based on the specified option
void board::move(int option, shape& s)
{
	switch (option)
	{
	case (int)gameConfig::eKeys::LEFT:
		shapeGoLeft(s);
		break;
	case (int)gameConfig::eKeys::RIGHT:
		shapeGoRight(s);
		break;
	case (int)gameConfig::eKeys::ROTATE:
		if (s.getType() != (int)gameConfig::shapeType::O) //if the shape is o it doesnt rotate
		{
			rotateInBoard(s);
		}
		break;
	case (int)gameConfig::eKeys::ROTATE_COUNTERCLOCKWISE:
		if (s.getType() != (int)gameConfig::shapeType::O) //if the shape is o it doesnt rotate
		{
			rotateCounterwizeInBoard(s);
		}
		break;

	}
}

void board::rotateInBoard(shape& s) //rotates the shape if it can be done in its placment on board
{
	shape tempS = s;
	tempS.rotateClockwise();
	if (CheckifShapeFitOnBoard(tempS)) //checks if the rotated shape fits and doesnt collide with other blocks or border
	{
		s.rotateClockwise(); //updates rotation when it does fit
	}
}

void board::rotateCounterwizeInBoard(shape& s)
{
	shape tempS = s;
	tempS.rotateCounterClockwise();
	if (CheckifShapeFitOnBoard(tempS)) //checks if the rotated shape fits and doesnt collide with other blocks or border
	{
		s.rotateCounterClockwise(); //updates rotation when it does fit
	}
}

//counts the rows deleted without deleting them
int board::numOfRowsDeleted() 
{
	int countRows = 0;
	for (int i = 0; i < 18; i++)
	{
		if (pixelRowCount[i] == 12)
		{
			countRows++;
		}
	}

	return countRows;
}

//returns max height of board
int board::maxHeight()
{
	int height = 0;

	while (pixelRowCount[height] != 0)
	{
		height++;
	}

	return height;
}

//counts unaccesible blocks
int board::unaccesibleBlocks()
{

	int countBlockedOverall = 0;
	bool thereWasABlock;


	for (int col = 0; col < gameConfig::GAME_WIDTH ; col++)
	{
		thereWasABlock = false;
		for (int row = gameConfig::GAME_HEIGHT - 1; row >= 0 ; row--)
		{
			if (board[row][col] != gameConfig::EMPTY_POINT && thereWasABlock == false)
			{
				thereWasABlock = true;
			}
			else if(board[row][col] == gameConfig::EMPTY_POINT && thereWasABlock == true)
			{
				countBlockedOverall++;
			}
		}
	}

	return countBlockedOverall;

}

//activates bomb on board with animation
void board::activateBomb(const point& Center)
{
	const int bomb_radios = 4;
	const int x = Center.getX();
	const int y = Center.getY();
	int runTillPointIsDown;
	int howMuchDown = bomb_radios;
	int howMuchUp = bomb_radios;
	int howMuchLeft = bomb_radios;
	int howMuchRight = bomb_radios;

	if (gameConfig::GAME_HEIGHT - 1 - Center.getY() < bomb_radios)
	{
		howMuchUp = gameConfig::GAME_HEIGHT - 1 - Center.getY();
	}

	if (Center.getY() < bomb_radios)
	{
		howMuchDown = Center.getY();
	}

	if (gameConfig::GAME_WIDTH - 1 - Center.getX() < bomb_radios)
	{
		howMuchRight = gameConfig::GAME_WIDTH - 1 - Center.getX();
	}

	if (Center.getX() < bomb_radios)
	{
		howMuchLeft = Center.getX();
	}






	for (int col = x - howMuchLeft; col <= x + howMuchRight; col++)
	{

		for (int row = y - howMuchDown; row <= y + howMuchUp; row++)
		{
			if (   abs(col - x) == 0 || abs(row - y) == 0 || (abs(col - x) == 2 && abs(row - y) == 2)   ||  (abs(col - x) == 1 && ((abs(row - y) == 3) || (abs(row - y) == 2) || (abs(row - y) == 1)))      ||        (abs(row - y) == 1 && ((abs(col - x) == 3) || (abs(col - x) == 2) || (abs(col - x) == 1))))
			{
				if (board[row][col] != (char)gameConfig::EMPTY_POINT)
				{
					pixelRowCount[row]--;
				}

				board[row][col] = (char)gameConfig::EMPTY_POINT;
				gotoxy(col + start_x + 1, start_y + gameConfig::GAME_HEIGHT - row);
				setColor((int)gameConfig::COLORS::ORENGE, activeColors);
				std::cout << (char)gameConfig::POINT_CHAR;
				
			}
		}
	}


	Sleep(100);


	for (int col = x - howMuchLeft; col <= x + howMuchRight; col++)
	{

		for (int row = y - howMuchDown; row <= y + howMuchUp; row++)
		{

			if (abs(col - x) == 0 || abs(row - y) == 0 || (abs(col - x) == 2 && abs(row - y) == 2) || (abs(col - x) == 1 && ((abs(row - y) == 3) || (abs(row - y) == 2) || (abs(row - y) == 1))) || (abs(row - y) == 1 && ((abs(col - x) == 3) || (abs(col - x) == 2) || (abs(col - x) == 1))))
			{
				gotoxy(col + start_x + 1, start_y + gameConfig::GAME_HEIGHT - row);
				setColor((int)gameConfig::COLORS::BLACK, activeColors);
				std::cout << (char)gameConfig::EMPTY_POINT;
			}
		}
	}
	


}

//returns the col num of highest one
int board::maxHeightCol()
{
	int maxRow = maxHeight();
	for (int col = 0; col < gameConfig::GAME_WIDTH; col++)
	{
		if (board[maxRow - 1][col] != gameConfig::EMPTY_POINT)
		{
			return col;
		}
	}
}





