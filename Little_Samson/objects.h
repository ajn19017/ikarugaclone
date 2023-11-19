#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "particles.h"

class Object {
public:
    Object(std::string texturePath, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
    Object(sf::Texture& texture, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
    virtual void update();
    void draw(sf::RenderWindow& window);
    float max_velocity {0};
    bool isAlive = true;
    sf::FloatRect size;
    sf::Texture texture;
    sf::Sprite sprite;    
};

class Bullet : public Object
{
public:
    Bullet(sf::Texture& texture, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
    void update(sf::CircleShape& circle);
};

class FightingObject : public Object
{
    public:
        FightingObject(std::string texturePath, float x, float y, float speed, sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f));
        void takeDamage(int damage);
        virtual void shoot(int damage);
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
        void handleInput(sf::RenderWindow& window, std::vector<Bullet>& bullets, sf::Texture& bulletTexture, float deltaTime, ParticleSystem& particleSystem, Particle& particle);
        int score;
        int lives;
        float acceleration = max_velocity/10;
        float xvelocity{ 0 };
        float yvelocity{ 0 };
        float bulletCooldown = 0.0f; 
        float shieldCooldown = 0.0f;
        bool shield{ false };
        float shieldTimer{ 0 };
        int shieldAlpha{ 255 };
        float shieldTimeout{ 0.2f };
        const float bulletCooldownTime = 0.05f; 
        const float shieldCooldownTime = 1.0f;
};