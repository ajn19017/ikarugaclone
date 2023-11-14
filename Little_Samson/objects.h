#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Object {
public:
    Object();
    void update();
    void draw();
    float position;
    float size;
    sf::Texture texture;
    sf::Sprite sprite;    
};