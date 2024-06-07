#include "human.h"



// Set the controller keys for the player
void human::setControllers(const char controllers[])
{
	for (int i = 0; i < 5; i++)
	{
		_controllers[i] = controllers[i];
	}
}


// Perform the specified move and update the player's shape on the board
void human::doTheMove(const int key)
{
	currShape.clear(_board.getStartX(), _board.getStartY(), getIsColorActive());
	_board.move(key, currShape);
	currShape.draw(_board.getStartX(), _board.getStartY(), getIsColorActive());

}

// Check if the provided character is a valid controller key for the player
bool human::isController(const char ch)
{
	for (int i = 0; i < 5; i++)
	{
		if (ch == _controllers[i])
			return true;
	}

	return false;
}


// Move the player based on the pressed key
void human::move(const char ch)
{
	if (_controllers[(int)gameConfig::eKeys::LEFT] == ch)
	{
		doTheMove((int)gameConfig::eKeys::LEFT);
	}
	else if (_controllers[(int)gameConfig::eKeys::RIGHT] == ch)
	{
		doTheMove((int)gameConfig::eKeys::RIGHT);
	}
	else if (_controllers[(int)gameConfig::eKeys::DOWN] == ch)
	{
		setIsCurrentlyFastFalling(true);
	}
	else if (_controllers[(int)gameConfig::eKeys::ROTATE] == ch)
	{
		doTheMove((int)gameConfig::eKeys::ROTATE);
	}
	else if (_controllers[(int)gameConfig::eKeys::ROTATE_COUNTERCLOCKWISE] == ch)
	{
		doTheMove((int)gameConfig::eKeys::ROTATE_COUNTERCLOCKWISE);
	}

}


// Handle the next falling frame of the player's shape, gets the num frame of the game (1-5, at fifth frame shapes go down)
void human::playerNextFallingFrame(const int frame)
{
	bool canContinue;
	if (getIsCurrentlyFastFalling() == false) //if its not fast falling it goes down in normal speed
	{
		if (frame == 5) //every fifth frame it goes down
		{
			clearShape();
			canContinue = isFalling();
			drawShape();

			//if it reached the bottom and cant go down anymore, clears full rows if there are any, updetes score, generates new shape and prints it:
			if (!canContinue)
			{
				if (currShape.getType() == (int)gameConfig::shapeType::B)
				{
					_board.activateBomb(currShape.getPointsArr()[0]);
				}
				else
				{
					addShapeToBoard();
					addScore(clearFullRows());
				}
				generateShape();
				drawShape();
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
			setIsCurrentlyFastFalling(false); //ends fast falling
		}
	}
}







