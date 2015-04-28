#include "StateStart.h"

StateStart::StateStart(Game* game)
{
	this->game = game;

	if (!fieldTexture.loadFromFile("..\\Graphics\\Frame.png"))
	{
		std::cout << "Can't load texture!";
	}
	if (!pointsFieldTexture.loadFromFile("..\\Graphics\\Frame2.png"))
	{
		std::cout << "Can't load texture!";
	}
	if (!bgTexture.loadFromFile("..\\Graphics\\Background.png"))
	{
		std::cout << "Can't load texture!" << std::endl;
	}
	if (!font.loadFromFile("..\\Graphics\\8bitOperatorPlus8-Regular.ttf"))
	{
		std::cout << "Can't load textfile!" << std::endl;
	}

	// Setting up frames for blocks and other information
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
}

void StateStart::draw(const float dt)
{
	// Clears screen and draws everything in order: background, frames, text, next block, all the other blocks

	this->game->window.clear(sf::Color::Black);

	game->window.draw(bg);
	game->window.draw(field);
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
}

void StateStart::handleInput()
{
	sf::Event event;
	while (this->game->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				game->window.close();
				break;
			}
			// Checks if escape, an arrow key or rotate button is pressed
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					this->game->pushState(new MainMenu(this->game));
					std::cout << "Back to main menu\n";
					return;
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					// Moves your current block left while checking if it collides to another block or wall
					for (int i = 0; i < vectorSize; i++)
					{
						if (spriteVector[i].getPosition().x - blockSize > 0)
						{
							positionCounter++;
						}
					}
					if (positionCounter == vectorSize)
					{
						for (int i = 0; i < vectorSize; i++)
						{
							for (int j = 0; j < allSprites.size() - vectorSize; j++)
							{
								if (spriteVector[i].getPosition().x - blockSize == allSprites[j].getPosition().x && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
								{
									collision = true;
								}
							}
						}
						if (collision == false)
						{
							blockVector[locationNumber]->moveLeft();
						}
						collision = false;
					}
					positionCounter = 0;
				}

				else if (event.key.code == sf::Keyboard::Right)
				{
					// Moves your current block right while checking if it collides to another block or wall
					for (int i = 0; i < vectorSize; i++)
					{
						if (spriteVector[i].getPosition().x + blockSize < 11 * blockSize)
						{
							positionCounter++;
						}
					}
					if (positionCounter == vectorSize)
					{
						for (int i = 0; i < vectorSize; i++)
						{
							for (int j = 0; j < allSprites.size() - vectorSize; j++)
							{
								if (spriteVector[i].getPosition().x + blockSize == allSprites[j].getPosition().x && spriteVector[i].getPosition().y == allSprites[j].getPosition().y)
								{
									collision = true;
								}
							}
						}
						if (collision == false)
						{
							blockVector[locationNumber]->moveRight();
						}
						collision = false;
					}
					positionCounter = 0;
				}

				else if (event.key.code == sf::Keyboard::Down && clock.getElapsedTime().asMicroseconds() < 600000 / (level + 1))
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
									this->game->pushState(new MainMenu(this->game));
									std::cout << "Back to main menu\n";
									return;
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

				else if (event.key.code == sf::Keyboard::M)
				{
					blockVector[locationNumber]->rotateClockwise(currentRandomBlock, allSprites);
				}

				else if (event.key.code == sf::Keyboard::N)
				{
					blockVector[locationNumber]->rotateCounterClockwise(currentRandomBlock, allSprites);
				}

			default:
				break;
			}
			case sf::Event::KeyReleased:
			{
				if (event.key.code == sf::Keyboard::Down)
				{
					pointsCounter = 0;
				}
			}
		}
	}
}

void StateStart::update(const float dt)
{
	// Inserts the next block in the vector or replaces the old one
	if (newBlock == true)
	{
		for (int i = 0; i < vectorSize; i++)
		{
			allSprites.push_back(spriteVector[i]);
			newBlock = false;
		}
	}
	else if (newBlock == false)
	{
		for (int i = 0; i < vectorSize; i++)
		{
			allSprites.erase(allSprites.end() - 1 - i);
			allSprites.push_back(spriteVector[i]);
		}
	}

	// Makes a new block and updates points
	for (int i = 0; i < vectorSize; i++)
	{
		if (collision == true)
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
			newBlock = true;
			break;
		}
	}

	// Drops your current block according to your current level and quits the game if you reach the top or you somehow end up dropping a block on top of another block
	if (clock.getElapsedTime().asMicroseconds() >= 600000 / (level + 1))
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
					this->game->pushState(new MainMenu(this->game));
					std::cout << "Back to main menu\n";
					return;
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

void StateStart::rowClearing()
{
	// Goes through allSprites vector finding blocks that should be removed or dropped down and gives you points according to how many rows you cleared at the same time
	for (int i = 0; i < blockSize * blockSize; i += blockSize)
	{
		for (int j = 0; j < allSprites.size(); j++)
		{
			if (clearRow == true && allSprites[j].getPosition().y == rowNumber)
			{			
				allSprites[j].move(0, blockSize * 30);
				rowCounter++;
			}
			else if (clearRow == true && allSprites[j].getPosition().y < rowNumber)
			{
				allSprites[j].move(0, blockSize);
			}
			if (clearRow == false && allSprites[j].getPosition().y == i)
			{
				rowCounter++;
			}
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

	for (int i = 0; i < allSprites.size() - vectorSize; i += vectorSize)
	{
		if (allSprites[i].getPosition().y > blockSize * 30 && allSprites[i + 1].getPosition().y > blockSize * 30 && allSprites[i + 2].getPosition().y > blockSize * 30 && allSprites[i + 3].getPosition().y > blockSize * 30)
		{
			delete blockVector[i / vectorSize];
			blockVector.erase(blockVector.begin() + i / vectorSize);
			allSprites.erase(allSprites.begin() + i, allSprites.begin() + i + 4);
			locationNumber--;
			i = -vectorSize;
		}
	}
}

StateStart::~StateStart()
{
}
