#ifndef TETRIS_H
#define TETRIS_H

#include <iostream>
using namespace std;
using namespace sf;
using namespace sfg;

enum GameState
{
	Paused     = 0,
	Playing    = 1,
	Clearing   = 2,
	Dropping   = 3,
	Meny       = 4,
	New        = 5,
	Quit       = 6,
	GameOver   = 7
};

// Max level
const int maxlevel = 20;
// Start Speed per second
const float startspeed = 1.0f;
// Increment of speed per speed level
const float incspeed = 0.5f;
// Max speed per second
const float maxspeed = 5.0f;

// All the following values are multiplied with current levels before actual calculation is done

// Points per dropped piece
const int dropped = 10;
// Points received per cleared row
const int cleared = 100;
// Slam speed per second when player press down key
const float slamspeed = 10.0f;
// Cleared rows before level increases
const int clearedrowsbeforelevel = 10;
// Drops before speed is increased
const int droppedbeforespeedinc = 10;

#endif