#pragma once
#include "computer.h"
#include "human.h"
#include "player.h"
#include "shape.h"



class game
{

private:
	player* players[2] = { nullptr, nullptr };
	const char controllersLeftPlayer[6] = "adxsw";
	const char controllersRightPlayer[6] = "jlmki";
	bool isGamePausedFlag = false;
	int winner = 0; // 0 is no winner, 1 is left 2 is right
	int frameNum; //frame of the game, counts every 5 frames to update falling shapes
	bool COLOR_ON = true;



	//functions for running the game:
	void setPlayers(const int gameMode, const int computerLevel);
	bool Play();
	int manu() const;
	int checkWhoTheWinnerIs() const;
	void generateShapeForPlayers();
	bool thereIsNoLoser() const;
	void changeToLower(char& ch);
	void handlePlayersMovement(const char key);
	bool keysOperations();
	void nextFrameCounter();
	void BothPlayersNextFallingFrame();
	void askIfPlayWithColors();
	int gameMode();
	int computerLevel();


	//functions for displaying the game:
	void drawPlayersBorder() const;
	void drawPlayersBoard() const;
	void drawPlayersShape() const;
	void clearPlayersShape() const;
	void printControlersInst() const;
	void printPlayersNameOnTop() const;
	void printWinners() const;
	void startScreen() const;
	void DrawLetterForStartScreen(const point* const letterPoints, const int size, const char pointSymbol, const int addX, const int addY) const;
	
public:
	//operates the whole game:
	void run();
	~game();
};