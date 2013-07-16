#ifndef MENU_H
#define MENU_H

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>
#include "Tetris.h"


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
	void setLabel(const sf::String label);
	void showWindow();
	void disableContinueButton();

private:
	SFGUI mSfgui;

	Label::Ptr mMenuHeadline;
	Button::Ptr mNewGameButton;
	Button::Ptr mContinueButton;
	Button::Ptr mQuitGameButton;
	sfg::Window::Ptr mWindow;
	sfg::Box::Ptr mBox;
	sfg::Desktop mDesktop;
	GameState mGameState;

	unsigned int mContButtonId;
};
#endif
