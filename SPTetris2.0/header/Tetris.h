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

// 10 points per dropped piece times level
const int dropped = 10;
// 100 points per cleared row times level
const int cleared = 100;
// Speed per second
const float speed = 1.0f;
// Max speed
const float maxspeed = 10.0f;
// Max level
const int maxlevel = 10;
// Dropps per level times level
const int dropsPerLevel = 5;


#endif