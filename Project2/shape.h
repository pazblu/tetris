#pragma once
#include "point.h"

class shape
{
    point pShape[4];
    int type;
    int color;

public:
    // Function to set the shape based on its type and position
    void set(const int type, const int Xval = 0, const int Yval = 0);

    // Get the type of the shape
    int getType() const;

    // Get the color of the shape
    int getColor() const;

    // Get the array of points representing the shape
    const point* const getPointsArr() const;

    // Draw the shape on the console at a specified position
    void draw(const int Xval = 0, const int Yval = 0, const bool activeColors = true) const;

    // Clear the shape from the console at a specified position
    void clear(const int Xval = 0, const int Yval = 0, const bool activeColors = true) const;

    // Move the shape based on a specified key
    void move(const gameConfig::eKeys key);

    // Rotate the shape clockwise
    void rotateClockwise();

    // Rotate the shape counterclockwise
    void rotateCounterClockwise();

    //return max point of shape
    int maxHeightOfShape();

};