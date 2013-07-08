#ifndef MENU_H
#define MENU_H

#include <SFGUI/SFGUI.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace sfg;

class Menu
{
public:
	Menu();
	~Menu();

	void handleInput(Event e);
	void update(float dt);
	void draw(RenderWindow &window);

private:
	SFGUI mSfgui;

	Label::Ptr mLabel;
	sfg::Window::Ptr mWindow;
	sfg::Desktop mDesktop;
};
#endif
