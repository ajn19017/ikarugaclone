#include "game.h"

void Game::scrollBackground(sf::RenderWindow& window) {
	float scrollSpeed = 0.25;

    // Create two sprites from the same texture
    // Set the initial position of the second sprite next to the first
    background2.setPosition(0, scrollbg.getSize().y);

    // Update the position of both sprites
    backgroundY += scrollSpeed;
    if (backgroundY >= static_cast<float>(scrollbg.getSize().y)) {
        backgroundY = 0;
    }

    // Set the position of the sprites
    background1.setPosition(0, backgroundY);
    background2.setPosition(0, backgroundY - scrollbg.getSize().y);

    // Draw the sprites
    window.draw(background1);
    window.draw(background2);
	window.display();
}

Game::Game(sf::RenderWindow& window) {
	if (!scrollbg.loadFromFile("images/scrollbg.png"))
		std::cout << "Error loading background\n";
	background1.setTexture(scrollbg);
	background2.setTexture(scrollbg);
	bgColor = sf::Color::Black;
	backgroundY = 0;
}

void Game::loopEvents(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(bgColor);
		scrollBackground(window);
		
		
	}
}