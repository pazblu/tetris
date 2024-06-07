#include "player.h"
#pragma once

class human: public player
{
	char _controllers[5];


public:

	virtual ~human() {}

	//Helper function
	void doTheMove(const int key);

	bool isController(const char ch);

	void move(const char ch);

	// Set the controller configuration for the player
	virtual void setControllers(const char controllers[]);

	// Handle the next falling frame of the player's shape, gets the num frame of the game (1-5, at fifth frame shapes go down)
	virtual void playerNextFallingFrame(const int frame) override;

	virtual void bestMove() override {} //no best move for human

};

