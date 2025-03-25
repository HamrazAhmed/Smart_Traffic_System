#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include<iostream>;
#include<Windows.h>
#include<string.h>
#include<vector>
using namespace std;

const wchar_t* pipeName = L"\\\\.\\pipe\\challan_pipe";



void backgroundScene(sf::Texture& backgroundTexture, sf::Sprite& backgroundSprite, sf::RenderWindow& window, sf::Font& font, sf::Text& heading, sf::Texture& TableTexture, sf::Sprite& TableSprite)
{
    if (!backgroundTexture.loadFromFile("C:/Users/Salman Ahmed/Documents/SFML/Accessories/PBG.jpg")) { // Replace with your background image path
        std::cerr << "Error loading background image!" << std::endl;
        return;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );


    if (!font.loadFromFile("C:/Users/Salman Ahmed/Documents/SFML/Accessories/ABG.otf")) { // Replace with your font path
        std::cerr << "Error loading font!" << std::endl;
        return;
    }


    heading.setFont(font);
    heading.setString("Cars Challan List");
    heading.setCharacterSize(50);
    heading.setFillColor(sf::Color::White);
    heading.setStyle(sf::Text::Bold);
    heading.setPosition(
        (window.getSize().x - heading.getLocalBounds().width) / 2.0f, // Center horizontally
        20.0f // Top margin
    );

    TableTexture.loadFromFile("C:/Users/Salman Ahmed/Documents/SFML/Accessories/Table.png");


    TableSprite.setTexture(TableTexture);

    TableSprite.setScale(1.1, 1.2);

    TableSprite.setPosition(
        (window.getSize().x - TableSprite.getLocalBounds().width - 40) / 2.0f, // Center horizontally
        200.0f // Top margin
    );
}

void PIPING(HANDLE& hPipe)
{
    hPipe = CreateFile(
        pipeName,           // Pipe name
        GENERIC_READ,       // Read-only access
        0,                  // No sharing
        NULL,               // Default security attributes
        OPEN_EXISTING,      // Opens existing pipe
        0,                  // Default attributes
        NULL                // No template file
    );

    // Check if the pipe handle is valid
    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to connect to the pipe. Error: " << GetLastError() << std::endl;
        /*return -1;*/
    }
}


int main()
{
    vector<string> messages;

    HANDLE hPipe;
    PIPING(hPipe);


    sf::RenderWindow window(sf::VideoMode(1200, 800), "Cars Challan List");
    window.setFramerateLimit(60);


    // Load background texture
    sf::Texture backgroundTexture;

    // Create background sprite
    sf::Sprite backgroundSprite;

    // Load font
    sf::Font font;

    // Heading text: Cars Challan List
    sf::Text heading;

    //////////////////////////////////////////////////////////////////////////              Table

    sf::Texture TableTexture;

    sf::Sprite TableSprite;



    backgroundScene(backgroundTexture, backgroundSprite, window, font, heading, TableTexture, TableSprite);

    // Clear window
    window.clear();

    // Draw background and heading
    window.draw(backgroundSprite);
    window.draw(heading);
    window.draw(TableSprite);



    // Display all elements
    window.display();


    sf::Text License[4];  sf::Text Brand[4]; sf::Text Speed[4];

    int i = 0;
        while (window.isOpen()) 
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) 
                {
                    window.close();
                }
            }



            // Define the exact size of the message you want to read
            const DWORD messageSize = 8; // Desired message length
            char buffer[messageSize] = { 0 }; // Initialize the buffer to hold the exact length
            DWORD bytesRead = 0;            // Variable to store the actual bytes read

            // Read data from the pipe
            BOOL success = ReadFile(
                hPipe,           // Handle to the pipe
                buffer,          // Buffer to store the received data
                messageSize,     // Size of the buffer (limited to the desired message size)
                &bytesRead,      // Actual number of bytes read
                NULL             // Not using overlapped I/O
            );

            // Check if the read operation was successful
            if (!success) {
                std::cerr << "Failed to read from the pipe. Error: " << GetLastError() << std::endl;
            }
            else 
            {
                // Add the received message to the array of strings
                messages.push_back(std::string(buffer, bytesRead)); // Convert buffer to std::string

                License[i].setFont(font);
                License[i].setString(buffer);
                License[i].setCharacterSize(20);
                License[i].setFillColor(sf::Color::White);
                License[i].setStyle(sf::Text::Bold);
                License[i].setPosition(440,350 + i * 80);

                Brand[i].setFont(font);

                int choose = rand() % 4 + 1;

                if (choose == 1)
                {
                    Brand[i].setString("Toyota");
                }
                else if (choose == 2)
                {
                    Brand[i].setString("Suzuki");
                }
                else if (choose == 3)
                {
                    Brand[i].setString("Honda");
                }
                else if (choose == 4)
                {
                    Brand[i].setString("Changan");
                }

                
                Brand[i].setCharacterSize(20);
                Brand[i].setFillColor(sf::Color::White);
                Brand[i].setStyle(sf::Text::Bold);
                Brand[i].setStyle(sf::Text::Bold);
                Brand[i].setPosition(615, 350 + i * 80);

                Speed[i].setFont(font);
                Speed[i].setString("70 km/h");
                Speed[i].setCharacterSize(20);
                Speed[i].setFillColor(sf::Color::White);
                Speed[i].setStyle(sf::Text::Bold);
                Speed[i].setStyle(sf::Text::Bold);
                Speed[i].setPosition(790, 350 + i * 80);

                i++;
            }







            // Clear window
            window.clear();

            // Draw background and heading
            window.draw(backgroundSprite);
            window.draw(heading);
            window.draw(TableSprite);
        
            for (int i = 0; i < 4; i++)
            {
                window.draw(License[i]);
                window.draw(Brand[i]);
                window.draw(Speed[i]);
            }

            // Display all elements
            window.display();
        }


	return 0;

}