/*
** Menu class
**
** Created by Stefan Hagdahl
**
*/

#include "Menu.h"

Menu::Menu(int Width, int Height)
{
	// Create the label.
	mMenuHeadline = sfg::Label::Create("Menu");
	mMenuHeadline->SetId("menu");
	mNewGameButton = sfg::Button::Create("New Game");
	mNewGameButton->SetId("new");
	mNewGameButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&Menu::OnNewGameClick, this);
	mContinueButton = sfg::Button::Create("Continue");
	mContinueButton->SetId("continue");
	
	mQuitGameButton = sfg::Button::Create("Quit");
	mQuitGameButton->SetId("quit");
	mQuitGameButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&Menu::OnQuitClick, this);
	// Create a window and add the label to it. Also set the window's title.
	mWindow = sfg::Window::Create(0);
	mBox = sfg::Box::Create(sfg::Box::VERTICAL);
	mBox->SetSpacing(1.0f);
	mBox->Pack(mMenuHeadline);
	mBox->Pack(mNewGameButton);
	mBox->Pack(mContinueButton);
	mBox->Pack(mQuitGameButton);

	mWindow->Add(mBox);
	Vector2f size = Vector2f(300.0f, 300.0f);
	float posX = Width / 2 - size.x / 2;
	float posY = Height / 2 - size.y / 2;
	mWindow->SetAllocation(FloatRect(Vector2f(posX, posY), size));
	
	mDesktop.Add(mWindow);
	mDesktop.SetProperty("Label#menu", "FontSize", 20);
	mDesktop.SetProperty("Label#menu", "Color", sf::Color(0, 255, 0));
	mDesktop.SetProperty("Button#continue", "Color", sf::Color(0, 0, 0));
	mDesktop.SetProperty("Button#continue", "FontSize", 20);
	mDesktop.SetProperty("Button#new", "FontSize", 20);
	mDesktop.SetProperty("Button#quit", "FontSize", 20);
	mGameState = Meny;
}

Menu::~Menu()
{

}

void Menu::OnNewGameClick()
{
	mGameState = New;
	mContinueButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&Menu::OnContinueClick, this);
	mDesktop.SetProperty("Button#continue", "Color", sf::Color(255, 255, 255));
}

void Menu::OnContinueClick()
{
	mGameState = Playing;
}

void Menu::OnQuitClick()
{
	mGameState = Quit;
}

GameState Menu::handleInput(Event e, RenderWindow &window)
{
	mGameState = Meny;
	while (window.pollEvent(e))
	{
		mDesktop.HandleEvent(e);
		switch(e.type)
		{
		case Event::Closed:
			// Delete all resources
			window.close();
			break;
		default:
			break;
		}
	}
	return mGameState;
}

void Menu::update(float dt)
{
	mDesktop.Update(dt);
}

void Menu::draw(RenderWindow &window)
{
	window.resetGLStates();
	mSfgui.Display(window);
}

void Menu::setLabel(const sf::String label)
{
	mMenuHeadline->SetText(label);
}