#include "menu.h"
#include "game.h"
#include "objects.h"

enum class GameState {
    MENU,
    GAME,
    PAUSE
};


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
