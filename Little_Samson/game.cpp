#include "game.h"
#include "objects.h"

void Game::scrollBackground(sf::RenderWindow& window) {

    // Create two sprites from the same texture
    // Set the initial position of the second sprite next to the first
    background2.setPosition(0, (float)scrollbg.getSize().y);

    // Update the position of both sprites
    backgroundY += bgScrollSpeed;
    if (backgroundY >= static_cast<float>(scrollbg.getSize().y)) {
        backgroundY = 0;
    }

    // Set the position of the sprites
    background1.setPosition(0, backgroundY);
    background2.setPosition(0, backgroundY - scrollbg.getSize().y);

    // Draw the sprites
    window.draw(background1);
    window.draw(background2);
}

Game::Game(sf::RenderWindow& window) {
	if (!scrollbg.loadFromFile("images/scrollbg.png"))
		std::cout << "Error loading background\n";
	background1.setTexture(scrollbg);
	background2.setTexture(scrollbg);
	bgColor = sf::Color::Black;
	backgroundY = 0;
}

void Game::addEnemiesToGrid(Object* enemyGrid[][10], const sf::Vector2u& windowSize, const std::string& texturePath, std::string spawnFormation) {
	const int rows = 10;
	const int cols = 10;
	if (spawnFormation == "leftDiag"){
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i == j) { 
					float initialX = (float)j * windowSize.x / rows;
					float initialY = (float)-(i * 50); // Example: 50 units apart vertically
					enemyGrid[i][j] = new Object(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyList.push_back(sf::Vector2u(i,j));
				}
			}
		}
	}
	else if (spawnFormation == "rightDiag") {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i + j == cols - 1) {
					float initialX = (float)j * windowSize.x / cols;
					float initialY = (float)-(i * 50); // Example: 50 units apart vertically
					enemyGrid[i][j] = new Object(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyList.push_back(sf::Vector2u(i, j));
				}
			}
		}
	}
	else if (spawnFormation == "all") {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				float initialX = (float)j * windowSize.x / rows;
				float initialY = (float)-(i * 50); // Example: 50 units apart vertically
				enemyGrid[i][j] = new Object(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
				enemyList.push_back(sf::Vector2u(i, j));
			}
		}
	}
	else if (spawnFormation == "cross") {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i == j || i + j == cols - 1) {
					float initialX = (float)j * windowSize.x / cols;
					float initialY = (float)-(i * 50); // Example: 50 units apart vertically
					enemyGrid[i][j] = new Object(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyList.push_back(sf::Vector2u(i, j));
				}
			}
		}
	}
}
void Game::checkEnemiesInGrid(Object* enemyGrid[][10], sf::RenderWindow& window) {
	
	
	for (auto iterator = enemyList.begin(); iterator != enemyList.end(); /* no increment here */) {
		auto index = *iterator; 

		if (enemyGrid[index.x][index.y] != nullptr && enemyGrid[index.x][index.y]->isAlive) {
			enemyGrid[index.x][index.y]->update();
			enemyGrid[index.x][index.y]->draw(window);
			++iterator;
		}
		else {
			delete enemyGrid[index.x][index.y];
			enemyGrid[index.x][index.y] = nullptr;
			iterator = enemyList.erase(iterator);
		}
	}
	if (enemyList.empty())
		enemyWave += 1;
}
void Game::loopEvents(sf::RenderWindow& window)
{

	Object* enemyGrid[10][10] = { 0 };
	sf::Vector2u windowSize = window.getSize();
	addEnemiesToGrid(enemyGrid, windowSize,"images/enemy2.png", "cross");

	PlayerObject player("images/ship1.png",500,500,7, sf::Vector2f(0.5f, 0.5f));

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(bgColor);
		scrollBackground(window);
		player.handleInput(window);
		checkEnemiesInGrid(enemyGrid, window);
		if(enemyList.empty() && enemyWave == 1)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy3.png", "leftDiag");
		if (enemyList.empty() && enemyWave == 2)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy4.png", "all");
		if (enemyList.empty() && enemyWave == 3)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy5.png", "cross");
		if (enemyList.empty() && enemyWave == 3)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy6.png", "cross");
		window.display();
		//spawn-matrix
		//check if spawn-matrix is empty
		//add new wave (next type of enemy) to matrix
		
	}
}