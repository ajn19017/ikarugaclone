#include "menu.h"
#include "game.h"

Menu::Menu(sf::RenderWindow& window) {
	if (!menuBackground.loadFromFile("images/menuBackground.png"))
		std::cout << "Error loading background\n";
	else {
		printf("background loaded");
	}
	sprite.setTexture(menuBackground);
	bgColor = sf::Color::Black;
	menuArrowJump = 58;
	menuArrow_x = 370;
	menuArrow_y = 280;
	menuArrowTopPosition = menuArrow_y; // Y position of the top menu item
	menuArrowBottomPosition = menuArrow_y + menuArrowJump*2;

	menuArrow.setPointCount(4);
	menuArrow.setPoint(0, sf::Vector2f(0, 0));
	menuArrow.setPoint(1, sf::Vector2f(30, 9));
	menuArrow.setPoint(2, sf::Vector2f(30, 11));
	menuArrow.setPoint(3, sf::Vector2f(0, 20));

	menuArrow.setPosition(menuArrow_x, menuArrow_y);
	menuArrow.setFillColor(sf::Color::Black);
	menuArrow.setOutlineThickness(3);
	menuArrow.setOutlineColor(sf::Color::White);
}

void Menu::loopEvents(sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				if (menuArrow_y == menuArrowTopPosition){
					Game game(window);
					game.loopEvents(window);
				}
				else if (menuArrow_y == menuArrowTopPosition+menuArrowJump){
					//leaderboard
				}
				else if (menuArrow_y == menuArrowBottomPosition){
					window.close(); //exit
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				menuArrow_y -= menuArrowJump;
				if (menuArrow_y < menuArrowTopPosition) {
					menuArrow_y = menuArrowBottomPosition;
				}
				menuArrow.setPosition(menuArrow_x, menuArrow_y);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				menuArrow_y += menuArrowJump;
				if (menuArrow_y > menuArrowBottomPosition) {
					menuArrow_y = menuArrowTopPosition;
				}
				menuArrow.setPosition(menuArrow_x, menuArrow_y);
			}
			window.clear(bgColor);
			window.draw(sprite);
			window.draw(menuArrow);
			window.display();
		}
	}
}
