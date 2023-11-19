#pragma once
#include "objects.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>


class Game {
public:
    Game(sf::RenderWindow& window);
    void loopEvents(sf::RenderWindow& window);
    void scrollBackground(sf::RenderWindow& window);
    void addEnemiesToGrid(FightingObject* enemyGrid[][10], const sf::Vector2u& windowSize, const std::string& texturePath, std::string spawnFormation, int enemyHealth);
    void checkEnemiesInGrid(FightingObject* enemyGrid[][10], sf::RenderWindow& window);
    void checkBullets(sf::RenderWindow& window, std::vector<Bullet>& bullets);
    void checkCollisions(FightingObject* enemyGrid[][10], std::vector<Bullet>& bullets, sf::RenderWindow& window);
    void checkShield(sf::RenderWindow& window, PlayerObject& player, float deltaTime, FightingObject* enemyGrid[][10]);
    sf::Texture getTexture(std::string string);
    
private:
    int enemyWave{ 0 };
    float backgroundY;
    float bgScrollSpeed{ 0.5 };
    int bulletThrust{ 0 };
    std::list<sf::Vector2u> enemyList;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Texture scrollbg;
    sf::Texture bulletTexture;
    sf::ConvexShape menuArrow;
    sf::Color bgColor;
};