
#include "game.h"
#include "general.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <cctype>


game::~game()
{
	if (players[gameConfig::LEFT_PLAYER] != nullptr && players[gameConfig::RIGHT_PLAYER] != nullptr)
	{
		delete players[gameConfig::LEFT_PLAYER];
		delete players[gameConfig::RIGHT_PLAYER];
	}
}

//initializing all the players:
void game::setPlayers(const int gameMode, const int computerLevel)
{

	switch (gameMode)
	{
	case (int)gameConfig::gameMode::humanVShuman:
		players[gameConfig::LEFT_PLAYER] = new human(); 
		players[gameConfig::RIGHT_PLAYER] = new human();
		break;
	case (int)gameConfig::gameMode::humanVScomputer:
		players[gameConfig::LEFT_PLAYER] = new human();
		players[gameConfig::RIGHT_PLAYER] = new computer(computerLevel);
		break;
	case (int)gameConfig::gameMode::computerVScomputer:
		players[gameConfig::LEFT_PLAYER] = new computer(computerLevel);
		players[gameConfig::RIGHT_PLAYER] = new computer(computerLevel);
		break;
	default:
		break;
	}

	players[gameConfig::LEFT_PLAYER]->setControllers(controllersLeftPlayer);
	players[gameConfig::RIGHT_PLAYER]->setControllers(controllersRightPlayer);
		
	players[gameConfig::LEFT_PLAYER]->initalize(gameConfig::STARTING_X_LEFT_Player, gameConfig::STARTING_Y_LEFT_Player);
	players[gameConfig::RIGHT_PLAYER]->initalize(gameConfig::STARTING_X_RIGHT_Player, gameConfig::STARTING_Y_RIGHT_Player);

	players[gameConfig::LEFT_PLAYER]->setActiveColors(COLOR_ON);
	players[gameConfig::RIGHT_PLAYER]->setActiveColors(COLOR_ON);

	players[gameConfig::LEFT_PLAYER]->PrintClearBoard();
	players[gameConfig::RIGHT_PLAYER]->PrintClearBoard();
}

//prints start screen (used one time only):
void game::startScreen() const
{
	point T[192];
	int counterPlace = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ShowConsoleCursor(false);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			T[counterPlace].set(j, 18 - i);
			counterPlace++;
		}
	}

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			T[counterPlace].set(j + 15, 15 - i);
			counterPlace++;
		}
	}




	point E[80];
	counterPlace = 0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			E[counterPlace].set(j + 23, 14 - i);
			counterPlace++;
			E[counterPlace].set(j + 23, 14 - i - 6);
			counterPlace++;
			E[counterPlace].set(j + 23, 14 - i - 12);
			counterPlace++;
		}
	}


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			E[counterPlace].set(j + 23, 12 - i - 6);
			counterPlace++;
			E[counterPlace].set(j + 23, 12 - i);
			counterPlace++;
		}
	}




	point smallT[36];
	counterPlace = 0;

	for (int j = 0; j < 12; j++)
	{
		smallT[counterPlace].set(j + 29, 5);
		counterPlace++;
		smallT[counterPlace].set(j + 29, 4);
		counterPlace++;
	}

	for (int j = 0; j < 4; j++)
	{
		smallT[counterPlace].set(j + 33, 3);
		counterPlace++;
		smallT[counterPlace].set(j + 33, 2);
		counterPlace++;
		smallT[counterPlace].set(j + 33, 1);
		counterPlace++;

	}





	point R[28];
	counterPlace = 0;

	for (int j = 0; j < 8; j++)
	{
		R[counterPlace].set(j + 43, 5);
		counterPlace++;
		R[counterPlace].set(j + 43, 4);
		counterPlace++;
	}

	for (int j = 0; j < 4; j++)
	{
		R[counterPlace].set(j + 43, 3);
		counterPlace++;
		R[counterPlace].set(j + 43, 2);
		counterPlace++;
		R[counterPlace].set(j + 43, 1);
		counterPlace++;

	}




	point I[20];
	counterPlace = 0;

	for (int j = 0; j < 4; j++)
	{
		I[counterPlace].set(j + 53, 5);
		counterPlace++;
		I[counterPlace].set(j + 53, 4);
		counterPlace++;
		I[counterPlace].set(j + 53, 3);
		counterPlace++;
		I[counterPlace].set(j + 53, 2);
		counterPlace++;
		I[counterPlace].set(j + 53, 1);
		counterPlace++;
	}





	point Dot[8];
	counterPlace = 0;

	for (int j = 0; j < 4; j++)
	{
		Dot[counterPlace].set(j + 53, 7);
		counterPlace++;
		Dot[counterPlace].set(j + 53, 8);
		counterPlace++;

	}




	point S[32];
	counterPlace = 0;

	for (int j = 0; j < 8; j++)
	{
		S[counterPlace].set(j + 63, 4);
		counterPlace++;
		S[counterPlace].set(j + 63, 3);
		counterPlace++;
		S[counterPlace].set(j + 59, 2);
		counterPlace++;
		S[counterPlace].set(j + 59, 1);
		counterPlace++;
	}



	point box[18];
	counterPlace = 0;

	for (int j = 0; j < 18; j++)
	{
		box[counterPlace].set(j + 33, 14);
		counterPlace++;
	}



	DrawLetterForStartScreen(T, 192, (char)219, 0, 0);

	for (int addX = 3; addX >= 0; addX--)
	{
		DrawLetterForStartScreen(E, 80, (char)219, addX * 12, 0);
		Sleep(100);
		if (addX != 0)
		{
			DrawLetterForStartScreen(E, 80, ' ', addX * 12, 0);
		}
	}

	Sleep(25);

	for (int addX = 4; addX >= 0; addX--)
	{
		DrawLetterForStartScreen(smallT, 36, (char)219, addX * 8, 0);
		Sleep(100);
		if (addX != 0)
		{
			DrawLetterForStartScreen(smallT, 36, ' ', addX * 8, 0);
		}
	}


	for (int addX = 3; addX >= 0; addX--)
	{
		DrawLetterForStartScreen(R, 28, (char)219, addX * 8, 0);
		Sleep(100);
		if (addX != 0)
		{
			DrawLetterForStartScreen(R, 28, ' ', addX * 8, 0);
		}
	}


	for (int addXandY = 3; addXandY >= 0; addXandY--)
	{
		DrawLetterForStartScreen(I, 20, (char)219, addXandY * 2, 0);
		DrawLetterForStartScreen(Dot, 8, (char)219, 0, addXandY * 4);
		Sleep(100);
		if (addXandY != 0)
		{
			DrawLetterForStartScreen(I, 20, ' ', addXandY * 2, 0);
			DrawLetterForStartScreen(Dot, 8, ' ', 0, addXandY * 4);
		}
	}

	for (int addX = 2; addX >= 0; addX--)
	{
		DrawLetterForStartScreen(S, 32, (char)219, addX * 2, 0);
		Sleep(100);
		if (addX != 0)
		{
			DrawLetterForStartScreen(S, 32, ' ', addX * 2, 0);
		}
	}



	if (COLOR_ON)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int h = 0; h < 18; h++)
			{
				box[h].draw(4, 4 + i, 15, COLOR_ON, (char)219);

			}
			Sleep(50);
		}

		SetConsoleTextAttribute(hConsole, 248);
		gotoxy(39, 11);
		std::cout << "By Paz & Adam ";
		gotoxy(39, 12);
		std::cout << "who are very nice" << std::endl;



		SetConsoleTextAttribute(hConsole, (int)gameConfig::COLORS::WHITE);
		gotoxy(43, 5);
		std::cout << " /\\_/\\";
		gotoxy(43, 6);
		std::cout << "( o.o )";
		gotoxy(43, 7);
		std::cout << " > ^ <";
	}



	Sleep(500);
}

//draws arr of points specificlly for start screen
void game::DrawLetterForStartScreen(const point* const letterPoints, const int size, const char pointSymbol, const int addX, const int addY) const
{
	for (int h = 0; h < size; h++)
	{
		letterPoints[h].draw(4 + addX, 4 - addY, 3, COLOR_ON, pointSymbol);

	}
}

//runs the whole game (with start screen, menu, the game itself etc)
void game::run()
{
	int userInput;

	bool gameHasNotEnded = true;

	bool run = true;

	int gameModeOption;

	int computeLevel = 0;

	askIfPlayWithColors();


	startScreen(); //start screen

	while (run) //runs the menu until 9 is pressed
	{
		ShowConsoleCursor(false);
		gotoxy(0, 0);
		userInput = manu(); //displayes menu

		switch (userInput) //does the operation the user chosed
		{
		case '1':
			clrscr();
			gameModeOption = gameMode();
			if (gameModeOption == gameConfig::BACK) //goes back if user pressed 9
			{
				break; //goes back to menu, does not start game
			}
			if (gameModeOption != (int)gameConfig::gameMode::humanVShuman) //not both human
			{
				computeLevel = computerLevel();
				if (computeLevel == gameConfig::BACK)
				{
					break; //goes back to menu, does not start game
				}
			}
			setPlayers(gameModeOption, computeLevel);//sets the whole game from start, cleans board curr shape and score
			isGamePausedFlag = 0;
			gameHasNotEnded = Play(); //play new game 
			break;
		case'2':
			clrscr();
			drawPlayersBoard(); //continues game from previous spot
			gameHasNotEnded = Play();
			break;
		case '8':
			printControlersInst(); //instructions
			break;
		case '9':
			clrscr;
			gotoxy(0, 0);
			run = false; //ends game, for getting out of the while loop 
			break;
		default:
			break;
		}
		clrscr();
		setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
		if (gameHasNotEnded == false)
		{
			printWinners();
		}
		clrscr();
	}


	std::cout << "Thank you for playing the most average tetris game in the world";

	gotoxy(0, 15);
}

void game::askIfPlayWithColors()
{
	ShowConsoleCursor(false);
	int input = 0;
	std::cout << "Ahoy, Captain Color or Grayscale Guru? Let us know who you are!\n";
	std::cout << "Ready for an epic journey in the most averege tetris game in the world?\n\n";
	std::cout << "1. Dive into the color extravaganza! Prepare for awesomeness!\n";
	std::cout << "2. Stick to the shades of 'meh.' Black, white, and fifty shades of snooze.\n\n";
	std::cout << "Enter your choice (1 or 2), but remember, colors are waiting for you: \n";
	std::cout << "" << std::endl;
	std::cout << "      /\\_/\\  /\\ " << std::endl;
	std::cout << "     / o o \\ \\ \\" << std::endl;
	std::cout << "    /   Y   \\/ /" << std::endl;
	std::cout << "   /         \\/" << std::endl;
	std::cout << "   \\ | | | | /" << std::endl;
	std::cout << "    `|_|-|_|'" << std::endl;




	while (!_kbhit())
	{
		continue;
	}

	while (input != '1' && input != '2')
	{
		input = _getch();
	}

	if (input == '1')
		COLOR_ON = true;
	else
		COLOR_ON = false;
	clrscr();
}

void game::printWinners() const
{
	switch (winner)
	{
	case 1:
		std::cout << "The winner is: player1" << std::endl;
		break;
	case 2:
		std::cout << "The winner is: player2" << std::endl;
		break;
	case 3:
		std::cout << "It's a tie - you are both losers! :) " << std::endl;
		break;
	default:
		break;
	}

	std::cout << "\nPress any key to continue" << std::endl;

	while (!_kbhit)
	{
		continue;
	}

	_getch();
	clrscr();
}

void game::printControlersInst() const
{
	ShowConsoleCursor(false);
	setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
	clrscr();
	gotoxy(0, 0);
	std::cout << "Left Player keys:                 |   Right Player keys:" << std::endl;
	std::cout << "------------------------------------------------------------------------" << std::endl;
	std::cout << "Move left - a or A                |   Move left - j or J" << std::endl;
	std::cout << "Move right - d or D               |   Move right - l or L" << std::endl;
	std::cout << "Drop - x or X                     |   Drop - m or M" << std::endl;
	std::cout << "ROTATE clockwise - s or S         |   ROTATE clockwise - k or K" << std::endl;
	std::cout << "ROTATE counterclockwise - w or W  |   ROTATE counterclockwise - i or I" << std::endl;
	std::cout << "\nPress any key to return";

	while (!_kbhit)
	{
		continue;
	}

	_getch();
	clrscr();
}

//prints menu and operates used selection:
int game::manu() const
{
	int input;

	ShowConsoleCursor(false);
	setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
	std::cout << "(1) Start a new game" << std::endl;
	if (isGamePausedFlag)
	{
		std::cout << "(2) Continue a paused game" << std::endl;
	}
	std::cout << "(8) Present instructions and keys" << std::endl;
	std::cout << "(9) EXIT" << std::endl;


	while (!_kbhit)
	{
		continue;
	}

	input = _getch();

	if (!isGamePausedFlag && input == '2')
	{
		input = 0;
	}

	return input;
}

//operated the running tettris game itself
bool game::Play()
{
	ShowConsoleCursor(false);
	char keyPressed = 0;
	frameNum = 1;


	printPlayersNameOnTop();
	drawPlayersBorder();
	if (!isGamePausedFlag) //generated new shape only if we started an new game
	{
		generateShapeForPlayers();
		players[gameConfig::LEFT_PLAYER]->bestMove();
		players[gameConfig::RIGHT_PLAYER]->bestMove();
	}
	drawPlayersShape(); //prints shape
	while (thereIsNoLoser())
	{
		ShowConsoleCursor(false);
		BothPlayersNextFallingFrame(); //runs the players positions with every frame
		if (keysOperations()) //if the user pressed esc it will return true and the play function will return true for a paused game
		{
			return true;
		}
		nextFrameCounter(); //changes to next frame of game num (1 to 5)
		Sleep(50);
	}
	drawPlayersBoard();
	winner = checkWhoTheWinnerIs();
	return false; //game ended
}

int game::checkWhoTheWinnerIs() const
{
	//checks if one of them lost by reaching the top, and if not will return winner according to score
	if (players[gameConfig::RIGHT_PLAYER]->not_losing())
		return gameConfig::RIGHT_PLAYER + 1;
	else if (players[gameConfig::LEFT_PLAYER]->not_losing())
		return gameConfig::LEFT_PLAYER + 1;
	else if (players[gameConfig::LEFT_PLAYER]->getScore() == players[gameConfig::RIGHT_PLAYER]->getScore())
		return gameConfig::TIE;
	else
		return players[gameConfig::LEFT_PLAYER]->getScore() > players[gameConfig::RIGHT_PLAYER]->getScore() ? gameConfig::LEFT_PLAYER + 1 : gameConfig::RIGHT_PLAYER + 1;
}

//handels all the keys users can press, moves shaped or bring menu
bool game::keysOperations()
{
	char keyPressed;
	for (int i = 0; i < 100; i++)
	{
		if (_kbhit())
		{
			keyPressed = _getch();

			changeToLower(keyPressed);

			if (keyPressed == (int)gameConfig::eKeys::ESC) //bring pause menu
			{
				isGamePausedFlag = true; //changed
				clrscr(); //changed
				return true; //changed
			}
			else if (keyPressed) //if menu wasnt called
			{
				handlePlayersMovement(keyPressed); //preforms users operations for the game 
			}
		}
	}
	return false;
}

void game::nextFrameCounter()
{
	frameNum = frameNum + 1;
	if (frameNum == 6) //every 5 frames the frame resets
	{
		frameNum = 1;
	}
}

//running next frame for both users
void game::BothPlayersNextFallingFrame()
{
	int prevScoreP1, prevScoreP2;
	prevScoreP1 = players[gameConfig::LEFT_PLAYER]->getScore(); //for checking if score changed after the next frame, to avoid unneccery score printing
	prevScoreP2 = players[gameConfig::RIGHT_PLAYER]->getScore();

	players[gameConfig::RIGHT_PLAYER]->playerNextFallingFrame(frameNum);
	players[gameConfig::LEFT_PLAYER]->playerNextFallingFrame(frameNum);

	if (prevScoreP1 != players[gameConfig::LEFT_PLAYER]->getScore() || prevScoreP2 != players[gameConfig::RIGHT_PLAYER]->getScore()) //for printing only is score changed
	{
		printPlayersNameOnTop();
	}
}

void game::drawPlayersBorder() const
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		players[i]->drawPlayersBorder();
	}
}

void game::generateShapeForPlayers()
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		players[i]->generateShape();
	}
}

//returns true if there is no winner yet, false if someone lost
bool game::thereIsNoLoser() const
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		if (!players[i]->not_losing())
		{
			return false; //if one of them lost, return false because there is a loser
		}
	}
	return true; //if there is no winner yet
}

void game::drawPlayersBoard() const
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		players[i]->drawBoard();
	}
}

void game::drawPlayersShape() const
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		players[i]->drawShape();
	}
}

void game::clearPlayersShape() const
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		players[i]->clearShape();
	}
}

//changes key to lower case if its in caps
void game::changeToLower(char& ch)
{
	if (isalpha(ch))
	{
		ch = tolower(ch);
	}
}

void game::handlePlayersMovement(const char key)
{
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		if (players[i]->isController(key)) //action according to key pressed
		{
			players[i]->move(key);
		}
	}
}

void game::printPlayersNameOnTop() const
{
	setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
	for (int i = 0; i < gameConfig::NUM_OF_PLAYERS; i++)
	{
		gotoxy(players[i]->getStartX(), players[i]->getStartY() - 1);
		std::cout << "player" << i + 1 << ", score:" << players[i]->getScore();
	}
}

int game::gameMode()
{
	int input = 0;

	clrscr();
	ShowConsoleCursor(false);
	setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
	std::cout << "Select a game mode:" << std::endl;
	std::cout << "(1) Human vs Human" << std::endl;
	std::cout << "(2) Human vs Computer" << std::endl;
	std::cout << "(3) Computer vs Computer" << std::endl;
	std::cout << "(9) back" << std::endl;


	while (!(input == '1' || input == '2' || input == '3' || input == '9')) // check if problem with random key!!!!!!!!
	{
		if(_kbhit)
		{
			input = _getch();
		}
		continue;
	}

	clrscr();
	return input;
}

int game::computerLevel()
{
	int input = 0;

	clrscr();
	ShowConsoleCursor(false);
	setColor((int)gameConfig::COLORS::WHITE, COLOR_ON);
	std::cout << "Select a computer level:" << std::endl;
	std::cout << "(1) Best" << std::endl;
	std::cout << "(2) Good" << std::endl;
	std::cout << "(3) Novice" << std::endl;
	std::cout << "(4) stupid" << std::endl;
	std::cout << "(9) back to start screen" << std::endl;


	while (!(input == '1' || input == '2' || input == '3' || input == '4' || input == '9')) // check if problem with random key!!!!!!!!
	{
		if (_kbhit)
		{
			input = _getch();
		}
		continue;
	}

	clrscr();
	return input;
}



