#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "IPiece.h"
#include "PieceBuilder.h"
#include "Map.h"
#include "Menu.h"
#include <SFML/Audio/Music.hpp>

class Game
{
public:
	Game(int width, int height);
	~Game();

	void loop(RenderWindow &window);

private:

	void handleinput(RenderWindow &window);
	void update();
	void draw(RenderWindow &window);
	void checkRows();
	void clearing();
	void dropping();
	void reset();
	void createPiece();
	void createInfoLabels();

	TetrisPiece *mCurrentPiece;
	PieceBuilder *mPieceBuilder;
	Map *mMap;
	Menu *mMenu;
	
	float mSpeed;
	int mLevel;
	int mDrops;
	int mCleared; 
	int mSpeedLevel;

	sf::Clock mSlidingTime;

	sf::Clock mClock;
	Event mEvent;
	float dt;
	float maxFps;
	PieceBuilder::Piece mPiece;
	GameState mGameState;
	Vector2f mStart;
	struct Rows
	{
		int *rows;
		bool *cleared;
		int nrOfRows;
		int deepest;
	};
	Rows *mRows;
	sf::Clock droppingClock;
	int mScore;

	// Level/Score board
	SFGUI mSfgui;

	Label::Ptr mInfoHeadline;
	Label::Ptr mScoreLabel;
	Label::Ptr mLevelLabel;
	Label::Ptr mSpeedLabel;
	sfg::Window::Ptr mWindow;
	sfg::Box::Ptr mBox;
	sfg::Desktop mDesktop;

	sf::Music mMusic;
};

#endif