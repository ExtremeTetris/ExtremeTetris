#include "InverseState.h"


InverseState::InverseState(Game* game)
{
	this->game = game;

	fieldTexture = game->setTexture(fieldTexture, "..\\Graphics\\Frame.png");
	pointsFieldTexture = game->setTexture(pointsFieldTexture, "..\\Graphics\\Frame2.png");
	bgTexture = game->setTexture(bgTexture, "..\\Graphics\\Background.png");
	font = game->setFont(font, "..\\Graphics\\8bitOperatorPlus8-Regular.ttf");

	// Setting up fields for blocks and other information
	field.setTexture(fieldTexture);
	field.setColor(sf::Color(red, blue, green));
	bg.setTexture(bgTexture);
	bg.setPosition(blockSize, blockSize);
	pointsField.setTexture(pointsFieldTexture);
	pointsField.setColor(sf::Color(red, blue, green));
	pointsField.setPosition(blockSize * 12, 0);

	// Making of the first block and inserting it into a vector
	currentRandomBlock = randomBlock;
	blockVector.push_back(new Blocks(randomBlock));
	randomBlock = rand() % 7 + 1;
	block = new Blocks(randomBlock);
	block->nextBlock(direction);
	direction = false;
	for (int i = 0; i < blockVector.size(); i++)
	{
		spriteVector = blockVector[i]->getVector();
	}

	// Setting up text for points
	pointsText.setFont(font);
	pointsText.setColor(sf::Color::Black);
	pointsText.setCharacterSize(25);
	pointsText.setPosition(sf::Vector2f(blockSize * 18, blockSize * 8.60));
	levelText.setFont(font);
	levelText.setColor(sf::Color::Black);
	levelText.setCharacterSize(25);
	levelText.setPosition(sf::Vector2f(blockSize * 18, blockSize * 11.60));
	ss << points;
	pointsText.setString(ss.str());
	ss.clear();
	ss.str("");
	ss << level;
	levelText.setString(ss.str());
	if (red < 150 && blue < 150 && green < 150)
	{
		pointsText.setColor(sf::Color::White);
		levelText.setColor(sf::Color::White);
	}
	ss.clear();
	ss.str("");

	gameOverRectangle.setPosition(blockSize * 2, blockSize * 5);
	gameOverRectangle.setSize(sf::Vector2f(blockSize * 8, blockSize * 6));
	gameOverRectangle.setOutlineColor(sf::Color::Blue);
	gameOverRectangle.setOutlineThickness(2);
	gameOverText.setFont(font);
	gameOverText.setColor(sf::Color::Black);
	gameOverText.setCharacterSize(20);
	gameOverText.setPosition(blockSize * 3, blockSize * 6);
}

void InverseState::draw(const float dt)
{
	// Clears screen and draws everything
	game->window.draw(bg);
	game->window.draw(pointsField);
	game->window.draw(pointsText);
	game->window.draw(levelText);

	for (int i = 0; i < blockVector.size(); i++)
	{
		spriteVector = block->getVector();
		for (int j = 0; j < 4; j++)
		{
			game->window.draw(spriteVector[j]);
		}
	}

	for (int i = 0; i < blockVector.size(); i++)
	{
		spriteVector = blockVector[i]->getVector();
	}

	for (int i = 0; i < allSprites.size(); i++)
	{
		game->window.draw(allSprites[i]);
	}
	game->window.draw(field);
	if (gameOver == true)
	{
		ss << "Game Over!\nPoints:\n" << points << "\nPress enter.";
		gameOverText.setString(ss.str());
		ss.clear();
		ss.str("");
		game->window.draw(gameOverRectangle);
		game->window.draw(gameOverText);
	}
}

void InverseState::handleInput()
{
	if (gameOver == true)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			if (game->getMultiplayerStart() == true)
			{
				game->setGameOverBool(true);
			}
			else
			{
				game->multiplayerStart(false);
				game->popState();
				std::cout << "Back to main menu\n";
				return;
			}
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			gameOver = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Moves your current block left while checking if it collides to another block or wall
			for (int i = 0; i < vectorSize; i++)
			{
				for (int j = 0; j < allSprites.size() - vectorSize; j++)
				{
					if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x - blockSize && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
					{
						collision = true;
					}
				}
			}
			if (collision == false)
			{
				for (int i = 0; i < blockVector.size() - 1; i++)
				{
					blockVector[i]->moveLeft();
				}
			}
			collision = false;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Moves your current block right while checking if it collides to another block or wall
			for (int i = 0; i < vectorSize; i++)
			{
				for (int j = 0; j < allSprites.size() - vectorSize; j++)
				{
					if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x + blockSize  && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
					{
						collision = true;
					}
				}
			}
			if (collision == false)
			{
				for (int i = 0; i < blockVector.size() - 1; i++)
				{
					blockVector[i]->moveRight();
				}
			}
			collision = false;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && clock.getElapsedTime().asMicroseconds() < 600000 / (level + 1))
		{
			// Moves your current block down while checking if it collides to another block or floor
			// If the block hits floor collision turns to true and another block is made in update section
			// If the block doesn't collide pointsCounter goes up providing you better points if you drop blocks at your own will
			for (int i = 0; i < vectorSize; i++)
			{
				if (spriteVector[i].getPosition().y + blockSize > 18 * blockSize)
				{
					collision = true;
				}
				else
				{
					positionCounter++;
				}
			}
			if (positionCounter == vectorSize)
				for (int i = 0; i < vectorSize; i++)
				{
				for (int j = 0; j < allSprites.size() - vectorSize; j++)
				{
					if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x && spriteVector[i].getPosition().y + blockSize == allSprites[j].getPosition().y)
					{
						collision = true;
					}
					else if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
					{
						gameOver = true;
					}
				}
				}
			if (collision == false)
			{
				blockVector[locationNumber]->moveDown();
				pointsCounter++;
			}
			positionCounter = 0;
		}
	}
}

void InverseState::update(const float dt)
{
	// Inserts the next block in the vector or replaces the old one

	allSprites.erase(allSprites.begin(), allSprites.end());
	for (int i = 0; i < blockVector.size(); i++)
	{
		blockVector[i]->seperateBlocks();
		spriteVector = blockVector[i]->getVector();
		for (int j = 0; j < vectorSize; j++)
		{
			allSprites.push_back(spriteVector[j]);
		}
	}

	// Makes a new block and updates points
	for (int i = 0; i < vectorSize; i++)
	{
		if (collision == true && gameOver == false)
		{
			clock.restart();
			collision = false;
			currentRandomBlock = randomBlock;
			blockVector.push_back(block);
			block->nextBlock(direction);
			direction = true;
			rowClearing();
			randomBlock = rand() % 7 + 1;
			block = new Blocks(randomBlock);
			block->nextBlock(direction);
			direction = false;
			points += pointsCounter + rowPoints;
			rowPoints = 0;
			pointsCounter = 0;
			locationNumber++;
			ss.clear();
			ss.str("");
			if (points >= pointsMover)
			{
				pointsText.move(-10, 0);
				pointsMover = pointsMover * 10;
			}
			ss << points;
			pointsText.setString(ss.str());

			if (randomBlock == 2 || randomBlock == 3 || randomBlock == 4)
			{
				randomRotation = rand() % 2 + 1;
				for (int j = 0; j < randomRotation; j++)
				{
					block->rotateClockwise(randomBlock, allSprites);
				}
			}
			else if (randomBlock == 5 || randomBlock == 6 || randomBlock == 7)
			{
				randomRotation = rand() % 4 + 1;
				for (int j = 0; j < randomRotation; j++)
				{
					block->rotateClockwise(randomBlock, allSprites);
				}
			}
			break;
		}
	}

	// Drops your current block according to your current level and quits the game if you reach the top or you somehow end up dropping a block on top of another block
	if (clock.getElapsedTime().asMicroseconds() >= 600000 / (level + 1) && gameOver == false)
	{
		for (int i = 0; i < vectorSize; i++)
		{
			if (spriteVector[i].getPosition().y + blockSize > 18 * blockSize)
			{
				collision = true;
			}
			for (int j = 0; j < allSprites.size() - vectorSize; j++)
			{
				if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x && spriteVector[i].getPosition().y + blockSize == allSprites[j].getPosition().y)
				{
					collision = true;
				}
				else if (spriteVector[i].getPosition().x == allSprites[j].getPosition().x && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
				{
					gameOver = true;
				}
			}
		}
		if (collision == false)
		{
			blockVector[locationNumber]->moveDown();
			clock.restart();
		}
	}
}

void InverseState::rowClearing()
{
	// Goes through allSprites vector finding blocks that should be removed or dropped down and gives you points according to how many rows you cleared at the same time
	for (int i = 0; i < blockSize * blockSize; i += blockSize)
	{
		for (int j = 0; j < blockVector.size(); j++)
		{
			rowCounter = blockVector[j]->clearBlocks(clearRow, rowNumber, rowCounter, i);
			if (clearRow == false && rowCounter == 10)
			{
				rowNumber = i;
				clearRow = true;
				rowCounter = 0;
			}
			else if (clearRow == true && rowCounter == 10)
			{
				rowsCleared++;
				if (rowsCleared % 10 == true && rowsCleared != 1 && level < 9)
				{
					level++;
					ss.clear();
					ss.str("");
					ss << level;
					levelText.setString(ss.str());
				}
				rowNumber = 0;
				rowCounter = 0;
				clearRow = false;
				j = -1;
				if (rowPoints == 0)
				{
					rowPoints = 40 * (level + 1);
				}
				else if (rowPoints == 40)
				{
					rowPoints = 100 * (level + 1);
				}
				else if (rowPoints == 100)
				{
					rowPoints = 300 * (level + 1);
				}
				else if (rowPoints == 300)
				{
					rowPoints = 1200 * (level + 1);
				}
			}
		}
		rowCounter = 0;
	}
	clearRow = false;

	for (int i = 0; i < blockVector.size(); i++)
	{
		spriteVector = blockVector[i]->getVector();
		if (spriteVector[0].getPosition().y > blockSize * 30 && spriteVector[1].getPosition().y > blockSize * 30 && spriteVector[2].getPosition().y > blockSize * 30 && spriteVector[3].getPosition().y > blockSize * 30)
		{
			delete blockVector[i];
			blockVector.erase(blockVector.begin() + i);
			locationNumber--;
			i = -vectorSize;
		}
	}
}


InverseState::~InverseState()
{
}
