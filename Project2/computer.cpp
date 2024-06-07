#include "computer.h"
#include <stdlib.h>


computer::computer(const int level) : gameLevel(level) {}

// Handle the next falling frame of the player's shape, gets the num frame of the game (1-5, at fifth frame shapes go down)
void computer::playerNextFallingFrame(const int frame)
{
	bool canContinue;
	if (getIsCurrentlyFastFalling() == false) //if its not fast falling it goes down in normal speed
	{
		if (frame == 5) //every fifth frame it goes down
		{
			clearShape();
			canContinue = isFalling();

			if (canContinue == true) //activates move for computer only if it didn't reach bottom
			{
				if (numOfRotations != 0) //rotates
				{
					while (numOfRotations > 0)
					{
						currShape.rotateClockwise();
						numOfRotations--;
					}
				}
				else //moving to the right col one move at a frame
				{

					if (colAdjasment > 0)
					{
						_board.shapeGoRight(currShape);
						colAdjasment--;
					}
					if (colAdjasment < 0)
					{
						_board.shapeGoLeft(currShape);
						colAdjasment++;
					}
					if (colAdjasment == 0)
					{
						setIsCurrentlyFastFalling(true);
					}
				}
				drawShape();
			}
			else //reched bottom, adds shape and created new shape
			{
				drawShape();
				addShapeToBoard();
				generateShape();
				if (_board.CheckifShapeFitOnBoard(currShape) == true) 
				{
					bestMove();
				}
				else
				{
					addShapeToBoard();
				}
				
			}

		}

	}
	else //fast speed, goes down with every frame
	{
		clearShape();
		canContinue = isFalling();
		drawShape();

		if (!canContinue) 
		{
			if (currShape.getType() != (int)gameConfig::shapeType::B)
			{
				addShapeToBoard();
				addScore(clearFullRows());
			}
			else
			{
				_board.activateBomb(currShape.getPointsArr()[0]);
			}
			generateShape();
			bestMove();


			setIsCurrentlyFastFalling(false); //ends fast falling
		}
	}
}

void computer::bestMove()
{


	shape temp = this->currShape;
	shape tempDown;

	MoveMetrics moveMetrics;

	if (currShape.getType() == (int)gameConfig::shapeType::B) //if bomb so calculated differently according to height
	{

		bestMoveForBomb(moveMetrics);

	}
	else
	{
		for (moveMetrics.rotation = 0; moveMetrics.rotation < 4; moveMetrics.rotation++) //checks for every rotation every possible move for every col it can reach
		{
			moveShapeToLeftmostPosition(temp, moveMetrics); //goes as left it can

			moveMetrics.didNotReachRightBorder = true;

			while (moveMetrics.didNotReachRightBorder) //moves right as he doesnt rech border or blocks
			{
				dropAndPlaceShapeInBoard(temp, tempDown); //goes down

				moveMetrics.currNumRowsCleared = _board.numOfRowsDeleted(); //check how many rows were deleted

				if (moveMetrics.currNumRowsCleared >= moveMetrics.bestNumRowsCleared) 
				{
					if (moveMetrics.currNumRowsCleared > moveMetrics.bestNumRowsCleared) //updets if it cleared the most
					{
						updateBestMove(moveMetrics, tempDown);
					}
					else //if it is even
					{

						updateBestMoveBasedOnFewestBlockedSpaces(moveMetrics, tempDown); //updates best on fewer blocks blocked, and lastly according to height

					}
				}
				removeTempShapeFromBoard(tempDown);

				moveMetrics.currPlaceAdjastments++;
				moveMetrics.didNotReachRightBorder = _board.shapeGoRight(temp);

			}
			temp = this->currShape;

			rotateAndMoveDown(moveMetrics, temp);
		}
	}

	changeBestMoveBasedOnLevel(moveMetrics); //ruins best move if needed

	numOfRotations = moveMetrics.bestRotation; //updetes best move
	colAdjasment = moveMetrics.bestColAdj;
}

void computer::bestMoveForBomb(MoveMetrics& saveBest)
{

	int colToGo = _board.maxHeightCol();
	saveBest.bestColAdj = colToGo - currShape.getPointsArr()[0].getX();
	saveBest.rotation = 0;

}

void computer::moveShapeToLeftmostPosition(shape& temp, MoveMetrics& moveMetrics)
{
	moveMetrics.currPlaceAdjastments = 0;

	while (_board.shapeGoLeft(temp))
	{
		moveMetrics.currPlaceAdjastments--;
	}
}

void computer::dropAndPlaceShapeInBoard(shape& temp, shape& tempDown) {

	// Copy the current shape for manipulation
	tempDown = temp;

	// Continuously move the shape downwards until it can't go down any further
	while (_board.shapeGoDown(tempDown)) {}

	// Add the shape to the board at its current position
	addTempShapeToBoard(tempDown);
}

void computer::updateBestMove(MoveMetrics& moveMetrics, shape& tempDown) {
	// Update best move if current position is better
	moveMetrics.bestNumRowsCleared = moveMetrics.currNumRowsCleared;
	moveMetrics.bestHowTall = tempDown.maxHeightOfShape();
	moveMetrics.bestNumOfUnaccesibleBlocks = _board.unaccesibleBlocks();

	moveMetrics.bestRotation = moveMetrics.rotation;
	moveMetrics.bestColAdj = moveMetrics.currPlaceAdjastments;
}

void computer::updateBestMoveBasedOnFewestBlockedSpaces(MoveMetrics& moveMetrics, shape& tempDown)
{
	moveMetrics.currNumOfUnaccesibleBlocks = _board.unaccesibleBlocks();
	if (moveMetrics.bestNumOfUnaccesibleBlocks >= moveMetrics.currNumOfUnaccesibleBlocks)
	{
		if (moveMetrics.bestNumOfUnaccesibleBlocks > moveMetrics.currNumOfUnaccesibleBlocks)
		{
			moveMetrics.bestNumRowsCleared = moveMetrics.currNumRowsCleared;
			moveMetrics.bestNumOfUnaccesibleBlocks = moveMetrics.currNumOfUnaccesibleBlocks;
			moveMetrics.bestHowTall = tempDown.maxHeightOfShape();

			moveMetrics.bestRotation = moveMetrics.rotation;
			moveMetrics.bestColAdj = moveMetrics.currPlaceAdjastments;


		}
		else
		{
			moveMetrics.currHowTall = tempDown.maxHeightOfShape();
			if (moveMetrics.currHowTall < moveMetrics.bestHowTall)
			{
				moveMetrics.bestNumRowsCleared = moveMetrics.currNumRowsCleared;
				moveMetrics.bestHowTall = moveMetrics.currHowTall;
				moveMetrics.bestNumOfUnaccesibleBlocks = moveMetrics.currNumOfUnaccesibleBlocks;

				moveMetrics.bestRotation = moveMetrics.rotation;
				moveMetrics.bestColAdj = moveMetrics.currPlaceAdjastments;

			}

		}
	}

}

void computer::updateBestMoveBasedOnLowestPosition(MoveMetrics& moveMetrics, shape& tempDown)
{
	moveMetrics.currHowTall = tempDown.maxHeightOfShape();
	if (moveMetrics.currHowTall <= moveMetrics.bestHowTall)
	{
		if (moveMetrics.currHowTall < moveMetrics.bestHowTall)
		{
			moveMetrics.bestNumRowsCleared = moveMetrics.currNumRowsCleared;
			moveMetrics.bestHowTall = moveMetrics.currHowTall;
			moveMetrics.bestNumOfUnaccesibleBlocks = _board.unaccesibleBlocks();

			moveMetrics.bestRotation = moveMetrics.rotation;
			moveMetrics.bestColAdj = moveMetrics.currPlaceAdjastments;

		}
		else
		{
			moveMetrics.currNumOfUnaccesibleBlocks = _board.unaccesibleBlocks();
			if (moveMetrics.bestNumOfUnaccesibleBlocks > moveMetrics.currNumOfUnaccesibleBlocks)
			{
				moveMetrics.bestNumRowsCleared = moveMetrics.currNumRowsCleared;
				moveMetrics.bestHowTall = moveMetrics.currHowTall;
				moveMetrics.bestNumOfUnaccesibleBlocks = moveMetrics.currNumOfUnaccesibleBlocks;

				moveMetrics.bestRotation = moveMetrics.rotation;
				moveMetrics.bestColAdj = moveMetrics.currPlaceAdjastments;

			}
		}
	}
}

void computer::rotateAndMoveDown(MoveMetrics& moveMetrics, shape& temp)
{
	for (int j = 0; j < moveMetrics.rotation + 1; j++)
	{
		_board.shapeGoDown(temp); //    works only when board isnt full!!!! else a problem!!!!!!
		temp.rotateClockwise();
	}
}

void computer::changeBestMoveBasedOnLevel(MoveMetrics& moveMetrics)
{
	int num = rand();
	switch (gameLevel)
	{
	case '1':
		break;
	case '2':
		if (num % 40 == 1)
		{
			ruinBestMove(moveMetrics);
		}
		break;
	case '3':
		if (num % 10 == 1)
		{
			ruinBestMove(moveMetrics);
		}
		break;
	case '4':
		ruinBestMove(moveMetrics);
		break;
	default:
		break;
	}
}

void computer::ruinBestMove(MoveMetrics& moveMetrics)
{

	shape temp = this->currShape;
	shape checkCanMove;
	int colAdj = moveMetrics.bestColAdj;
	int rotate = moveMetrics.bestRotation;


	while (numOfRotations > 0)
	{
		temp.rotateClockwise();
		numOfRotations--;
	}

	if (colAdjasment > 0)
	{
		_board.shapeGoRight(temp);
		colAdjasment--;
	}
	if (colAdjasment < 0)
	{
		_board.shapeGoLeft(temp);
		colAdjasment++;
	}


	checkCanMove = temp;

	if (_board.shapeGoRight(checkCanMove) == true)
	{
		moveMetrics.bestColAdj++;
	}
	else
	{
		checkCanMove = temp;
		if (_board.shapeGoLeft(checkCanMove) == true)
		{
			moveMetrics.bestColAdj--;
		}
	}
	

}








