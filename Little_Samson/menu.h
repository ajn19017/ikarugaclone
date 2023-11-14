#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu {
public:
    Menu(sf::RenderWindow& window);
    void loopEvents(sf::RenderWindow& window);

private:
    sf::Texture menuBackground;
    sf::Sprite sprite;
    sf::ConvexShape menuArrow;
    sf::Color bgColor;
    float menuArrow_x;
    float menuArrow_y;
    float menuArrowTopPosition;
    float menuArrowBottomPosition;
    int menuArrowJump;
};