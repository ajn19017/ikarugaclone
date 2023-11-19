#include "particles.h"
#include <random>
#include <SFML/Graphics.hpp>

float randomFloat(float min, float max) {
    // static used for efficiency: only one random engine and distribution needed
    static std::random_device rd;  // Obtain a random number from hardware
    static std::mt19937 eng(rd()); // Seed the generator
    static std::uniform_real_distribution<> distr(min, max); // Define the range

    return distr(eng);
}
ParticleSystem::ParticleSystem(std::string texturePath, sf::Vector2f scale, int alpha) {
    particleTexture.loadFromFile(texturePath);
    particleSprite.setTexture(particleTexture);
    particleSprite.setScale(scale.x, scale.y);
    particleSprite.setColor(sf::Color(255,255,255,alpha));
}
void ParticleSystem::addParticle(const Particle& particle) {

    particles.push_back(particle);
}

void ParticleSystem::update(float dt) {
    for (auto& particle : particles) {

        particle.position.y += particle.velocity.y * dt;
        particle.position.x += randomFloat(-particle.velocity.x, particle.velocity.x) * dt;
        particle.lifespan -= dt;
    }

    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return p.lifespan <= 0; }),
        particles.end());
}

void ParticleSystem::render(sf::RenderWindow& window) {
    for (const auto& particle : particles) {

       // sf::RectangleShape shape; 
        //shape.setSize(sf::Vector2f(10.0f,10.0f));
        
        particleSprite.setPosition(particle.position);
        //particleSprite.setFillColor(particle.color);
        window.draw(particleSprite);
    }
}



