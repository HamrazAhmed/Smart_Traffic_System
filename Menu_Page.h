#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"

class Menu
{

public:
	void present()
	{
        ////////////////////////////////////////////////////////////

    // Create a window
        sf::RenderWindow window(sf::VideoMode(640, 640), "Smart Traffix");

        // Load background texture
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("Accessories/Main Page.png")) {
            std::cerr << "Error loading background image!" << std::endl;
            return;
        }

        // Create a sprite for the background
        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
        );

        // Load font
        sf::Font font;
        if (!font.loadFromFile("Accessories/ABG.otf")) {
            std::cerr << "Error loading font!" << std::endl;
            return;
        }

        // Create welcome text
        sf::Text welcomeText;
        welcomeText.setFont(font);
        welcomeText.setString("Welcome to\n Smart Traffix Simulation");
        welcomeText.setCharacterSize(30); // Font size
        welcomeText.setFillColor(sf::Color::White); // Text color
        welcomeText.setStyle(sf::Text::Bold | sf::Text::Italic);

        // Center welcome text
        sf::FloatRect welcomeBounds = welcomeText.getLocalBounds();
        welcomeText.setOrigin(welcomeBounds.width / 2, welcomeBounds.height / 2);
        welcomeText.setPosition(window.getSize().x / 2, window.getSize().y / 2 - 100);

        // Create "Start!" text
        sf::Text startText;
        startText.setFont(font);
        startText.setString("Start!");
        startText.setCharacterSize(40); // Font size
        startText.setFillColor(sf::Color::Yellow); // Text color
        startText.setStyle(sf::Text::Bold);

        // Position the "Start!" text in the center of the screen below the welcome text
        sf::FloatRect startBounds = startText.getLocalBounds();
        startText.setOrigin(startBounds.width / 2, startBounds.height / 2);
        startText.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 50);

        // Main loop
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Handle mouse click events
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (startText.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        window.close(); // Exit the rendering loop
                    }
                }
            }

            // Clear and draw
            window.clear();
            window.draw(backgroundSprite); // Draw background
            window.draw(welcomeText);      // Draw welcome text
            window.draw(startText);        // Draw "Start!" text
            window.display();
        }


        ////////////////////////////////////////////////////////////
	}

};
