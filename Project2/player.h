#pragma once
#include "board.h"


class player
{

protected: 
	board _board;
	shape currShape;


private:
	int score;
	bool currentyFastFalling;
	bool isColorActive = true;



public:

	virtual ~player() {}

	// Handle the next falling frame of the player's shape, gets the num frame of the game (1-5, at fifth frame shapes go down)
	virtual void playerNextFallingFrame(const int frame) = 0;

	// Initialize the player with starting coordinates
	void initalize(int start_X, int start_y);

	void setActiveColors(const bool activeColors = true);

	// Draw the border for the player's gameplay area
	void drawPlayersBorder() const;

	// Generate a new random shape for the player
	void generateShape();

	// Check if the player is still in the game (not losing)
	bool not_losing() const;

	// Draw the player's game board
	void drawBoard() const;

	// Draw the current falling shape on the player's board
	void drawShape() const;

	// Clear the current falling shape from the player's board
	void clearShape() const;

	// Check if the current falling shape is still able to fall
	bool isFalling();

	// Add the current falling shape to the player's board
	void addShapeToBoard();

	// Print the player's board after clearing full rows
	void PrintClearBoard() const;

	// Clear full rows and update the player's score
	int clearFullRows();

	// Get the current score of the player
	int getScore() const;

	// Get the starting X and Y coordinate of the player's gameplay area
	int getStartX() const;
	int getStartY() const;

	int getIsColorActive() const;

	bool getIsCurrentlyFastFalling() const;

	void setIsCurrentlyFastFalling(bool trueORfalse);

	void setScore(int newscore);

	//adds points to curr score
	void addScore(int addscore);

	//adds a temp shape to board, not the curr shape like addshapetoboard
	void addTempShapeToBoard(const shape& s); 

	//removes the shape from the board, used with temp shapes
	void removeShapeFromBoard(); 

	//removes a temp shape to board, not the curr shape like removeshapetoboard does
	void removeTempShapeFromBoard(const shape& s); 

	//used for calculating move for computer player, for human it does nothing
	virtual void bestMove() = 0;

	//check if key pressed is one of the controllers for player
	virtual bool isController(const char ch) = 0;

	//set controllers for human player, for computer does nothing
	virtual void setControllers(const char controllers[]) = 0; 

	//moves according to key pressed
	virtual void move(const char ch) = 0;
};