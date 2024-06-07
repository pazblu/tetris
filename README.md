
# Project Name

Advanced TETRIS Game

![Example Image](https://github.com/pazblu/tetris/blob/main/tetris.png)

## Description

This project is an advanced version of the classic TETRIS game implemented as a console application in C++.
 It includes features like different shapes, colors, and a point system for players. The game supports both 
 human and computer players with multiple difficulty levels.

## Features

- Configurable game board size.
- Human vs. Human, Human vs. Computer, and Computer vs. Computer game modes.
- Adjustable game difficulty levels (Best, Good, Novice, Stupid).
- Console-based graphical interface with color setting.
- Scoring system with row clearing and bomb activation.

## Files

- `gameConfig`: Implementation of game configuration settings.
- `gameConfig`: for game configuration settings.
- `general`: General utility functions for the console interface.
- `human`: Implementation of human player-specific functions.
- `main`: Main file to run the game.
- `player`: Implementation of common player functions.
- `point`: Implementation of point-related functions.
- `shape`: Implementation of shape-related functions.
- `board`: Implementation of board-related functions.



## Configuration

Game configuration settings can be adjusted in the `gameConfig.h` file. Key parameters include:

- Game board dimensions (`GAME_WIDTH`, `GAME_HEIGHT`)
- Starting positions for players (`STARTING_X_LEFT_Player`, `STARTING_Y_LEFT_Player`, `STARTING_X_RIGHT_Player`, `STARTING_Y_RIGHT_Player`)
- Number of players (`NUM_OF_PLAYERS`)
- Active colors (`COLORS_ACTIVE`)
- colors for points, bombs, and empty spaces.

## Game Controls

Controls can be set and adjusted within the game configuration:

- `LEFT`, `RIGHT`, `DOWN`: Move the shape left, right, or down.
- `ROTATE`, `ROTATE_COUNTERCLOCKWISE`: Rotate the shape clockwise or counterclockwise.
- `ESC`: Exit the game.
