#include "GameState.h"


GameState::GameState()
{
	initialized = false;
}


// Tyhj� metodi joka voidaan ylikirjoittaa periv�ss�
// statessa, jos staten tarvitsee ladata resursseja.
void GameState::onInitialize()
{

}

void GameState::initialize() 
{
	if (initialized)
	{
		return;
	}

	onInitialize();

	initialized = true;
}

GameState::~GameState()
{
}
