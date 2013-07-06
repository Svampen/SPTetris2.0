#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Game.h"

using namespace sf;

int main()
{
	// Hide console window
	HWND hWnd = GetConsoleWindow(); 
    ShowWindow(hWnd, SW_HIDE );
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1280, 720), "SPTetris 2.0", Style::Close, ContextSettings());
	srand((unsigned int)time(NULL));
	
	Game *g = new Game();

	g->loop(window);

    return 0;
}