/*
** Menu class
**
** Created by Stefan Hagdahl
**
*/

#include "Menu.h"

Menu::Menu()
{
	// Create the label.
    mLabel = sfg::Label::Create("Hello world!");
	// Create a window and add the label to it. Also set the window's title.
	mWindow = sfg::Window::Create();
    mWindow->SetTitle("Hello world!");
    mWindow->Add(mLabel);

	mDesktop.Add(mWindow);
}

Menu::~Menu()
{

}

void Menu::update(float dt)
{
	mDesktop.Update(dt);
}

void Menu::draw(RenderWindow &window)
{
	mSfgui.Display(window);
}