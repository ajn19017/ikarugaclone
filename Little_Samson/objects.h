#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Object {
public:
    Object(std::string texturePath, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
    void update();
    void draw(sf::RenderWindow& window);
    float velocity {0};
    bool isAlive = true;
    sf::FloatRect size;
    sf::Texture texture;
    sf::Sprite sprite;    
};

class FightingObject : public Object
{
    public:
        FightingObject(std::string texturePath, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
        void takeDamage(int damage);
        virtual void shoot(int damage);
    protected:
        int health;
};

class EnemyObject : public FightingObject
{
};

class RotatingEnemyObject : public EnemyObject
{
};

class FastEnemyObject : public EnemyObject
{
};

class BossObject : public FightingObject
{
};

class PlayerObject : public FightingObject
{
    public:
    PlayerObject(std::string texturePath, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
        void shoot();
        void handleInput(sf::RenderWindow& window);
        int score;
        int lives;
        
};