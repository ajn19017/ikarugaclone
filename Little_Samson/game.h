#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Game {
public:
    Game(sf::RenderWindow& window);
    void loopEvents(sf::RenderWindow& window);
    void scrollBackground(sf::RenderWindow& window);

private:
    float backgroundY;
    sf::Sprite background1;
    sf::Sprite background2;
    sf::Texture scrollbg;
    sf::ConvexShape menuArrow;
    sf::Color bgColor;
};