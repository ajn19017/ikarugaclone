#include "menu.h"
#include "game.h"
#include "objects.h"

enum class GameState {
    MENU,
    GAME,
    PAUSE
};

void centerEntity(sf::Text& object, int windowWidth, int windowHeight) {
    sf::FloatRect textRect = object.getGlobalBounds();
    // Set the origin of the text to its center
    object.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    object.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
}

void centerEntity(sf::Sprite& object, int windowWidth, int windowHeight) {
    sf::FloatRect textRect = object.getGlobalBounds();
    // Set the origin of the text to its center
    object.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    object.setPosition(windowWidth / 2.0f, windowHeight / 2.0f);
}

int main()
{
    int width{ 1024 };
    int height{ 768 };
    sf::RenderWindow window(sf::VideoMode(width, height), "Space Skirmish", sf::Style::Default);
    window.setFramerateLimit(60);
    GameState currentState = GameState::MENU;
    Menu menu(window);
    menu.loopEvents(window);
    return 0;
}

//sf::Font font;
//if (!font.loadFromFile("arial.ttf"))
//{
//    // error...
//}
//sf::Text text;
//
//// select the font
//text.setFont(font); // font is a sf::Font
//
//// set the string to display
//text.setString("Hello world");
//
//// set the character size
//text.setCharacterSize(24); // in pixels, not points!
//
//// set the color
//text.setFillColor(sf::Color::Black);
//
//// set the text style
//text.setStyle(sf::Text::Bold);
//
//centerEntity(text, width, height);