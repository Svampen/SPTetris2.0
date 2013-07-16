#include <SFML/Graphics.hpp>
#include "windows.h"
#include "Game.h"

using namespace sf;

int main()
{
	// Hide console window
	HWND hWnd = GetConsoleWindow(); 
    //ShowWindow(hWnd, SW_HIDE );
	VideoMode desktop = VideoMode::getDesktopMode();
	RenderWindow window(VideoMode(1024, 768), "SPTetris 2.0", Style::Close, ContextSettings());
	srand((unsigned int)time(NULL));
	window.setVerticalSyncEnabled(true);
	Game *g = new Game(1024, 768);

	g->loop(window);

	delete g;

    return 0;
}