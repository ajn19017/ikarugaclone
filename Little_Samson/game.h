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
    void addEnemiesToGrid(Object* enemyGrid[][10], const sf::Vector2u& windowSize, const std::string& texturePath, std::string spawnFormation);
    void checkEnemiesInGrid(Object* enemyGrid[][10], sf::RenderWindow& window);

private:
    int enemyWave{ 0 };
    float backgroundY;
    float bgScrollSpeed{ 0.5 };
    int noOfEnemies{0};
    std::list<sf::Vector2u> enemyList;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Texture scrollbg;
    sf::ConvexShape menuArrow;
    sf::Color bgColor;
};