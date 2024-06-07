#pragma once
#include "point.h"
#include "shape.h"
#include "gameConfig.h"




class board
{
private:
	int start_x = 0, start_y = 0;
	char board[gameConfig::GAME_HEIGHT][gameConfig::GAME_WIDTH]; //rows start from level 0 to 17, cols are 0 to 11
	int pixelRowCount[gameConfig::GAME_HEIGHT];
	bool activeColors = true;

	// Private helper functions
	bool checkIfPointCanGoRight(const point& p) const;
	bool checkIfShapeCanGoRight(const shape& s) const;
	bool checkIfPointCanGoLeft(const point& p) const;
	bool checkIfShapeCanGoLeft(const shape& s) const;
	bool CheckifPointAvaliableOnBoard(const point& p) const;
	bool checkIfPointCanGoDown(const point& p) const; //for cube to know when to stop while free falling, and also used by down arrow to know to stop


public:
	// Getter functions
	int getStartX() const;
	int getStartY() const;

	// Setter function
	void setActiveColor(const bool isActive);
	void setBorderStart(const int x, const int y);

	// Drawing functions
	void drawBorderSomwhere() const;
	void drawPointsSomwhere() const;
	void PrintClearBoard()const;

	// Board manipulation functions
	void cleanBoard();
	bool shapeGoRight(shape& S);
	bool shapeGoLeft(shape& S);
	bool shapeGoDown(shape& S);
	void addShape(const shape& S);
	void removeShape(const shape& S);
	int clearFullRows();
	bool topIsClear() const;

	// Game movment mechanics functions
	void move(const int option, shape& s);
	bool CheckifShapeFitOnBoard(const shape& s) const;
	void rotateInBoard(shape& s);
	void rotateCounterwizeInBoard(shape& s);
	int numOfRowsDeleted();
	int maxHeight();
	int unaccesibleBlocks();
	void activateBomb(const point& Center);
	int maxHeightCol();
};