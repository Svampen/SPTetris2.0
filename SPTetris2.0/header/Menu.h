#ifndef MENU_H
#define MENU_H

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Tetris.h"
#include <iostream>
using namespace std;

using namespace sf;
using namespace sfg;

class Menu
{
public:
	Menu(int Width, int Height);
	~Menu();

	void OnNewGameClick();
	void OnContinueClick();
	void OnQuitClick();

	GameState handleInput(Event e, RenderWindow &window);
	void update(float dt);
	void draw(RenderWindow &window);

private:
	SFGUI mSfgui;

	Button::Ptr mNewGameButton;
	Button::Ptr mContinueButton;
	Button::Ptr mQuitGameButton;
	sfg::Window::Ptr mWindow;
	sfg::Box::Ptr mBox;
	sfg::Desktop mDesktop;
	GameState mGameState;
};
#endif
