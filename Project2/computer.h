#pragma once
#include "player.h"


class computer: public player
{
private:
	
	
	int colAdjasment;
	int numOfRotations;
	int gameLevel = (int)gameConfig::gameLevel::BEST;

	struct MoveMetrics //keeps data for best move, its position and rotation + properties of achievements 
	{
		bool didNotReachRightBorder = true;
		int bestRotation = 0;
		int bestColAdj = 0; // negative or positive col adjasments
		int currPlaceAdjastments = 0;
		int currNumRowsCleared;
		int currHowTall;
		int currNumOfUnaccesibleBlocks;
		int bestNumRowsCleared = 0;
		int bestHowTall = 18;
		int bestNumOfUnaccesibleBlocks = 216;
		int rotation = 0;
	};

	void moveShapeToLeftmostPosition(shape& temp, MoveMetrics& moveMetrics); //takes the shape to the left of the board
	void dropAndPlaceShapeInBoard(shape& temp, shape& tempDown); ////drops temp shape to see where it lands
	void updateBestMove(MoveMetrics& moveMetrics, shape& tempDown);
	void updateBestMoveBasedOnFewestBlockedSpaces(MoveMetrics& moveMetrics, shape& tempDown); //checks how many blocked spaces after shape lands, checks the min
	void rotateAndMoveDown(MoveMetrics& moveMetrics, shape& temp);
	void updateBestMoveBasedOnLowestPosition(MoveMetrics& moveMetrics, shape& tempDown); //checks the height of shape, the min is best 
	void changeBestMoveBasedOnLevel(MoveMetrics& moveMetrics); //ruins the best move if needed according to level
	void ruinBestMove(MoveMetrics& moveMetrics); //ruins best move by adjusting it one left or one right, "missing" as a human would

public:

	computer(const int level);

	virtual ~computer() {}

	// Handle the falling of the player's shape during each frame
	virtual void playerNextFallingFrame(const int frame) override;

	void bestMove(); //calculates best move for a shape

	void bestMoveForBomb(MoveMetrics& saveBest); //calculates best move for the bomb

	virtual bool isController(const char ch) override { return false; } //for computer always false it does not get keys

	virtual void move(const char ch) override{} //does not move for computer only for human

	virtual void setControllers(const char controllers[]) override {} //does not set controllers for computer only for human

};