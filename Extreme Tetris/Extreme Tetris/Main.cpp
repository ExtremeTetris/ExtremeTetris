#include "Game.h"
#include "MainMenu.h"

int main()
{
	Game game;
	game.pushState(new MainMenu(&game));
	game.gameLoop();							//gameLoop() metodissa py�rii itse peli
												//ja toimii ns. main.cpp:n�

	return 0;
}