#ifndef SINGLEPLAYERSTATE_H
#define SINGLEPLAYERSTATE_H

#include "GameState.h"
#include "Blocks.h"
#include "MainMenu.h"
#include <sstream>

class SingleplayerState : public GameState
{
public:
	SingleplayerState(Game* game);
	~SingleplayerState();

	void draw(const float dt);
	void update(const float dt);
	void handleInput();
	void rowClearing();

protected:
	void onInitialize();

private:
	Blocks* block;
	bool direction = true, newBlock = true, collision = false, clearRow = false, gameOver = false;
	int blockSize = 20, locationNumber = 0, positionCounter = 0, vectorSize = 4, pointsCounter = 0, points = 0, randomBlock = rand() % 7 + 1, currentRandomBlock, pointsMover = 10, rowCounter = 0, rowNumber = 0, rowPoints = 0, level = 0, rowsCleared = 0, red = rand() % 255 + 1, blue = rand() % 255 + 1, green = rand() % 255 + 1;
	sf::Clock clock;
	sf::Font font;
	sf::RectangleShape gameOverRectangle;
	sf::Sprite field, pointsField, bg;
	sf::Text pointsText, levelText, gameOverText, controlsText;
	sf::Texture fieldTexture, pointsFieldTexture, bgTexture;
	std::stringstream ss;
	std::vector<Blocks*>blockVector;
	std::vector<sf::Sprite> spriteVector, allSprites;
};
#endif;
