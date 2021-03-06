#include "MainMenu.h"
#include "SingleplayerState.h"
#include "OptionsState.h"
#include "PlayerState.h"
#include "InverseState.h"

MainMenu::MainMenu(Game* game)
{
	this->game = game;
}

void MainMenu::draw(const float dt)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		game->window.draw(this->menu[i]);
	}
}

void MainMenu::onInitialize()
{
	font = game->setFont(font, "..\\Graphics\\8bitOperatorPlus8-Regular.ttf");

	float width = game->getWindowWidth();
	float height = game->getWindowHeight();

	menu[0].setFont(font);
	menu[1].setFont(font);
	menu[2].setFont(font);
	menu[3].setFont(font);
	menu[4].setFont(font);
	menu[5].setFont(font);

	menu[0].setString("Main Menu");
	menu[0].setColor(sf::Color::Green);
	menu[0].setCharacterSize(50);
	menu[0].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 0.2));

	menu[1].setString("Single Player");
	menu[1].setColor(sf::Color::Red);
	menu[1].setCharacterSize(40);
	menu[1].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 1.7));

	menu[2].setString("Multiplayer");
	menu[2].setColor(sf::Color::White);
	menu[2].setCharacterSize(40);
	menu[2].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 2.7));

	menu[3].setString("Inverse Tetris");
	menu[3].setColor(sf::Color::White);
	menu[3].setCharacterSize(40);
	menu[3].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 3.7));

	menu[4].setString("Options");
	menu[4].setColor(sf::Color::White);
	menu[4].setCharacterSize(40);
	menu[4].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 4.7));

	menu[5].setString("Quit");
	menu[5].setColor(sf::Color::White);
	menu[5].setCharacterSize(40);
	menu[5].setPosition(sf::Vector2f(width / 6, height / (MAX_NUMBER_OF_ITEMS + 1) * 5.7));

}

/*void MainMenu::Main(float width, float height)
{
}*/

void MainMenu::MoveUp()
{
	if (selectedItemIndex > 1)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void MainMenu::MoveDown()
{
	if (selectedItemIndex < MAX_NUMBER_OF_ITEMS - 1)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

int MainMenu::GetPressedItem()
{
	return selectedItemIndex;
}

void MainMenu::update(const float dt)
{

}
void MainMenu::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		MoveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		MoveDown();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		switch (GetPressedItem())
		{
		case 1:
			this->game->pushState(new SingleplayerState(this->game));
			break;
		case 2:
			this->game->pushState(new PlayerState(this->game));
			break;
		case 3:
			this->game->pushState(new InverseState(this->game));
			break;
		case 4:
			this->game->pushState(new OptionsState(this->game));
			break;
		case 5:
			this->game->window.close();
			break;
		default:
			break;
		}
	}
}

MainMenu::~MainMenu()
{
}
