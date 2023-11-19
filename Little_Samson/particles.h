#pragma once
#include <SFML/Graphics.hpp>


struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifespan;  // in seconds
};

class ParticleSystem {
public:
    ParticleSystem(std::string texturePath, sf::Vector2f scale, int alpha);
    sf::Sprite particleSprite;
    sf::Texture particleTexture;
    void update(float dt); // dt is the delta time
    void render(sf::RenderWindow& window);
    void addParticle(const Particle& particle);


private:
    std::vector<Particle> particles;
};