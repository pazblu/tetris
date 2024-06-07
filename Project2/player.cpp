#include "player.h"
#include <stdlib.h>


void player::initalize(int start_X, int start_y)
{
	_board.setBorderStart(start_X, start_y);
	_board.cleanBoard();
	currentyFastFalling = false;
	score = 0;
}

void player::setActiveColors(const bool activeColors)
{
	isColorActive = activeColors;
	_board.setActiveColor(activeColors);
}

void player::drawPlayersBorder() const
{

	_board.drawBorderSomwhere();

}

void player::generateShape() // 
{
	int type = rand() % 20; //chooses random shape

	if (type == (int)gameConfig::shapeType::B)
	{
		currShape.set(type, gameConfig::GAME_WIDTH / 2, gameConfig::GAME_HEIGHT - 1);
	}
	else
	{
		type = type % 7;

		if (type == (int)gameConfig::shapeType::I) //sets starting position based on type of shape
		{
			currShape.set(type, gameConfig::GAME_WIDTH / 2, gameConfig::GAME_HEIGHT - 4);
		}
		else if (type == (int)gameConfig::shapeType::L || type == (int)gameConfig::shapeType::J)
		{
			currShape.set(type, gameConfig::GAME_WIDTH / 2, gameConfig::GAME_HEIGHT - 3);
		}
		else
		{
			currShape.set(type, gameConfig::GAME_WIDTH / 2, gameConfig::GAME_HEIGHT - 2);
		}
	}

}

// Check if the player is still in the game
bool player::not_losing() const
{
	if (_board.topIsClear())
	{
		return true;
	}
	return false;
}

void player::drawBoard() const
{
	_board.drawPointsSomwhere();
}

void player::drawShape() const
{
	currShape.draw(_board.getStartX(), _board.getStartY(), isColorActive);
}

//clears shape from being printed on screen
void player::clearShape() const
{
	currShape.clear(_board.getStartX(), _board.getStartY(), isColorActive);
}

// Check if the current shape is still falling
bool player::isFalling()
{
	return _board.shapeGoDown(currShape);
}

void player::addShapeToBoard()
{
	_board.addShape(currShape);
}

void player::PrintClearBoard() const
{
	_board.PrintClearBoard();
}

int player::clearFullRows()
{
	return _board.clearFullRows();
}

int player::getStartX() const
{
	return _board.getStartX();
}

int player::getStartY() const
{
	return _board.getStartY();
}

int player::getIsColorActive() const
{
	return isColorActive;
}

bool player::getIsCurrentlyFastFalling() const
{
	return currentyFastFalling;
}

void player::setIsCurrentlyFastFalling(bool trueORfalse)
{
	currentyFastFalling = trueORfalse;
}

int player::getScore() const
{
	return score;
}

void player::setScore(int newscore) 
{
	score = newscore;
}

void player::addScore(int addscore)
{
	score = score + addscore;
}

void player::addTempShapeToBoard(const shape& s)
{
	_board.addShape(s);
}

void player::removeShapeFromBoard()
{
	_board.removeShape(currShape);
}

void player::removeTempShapeFromBoard(const shape& s)
{
	_board.removeShape(s);
}




