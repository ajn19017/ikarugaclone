#include "objects.h"
#include "game.h"
#include "particles.h"
#include <iostream>

Object::Object(std::string texturePath, float x, float y, float speed, sf::Vector2f scale){
    if (!texture.loadFromFile(texturePath))
        std::cout << "Error loading texture\n";
    sprite.setTexture(texture);
    size = sprite.getLocalBounds();
    sprite.setPosition(x, y);
    sprite.scale(scale);
    max_velocity = speed;
}

Object::Object(sf::Texture& texture, float x, float y, float speed, sf::Vector2f scale) {
    sprite.setTexture(texture);
    size = sprite.getLocalBounds();
    sprite.setPosition(x, y);
    sprite.scale(scale);
    max_velocity = speed;
}

void Object::update() {
    sf::Vector2f position = sprite.getPosition();
    sprite.setPosition(position.x, position.y+max_velocity);
    if (position.y > 768)
        isAlive = false;
}

void Object::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

Bullet::Bullet(sf::Texture& texture, float x, float y, float speed, sf::Vector2f scale)
    : Object(texture, x, y, speed, scale) {

}

void Bullet::update(sf::CircleShape& circle) {

    sf::Vector2f position = sprite.getPosition();
    circle.setPosition(position.x-1.0f, position.y - max_velocity + 13.0f);
    sprite.setPosition(position.x, position.y - max_velocity);
    if (position.y < 0)
        isAlive = false;
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

template <typename T> int sign(T val) {
    return (T(0) < val) - (val < T(0));
}

void PlayerObject::handleInput(sf::RenderWindow& window, std::vector<Bullet>& bullets, sf::Texture& bulletTexture, float deltaTime, ParticleSystem& particleSystem, Particle& particle) {

        bulletCooldown -= deltaTime; // Decrease cooldown timer
        shieldCooldown -= deltaTime; // Decrease cooldown timer
        sf::Vector2f playerPosition = sprite.getPosition();
        sf::Vector2f playerScale = sprite.getScale();
        float spriteWidth = sprite.getLocalBounds().width * playerScale.x;
        float spriteHeight = sprite.getLocalBounds().height * playerScale.y;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bulletCooldown <= 0.0f) {
            bullets.emplace_back(bulletTexture, playerPosition.x+7, playerPosition.y+30, 5.0f, sf::Vector2f(0.2f, 0.2f));
            bullets.emplace_back(bulletTexture, playerPosition.x + 73, playerPosition.y + 30, 5.0f, sf::Vector2f(0.2f, 0.2f));
            bulletCooldown = bulletCooldownTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && shieldCooldown <= 0.0f) {
            shield = true;
            shieldCooldown = shieldCooldownTime;
        }
        int xdir = (int)-sf::Keyboard::isKeyPressed(sf::Keyboard::Left) + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        int ydir = (int)-sf::Keyboard::isKeyPressed(sf::Keyboard::Up) + (int)sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

        if (xdir != 0){
            if (fabsf(xvelocity) < max_velocity) {
                xvelocity += acceleration * xdir;
            }
                
            else
                xvelocity = max_velocity * xdir;
        }
        else{
            if (fabsf(xvelocity) > 0.0f)
                xvelocity -= std::min(acceleration, fabsf(xvelocity)) * sign(xvelocity);
        }

        if ((playerPosition.x + xvelocity <= 0)) {
            playerPosition.x = 0;
            xvelocity = 0;
        }
        if ((playerPosition.x + spriteWidth + xvelocity >= 1024)) {
            playerPosition.x = 1024 - spriteWidth;
            xvelocity = 0;
        }

        if (ydir != 0){
            if (fabsf(yvelocity) < max_velocity)
                yvelocity += acceleration * ydir;
            else
                yvelocity = max_velocity * ydir;
        }
        else{
            if (fabsf(yvelocity) > 0.0f)
                yvelocity -= std::min(acceleration, fabsf(yvelocity)) * sign(yvelocity);
        }

        if ((playerPosition.y + yvelocity <= 0)) {
            playerPosition.y = 0;
            yvelocity = 0;
        }
        if ((playerPosition.y + spriteHeight + yvelocity >= 768)) {
            playerPosition.y = 768 - spriteHeight;
            yvelocity = 0;
        }
        playerPosition.x += xvelocity;
        playerPosition.y += yvelocity;

        sprite.setPosition(playerPosition.x, playerPosition.y);
        window.draw(sprite);

}

