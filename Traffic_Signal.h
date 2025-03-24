#pragma once
#include<string.h>
#include <iomanip>
#include <sstream>

class Traffic_Signal
{

//____
public:

	sf::CircleShape red, yellow, green;


public:

	Traffic_Signal()
	{
		red.setRadius(2.f);
		red.setPosition(364.f, 113.f);
		red.setFillColor(sf::Color::Red);
		red.setOutlineThickness(5.f);
		red.setOutlineColor(sf::Color(64, 64, 64));

		yellow.setRadius(2.f);
		yellow.setPosition(364.f, 133.f);
		yellow.setFillColor(sf::Color::Yellow);
		yellow.setOutlineThickness(5.f);
		yellow.setOutlineColor(sf::Color(64, 64, 64));

		green.setRadius(2.f);
		green.setPosition(364.f, 153.f);
		green.setFillColor(sf::Color::Green);
		green.setOutlineThickness(5.f);
		green.setOutlineColor(sf::Color(64, 64, 64));
	}

};


//////////////////////////////////////////////////////////////////////		Some Timing Stuff

void PeekHrsTiming(sf::RenderWindow& window, bool& PeekTime, sf::Clock& Main_Clock, sf::Text& PeekTimeText)
{
    std::string timeString;

    // Initial times for both conditions
    int min = 0, hrs = 7, min1 = 30, hrs1 = 4;

    // Variable to track elapsed time in each condition
    int elapsedTime = 0;

    while (Main_Clock.getElapsedTime().asSeconds() < 301)
    {
        elapsedTime = int(Main_Clock.getElapsedTime().asSeconds()) % 60;

        if (elapsedTime > 30 && elapsedTime < 70) // First condition: 7:00 AM start
        {
            PeekTime = true;

            // Increment minutes based on elapsed time (in seconds)
            min = (elapsedTime % 60); // Minutes reset after 59

            if (min == 59)
            {
                min = 0;
            }

            // Format the time string as HH:MM AM
            timeString = std::to_string(hrs) + ":" + (min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + " AM";

            // Increment hours when minutes exceed 59
		
            if (min == 59)
            {
                min = 0;
                if(hrs == 7)
                hrs++; // Increment the hour
            }

        }
        else if (elapsedTime > 170 && elapsedTime < 220) // Second condition: 4:30 AM start
        {
            PeekTime = true;

            // Increment minutes based on elapsed time (in seconds)
            min = (elapsedTime % 60); // Minutes reset after 59

            if (min == 59)
            {
                min = 0;
            }

            // Format the time string as HH:MM AM
            timeString = std::to_string(hrs) + ":" + (min < 10 ? "0" + std::to_string(min) : std::to_string(min)) + " AM";

            // Increment hours when minutes exceed 59
            if (min == 59)
            {
                min = 0;
                if (hrs == 4 || hrs == 5)
                    hrs++; // Increment the hour
            }
        }
        else
        {
            PeekTime = false;
            timeString = " ";
        }

        // Update the displayed time string
        PeekTimeText.setString("Peek Hour Time\n      " + timeString);
    }
}






