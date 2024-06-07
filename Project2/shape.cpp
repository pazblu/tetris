#pragma once

#include "shape.h"
#include "gameConfig.h"



// Function to set the shape based on its type and position
void shape::set(const int type, const int Xval, const int Yval)
{
	switch (type)
	{
	case (int)gameConfig::shapeType::I:
		pShape[0].set(Xval, Yval);
		pShape[1].set(Xval, Yval + 1);
		pShape[2].set(Xval, Yval + 2);
		pShape[3].set(Xval, Yval + 3);
		this->type = (int)gameConfig::shapeType::I;
		color = (int)gameConfig::COLORS::TURQUOISE;
		break;
	case (int)gameConfig::shapeType::L:
		pShape[0].set(Xval, Yval);
		pShape[1].set(Xval, Yval + 1);
		pShape[2].set(Xval + 1, Yval);
		pShape[3].set(Xval, Yval + 2);
		this->type = (int)gameConfig::shapeType::L;
		color = (int)gameConfig::COLORS::GREY;
		break;
	case (int)gameConfig::shapeType::J:
		pShape[0].set(Xval - 1, Yval);
		pShape[1].set(Xval, Yval + 1);
		pShape[2].set(Xval, Yval);
		pShape[3].set(Xval, Yval + 2);
		this->type = (int)gameConfig::shapeType::J;
		color = (int)gameConfig::COLORS::BLUE;
		break;
	case (int)gameConfig::shapeType::S:
		pShape[0].set(Xval - 1, Yval);
		pShape[1].set(Xval, Yval);
		pShape[2].set(Xval, Yval + 1);
		pShape[3].set(Xval + 1, Yval + 1);
		this->type = (int)gameConfig::shapeType::S;
		color = (int)gameConfig::COLORS::RED;
		break;
	case (int)gameConfig::shapeType::Z:
		pShape[0].set(Xval + 1, Yval);
		pShape[1].set(Xval, Yval);
		pShape[2].set(Xval, Yval + 1);
		pShape[3].set(Xval - 1, Yval + 1);
		this->type = (int)gameConfig::shapeType::Z;
		color = (int)gameConfig::COLORS::GREEN;
		break;
	case (int)gameConfig::shapeType::T:
		pShape[0].set(Xval - 1, Yval + 1);
		pShape[1].set(Xval, Yval + 1);
		pShape[2].set(Xval + 1, Yval + 1);
		pShape[3].set(Xval, Yval);
		this->type = (int)gameConfig::shapeType::T;
		color = (int)gameConfig::COLORS::PURPLE;
		break;
	case (int)gameConfig::shapeType::O:
		pShape[0].set(Xval - 1, Yval);
		pShape[1].set(Xval, Yval);
		pShape[2].set(Xval - 1, Yval + 1);
		pShape[3].set(Xval, Yval + 1);
		this->type = (int)gameConfig::shapeType::O;
		color = (int)gameConfig::COLORS::YELLOW;
		break;
	case (int)gameConfig::shapeType::B: //bomb
		pShape[0].set(Xval, Yval);
		pShape[1].set(Xval, Yval); 
		pShape[2].set(Xval, Yval);
		pShape[3].set(Xval, Yval);
		this->type = (int)gameConfig::shapeType::B;
		color = (int)gameConfig::COLORS::ORENGE;
		break;

	default:
		break;
	}
}


int shape::getType() const
{
	return type;
}


int shape::getColor() const
{
	return color;
}

// Get the array of points representing the shape - gets the arr as pointer to const as we dont want a funtion outside of shape to change the points
const point* const shape::getPointsArr() const
{
	const point* const pshapeArr = pShape;

	return pshapeArr;
}


void shape::draw(const int Xval, const int Yval, const bool activeColors) const
{
	for (int i = 0; i < 4; i++)
	{
		if (type == (int)gameConfig::shapeType::B)
		{
			pShape[i].draw(Xval, Yval, this->color, activeColors, gameConfig::BOMB_SYMBOL);
		}
		else
		{
			pShape[i].draw(Xval, Yval, this->color, activeColors);
		}
	}
}

// Clear the shape from the console at a specified position
void shape::clear(const int Xval, const int Yval, const bool activeColors) const
{
	for (int i = 0; i < 4; i++)
	{
		pShape[i].draw(Xval, Yval, (int)gameConfig::COLORS::BLACK, activeColors, ' ');
	}
}

void shape::move(const gameConfig::eKeys key)
{
	for (int i = 0; i < 4; i++)
	{
		pShape[i].move(key);
	}
}

//Function to rotate the shape around a specified center point
void shape::rotateClockwise()
{
	point p = pShape[1]; // Center of rotation
	for (int i = 0; i < 4; i++)
	{
		int x = pShape[i].getX();
		int y = pShape[i].getY();
		pShape[i].set(p.getX() + (y - p.getY()), p.getY() - (x - p.getX()));
	}
}

void shape::rotateCounterClockwise()
{
	for (int i = 0; i < 3; i++)
	{
		rotateClockwise();
	}
}


int shape::maxHeightOfShape()
{
	int max = 0;

	for (int i = 0; i < 4; i++)
	{
		if (pShape[i].getY() > max)
			max = pShape[i].getY();
	}

	return max;
}