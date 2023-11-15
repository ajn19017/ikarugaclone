#include "objects.h"
#include <iostream>

Object::Object(std::string texturePath, float x, float y, float speed, sf::Vector2f scale){
    if (!texture.loadFromFile(texturePath))
        std::cout << "Error loading texture\n";
    sprite.setTexture(texture);
    size = sprite.getLocalBounds();
    sprite.setPosition(x, y);
    sprite.scale(scale);
    velocity = speed;
}

void Object::update() {
    sf::Vector2f position = sprite.getPosition();
    sprite.setPosition(position.x, position.y+velocity);
    if (position.y > 768)
        isAlive = false;
}

void Object::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

FightingObject::FightingObject(std::string texturePath, float x, float y, float speed, sf::Vector2f scale)
    : Object(texturePath, x, y, speed, scale) {
    health = 100;
}

void FightingObject::shoot(int damage) {
    //spawn bullet with velocity
}

void FightingObject::takeDamage(int damage) {
    health = health - damage;
    if (health <= 0){
        isAlive = false;
    }
}

PlayerObject::PlayerObject(std::string texturePath, float x, float y, float speed, sf::Vector2f scale)
    : FightingObject(texturePath, x, y, speed, scale) {
    score = 0;
    lives = 5;

}
void PlayerObject::handleInput(sf::RenderWindow& window) {


        sf::Vector2f playerPosition = sprite.getPosition();
        sf::Vector2f playerScale = sprite.getScale();
        float spriteWidth = sprite.getLocalBounds().width * playerScale.x;
        float spriteHeight = sprite.getLocalBounds().height * playerScale.y;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (playerPosition.x - velocity >= 0)) {
            playerPosition.x -= velocity;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (playerPosition.x + spriteWidth + velocity <= 1024)) {
            playerPosition.x += velocity;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (playerPosition.y - velocity >= 0)) {
            playerPosition.y -= velocity;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (playerPosition.y + spriteHeight + velocity <= 768)) {
            playerPosition.y += velocity;
        }
        sprite.setPosition(playerPosition.x, playerPosition.y);
        window.draw(sprite);

}