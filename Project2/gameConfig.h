#pragma once


class gameConfig
{

public:

	//configs and sets parameters for game, can be updated in this pannel

	enum class eKeys { LEFT, RIGHT, DOWN, ROTATE, ROTATE_COUNTERCLOCKWISE, ESC = 27 };

	enum class shapeType { I, L, J, S, Z, T, O, B };
	static constexpr int defaultPointsNum = 4;

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int STARTING_X_LEFT_Player = 15;
	static constexpr int STARTING_Y_LEFT_Player = 2;


	static constexpr int STARTING_X_RIGHT_Player = 40;
	static constexpr int STARTING_Y_RIGHT_Player = 2;

	static constexpr int NUM_OF_PLAYERS = 2;

	enum class COLORS { BLACK = 0, TURQUOISE = 11, GREY = 7, BLUE = 9, RED = 12, GREEN = 10, PURPLE = 13, YELLOW = 14, WHITE = 15, ORENGE = 6 };
	static const bool COLORS_ACTIVE = true;

	static constexpr char POINT_CHAR = (char)219;

	static constexpr int EMPTY_POINT = ' ';
	static constexpr int BOMB_SYMBOL = 'Q';

	static constexpr int BACK = '9';

	static constexpr int LEFT_PLAYER = 0;
	static constexpr int RIGHT_PLAYER = 1;
	static constexpr int TIE = 3;

	enum class gameMode { humanVShuman = '1', humanVScomputer = '2', computerVScomputer = '3' };

	enum class gameLevel {BEST='1', GOOD='2', NOVICE='3' , STUPID = '4'};



};