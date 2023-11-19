#include "game.h"
#include "objects.h"
#include "particles.h"

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
	if (!bulletTexture.loadFromFile("images/bullet1.png"))
		std::cout << "Error loading bullet\n";
	background1.setTexture(scrollbg);
	background2.setTexture(scrollbg);
	bgColor = sf::Color::Black;
	backgroundY = 0;

}

sf::Texture Game::getTexture(std::string string) {
	if (string == "bullet")
		return bulletTexture;
}

void Game::addEnemiesToGrid(FightingObject* enemyGrid[][10], const sf::Vector2u& windowSize, const std::string& texturePath, std::string spawnFormation, int enemyHealth) {
	const int rows = 10;
	const int cols = 10;
	if (spawnFormation == "leftDiag"){
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (i == j) { 
					float initialX = (float)j * windowSize.x / rows;
					float initialY = (float)-(i * 50); // Example: 50 units apart vertically
					enemyGrid[i][j] = new FightingObject(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyGrid[i][j]->health = enemyHealth;
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
					enemyGrid[i][j] = new FightingObject(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyGrid[i][j]->health = enemyHealth;
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
				enemyGrid[i][j] = new FightingObject(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
				enemyGrid[i][j]->health = enemyHealth;
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
					enemyGrid[i][j] = new FightingObject(texturePath, initialX, initialY, 2.0f, sf::Vector2f(0.5f, 0.5f));
					enemyGrid[i][j]->health = enemyHealth;
					enemyList.push_back(sf::Vector2u(i, j));
				}
			}
		}
	}
}
void Game::checkEnemiesInGrid(FightingObject* enemyGrid[][10], sf::RenderWindow& window) {
	
	
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

void Game::checkCollisions(FightingObject* enemyGrid[][10], std::vector<Bullet>& bullets, sf::RenderWindow& window) {
	
	for (auto& bullet : bullets) {
		sf::Vector2f bulletPosition = bullet.sprite.getPosition();
		bulletPosition.x += 6.3f;

		for (auto enemyIterator = enemyList.begin(); enemyIterator != enemyList.end();) {
			auto index = *enemyIterator;
			//if (enemyGrid[index.x][index.y] != nullptr && enemyGrid[index.x][index.y]->isAlive){}
			sf::FloatRect enemyBounds = enemyGrid[index.x][index.y]->sprite.getGlobalBounds();

			if (enemyBounds.contains(bulletPosition)) {
				enemyGrid[index.x][index.y]->health -= 20;
				bullet.isAlive = false;
			}
			if (enemyGrid[index.x][index.y]->health <= 0) {
				enemyGrid[index.x][index.y]->isAlive = false;
			}
			++enemyIterator;
		}

	}
}

void Game::checkBullets(sf::RenderWindow& window, std::vector<Bullet>& bullets)
{
	if (bulletThrust > 110){
		bulletThrust = 50;
	}
	else{
		bulletThrust += 20;
	}

	sf::CircleShape circle(7);
	circle.setPointCount(10);
	circle.scale(1,2);
	circle.setFillColor(sf::Color(255, 100, 0, bulletThrust));

	for (auto& bullet : bullets) {
		bullet.update(circle);
		window.draw(circle);
		window.draw(bullet.sprite);
		
	}

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
		return !bullet.isAlive;
		}), bullets.end());


}
bool isCircleIntersectingWithEnemy(const sf::CircleShape& circle, const sf::FloatRect& enemyBounds) {
	float radius = circle.getRadius();
	sf::Vector2f circleCenter = circle.getPosition();
	float circleDistanceX = abs(circleCenter.x - (enemyBounds.left + enemyBounds.width/2));
	float circleDistanceY = abs(circleCenter.y - (enemyBounds.top + enemyBounds.height / 2));

	if (circleDistanceX > (enemyBounds.width / 2 + radius)) { return false; }
	if (circleDistanceY > (enemyBounds.height / 2 + radius)) { return false; }

	if (circleDistanceX <= (enemyBounds.width / 2)) { return true; }
	if (circleDistanceY <= (enemyBounds.height / 2)) { return true; }

	float cornerDistance_sq = (circleDistanceX - enemyBounds.width / 2) * (circleDistanceX - enemyBounds.width / 2) + (circleDistanceY - enemyBounds.height / 2) * (circleDistanceY - enemyBounds.height / 2);

	return (cornerDistance_sq <= (radius*radius));

}

void Game::checkShield(sf::RenderWindow& window, PlayerObject& player, float deltaTime, FightingObject* enemyGrid[][10]) {
	if (player.shieldTimer >= player.shieldTimeout){
		player.shield = false;
		player.shieldTimer = 0.0f;
		player.shieldAlpha = 255;
	}
	if (player.shield) {
		player.shieldAlpha -= (int)player.shieldAlpha / (60 * player.shieldTimeout);
		player.shieldTimer += deltaTime;
		sf::Vector2u textureSize = player.sprite.getTexture()->getSize();
		sf::Vector2f scale = player.sprite.getScale();
		sf::Vector2f halfSize(textureSize.x * scale.x * 0.5f, textureSize.y * scale.y * 0.5f);
		sf::Vector2f position = player.sprite.getPosition();
		sf::Vector2f origin = player.sprite.getOrigin();
		position.x += halfSize.x - origin.x;
		position.y += halfSize.y - origin.y;
		int radius = (int)2000*player.shieldTimer;
		radius = std::min(radius, 200);
		sf::CircleShape circle(radius);
		circle.setFillColor(sf::Color(180,0,0,player.shieldAlpha));
		circle.setOutlineColor(sf::Color(255,255,255,player.shieldAlpha));
		circle.setOutlineThickness(7.0f);
		circle.setOrigin(radius, radius);
		circle.setPosition(position.x, position.y);
		sf::CircleShape bg_circle = circle;
		bg_circle.setPosition(position.x+2, position.y+2);
		bg_circle.setOutlineColor(sf::Color(0, 0, 0,player.shieldAlpha));
		
		window.draw(bg_circle);
		window.draw(circle);
		for (auto enemyIterator = enemyList.begin(); enemyIterator != enemyList.end();) {
			auto index = *enemyIterator;

			sf::FloatRect enemyBounds = enemyGrid[index.x][index.y]->sprite.getGlobalBounds();
			if (isCircleIntersectingWithEnemy(circle, enemyBounds)) {
				enemyGrid[index.x][index.y]->isAlive = false;
			}
			++enemyIterator;
		}
		
	}
}
void Game::loopEvents(sf::RenderWindow& window)
{
	sf::Clock clock;
	sf::Texture bulletTexture = getTexture("bullet");
	sf::Vector2u windowSize = window.getSize();
	std::vector<Bullet> bullets;
	FightingObject* enemyGrid[10][10] = { 0 };
	PlayerObject player("images/ship1.png", 500, 500, 7, sf::Vector2f(0.5f, 0.5f));

	addEnemiesToGrid(enemyGrid, windowSize,"images/enemy1.png", "cross", 100);
	ParticleSystem particleSystem("images/smoke.png",sf::Vector2f(0.08f,0.08f),50);
	Particle newParticle;
	newParticle.position = sf::Vector2f(500, 500);
	newParticle.velocity = sf::Vector2f(150, 400); 
	newParticle.lifespan = 1.0f;
	Particle newParticle2 = newParticle;
	
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float deltaTime = clock.restart().asSeconds();
		window.clear(bgColor);
		scrollBackground(window);
		player.handleInput(window, bullets, bulletTexture, deltaTime, particleSystem, newParticle);
		checkCollisions(enemyGrid, bullets, window);
		checkEnemiesInGrid(enemyGrid, window);
		checkBullets(window, bullets);
		checkShield(window, player, deltaTime, enemyGrid);
		newParticle.position = player.sprite.getPosition();
		newParticle.position.y += 115;
		newParticle.position.x += 28;
		newParticle2.position.y = newParticle.position.y;
		newParticle2.position.x = newParticle.position.x+16;
		particleSystem.addParticle(newParticle);
		particleSystem.addParticle(newParticle2);
		particleSystem.update(deltaTime); // dt is the delta time
		particleSystem.render(window);
		if(enemyList.empty() && enemyWave == 1)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy3.png", "leftDiag", 100);
		if (enemyList.empty() && enemyWave == 2)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy4.png", "all", 20);
		if (enemyList.empty() && enemyWave == 3)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy5.png", "cross", 50);
		if (enemyList.empty() && enemyWave == 4)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy1.png", "cross", 50);
		if (enemyList.empty() && enemyWave == 5)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy2.png", "all", 20);
		if (enemyList.empty() && enemyWave == 6)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy2.png", "all", 20);
		if (enemyList.empty() && enemyWave == 7)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy3.png", "leftDiag", 100);
		if (enemyList.empty() && enemyWave == 8)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy4.png", "all", 20);
		if (enemyList.empty() && enemyWave == 9)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy5.png", "cross", 50);
		if (enemyList.empty() && enemyWave == 10)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy4.png", "cross", 50);
		if (enemyList.empty() && enemyWave == 11)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy2.png", "all", 30);
		if (enemyList.empty() && enemyWave == 12)
			addEnemiesToGrid(enemyGrid, windowSize, "images/enemy2.png", "all", 30);
		

		window.display();
		
	}
}