#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory> // For std::unique_ptr

class GameState {
public:
    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~GameState() {}
};

class MenuState : public GameState {

public:
    MenuState(sf::RenderWindow& window) {
        // Initialize menu items
        menuItems.push_back("Start Game");
        menuItems.push_back("Options");
        menuItems.push_back("Exit");

        // Load a font (make sure you have a font file, e.g., Arial.ttf)
        if (!font.loadFromFile("Arial.ttf")) {
            // Handle error
        }

        // Set up text elements for each menu item
        for (size_t i = 0; i < menuItems.size(); ++i) {
            sf::Text text;
            text.setFont(font);
            text.setString(menuItems[i]);
            text.setCharacterSize(30); // Or any other size
            text.setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
            text.setPosition(100, 100 + i * 40); // Adjust positioning as needed
            menuTexts.push_back(text);
        }
    }

    void handleInput(sf::RenderWindow& window) override {
        // Handle user input for menu navigation
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    if (selectedItemIndex > 0) {
                        selectedItemIndex--;
                    }
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    if (selectedItemIndex < menuItems.size() - 1) {
                        selectedItemIndex++;
                    }
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    // Handle menu selection (start game, options, etc.)
                }
            }
        }
    }

    void update(float deltaTime) override {
        // Update the menu state
        for (size_t i = 0; i < menuTexts.size(); ++i) {
            menuTexts[i].setFillColor(i == selectedItemIndex ? sf::Color::Red : sf::Color::White);
        }
    }

    void render(sf::RenderWindow& window) override {
        // Render the menu
        window.clear();
        for (const auto& text : menuTexts) {
            window.draw(text);
        }
        window.display();
    }

private:
    std::vector<std::string> menuItems;
    std::vector<sf::Text> menuTexts;
    sf::Font font;
    size_t selectedItemIndex = 0;
};

class PlayingState : public GameState {
    // Implement handleInput, update, and render for the game play
public:
    void handleInput(sf::RenderWindow& window) override {
        // Handle user input specific to the menu state
    }

    void update(float deltaTime) override {
        // Update the menu state (e.g., animations, selections) based on deltaTime
    }

    void render(sf::RenderWindow& window) override {
        // Render the menu (e.g., draw menu items, background)
    }
};

class PausedState : public GameState {
    // Implement handleInput, update, and render for the paused state
public:
    void handleInput(sf::RenderWindow& window) override {
        // Handle user input specific to the menu state
    }

    void update(float deltaTime) override {
        // Update the menu state (e.g., animations, selections) based on deltaTime
    }

    void render(sf::RenderWindow& window) override {
        // Render the menu (e.g., draw menu items, background)
    }
};


class Game {
public:
    Game() : window(sf::VideoMode(800, 600), "Little Samson Remake") {
        // Initialize to menu state, for example

        currentState = std::make_unique<MenuState>(window);
    }

    void run() {
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Time deltaTime = clock.restart();
            processEvents();
            update(deltaTime.asSeconds());
            render();
        }
    }

private:
    sf::RenderWindow window;
    std::unique_ptr<GameState> currentState;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else
                currentState->handleInput(window);
        }
    }

    void update(float deltaTime) {
        currentState->update(deltaTime);
        // Change state based on game logic if necessary
        // e.g., if (gameOver) currentState = std::make_unique<GameOverState>();
    }

    void render() {
        window.clear();
        currentState->render(window);
        window.display();
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}