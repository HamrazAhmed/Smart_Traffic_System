#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <Windows.h>
#include <cstring>
#include "Traffic_Signal.h"
using namespace std;


sf::Clock Main_Clock;

bool AvoidTB = false, AvoidLR = false, AvoidBT = false, AvoidRL = false;            //      Some Priority Bools


/////////////////////////////////////////////////////           Cars arriving Clocks

sf::Clock lightVehicleClockTB, heavyVehicleClockTB, emergencyVehicleClockTB, lightVehicleClockLR, heavyVehicleClockLR, emergencyVehicleClockLR;
sf::Clock lightVehicleClockBT, heavyVehicleClockBT, emergencyVehicleClockBT, lightVehicleClockRL, heavyVehicleClockRL, emergencyVehicleClockRL;

bool LaneTB = false;                        /////////           Lane Top_To_Bottom mein gari kharab hone pr on hoga

sf::Clock ChallanClock;               /////////           Challan dalne k liye clock rkha hai, jo kuch time intervals pr kisi b eik gari ki speed kisi random time pr increase kr dega

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PipeTransfer(const std::string& Plate, HANDLE& hPipe);

class Car
{
public:
    string LicensePlate;
    sf::Texture CarTexture;
    sf::Sprite CarSprite;
    bool EV = false;
    bool OOO = false;
    float speed;
    bool KamWalaTruck = false;
    sf::Clock CarSpeedClock;


    virtual void moveCarBottomToTop() = 0;
    virtual void moveCarTopToBottom() = 0;
    virtual void moveCarLeftToRight() = 0;
    virtual void moveCarRightToLeft() = 0;

    void GeneratePlate()
    {
        static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        // Create a random device and generator
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> letterDist(0, 25); // Random index for letters
        std::uniform_int_distribution<int> numberDist(0, 9999); // Random 4-digit number

        // Generate 3 random uppercase letters
        for (int i = 0; i < 3; ++i) {
            LicensePlate += alphabet[letterDist(generator)];
        }

        // Add the '-' character
        LicensePlate += '-';

        // Generate a random 4-digit number and format it to ensure 4 digits
        int number = numberDist(generator);
        LicensePlate += (number < 10 ? "000" : (number < 100 ? "00" : (number < 1000 ? "0" : ""))) + std::to_string(number);
    }

};



///////////////////////////////////////////////////////////////////////////////////////////////



/// Derived classes

class LightCar : public Car
{
public:
    LightCar()
    {
        CarSprite.setTexture(CarTexture);
        CarSprite.setScale(0.35f, 0.3f);
        speed = 0.5;
        CarSpeedClock.restart();
    }

    void moveCarBottomToTop() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y -= speed; // Move upward
        CarSprite.setPosition(position);
    }

    void moveCarTopToBottom() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y += speed; // Move downward
        CarSprite.setPosition(position);

    }

    void moveCarLeftToRight() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x += speed; // Move rightward
        CarSprite.setPosition(position);
    }

    void moveCarRightToLeft() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x -= speed; // Move leftward
        CarSprite.setPosition(position);
    }

};


///
class HeavyCar : public Car
{
public:
    HeavyCar()
    {
        CarSprite.setTexture(CarTexture);
        CarSprite.setScale(0.4f, 0.35f);
        speed = 0.3;
        CarSpeedClock.restart();
    }

    void moveCarBottomToTop() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y -= speed; // Move upward
        CarSprite.setPosition(position);
    }

    void moveCarTopToBottom() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y += speed; // Move downward
        CarSprite.setPosition(position);

    }

    void moveCarLeftToRight() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x += speed; // Move rightward
        CarSprite.setPosition(position);
    }

    void moveCarRightToLeft() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x -= speed; // Move leftward
        CarSprite.setPosition(position);
    }

};


///
class SpecialCar : public Car
{
public:

    SpecialCar()
    {
        CarSprite.setTexture(CarTexture);
        CarSprite.setScale(0.15f, 0.15f);
        EV = true;
        speed = 1.1;
        CarSpeedClock.restart();
    }

    void moveCarBottomToTop() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y -= speed; // Move upward
        CarSprite.setPosition(position);
    }

    void moveCarTopToBottom() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.y += speed; // Move downward
        CarSprite.setPosition(position);

    }

    void moveCarLeftToRight() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x += speed; // Move rightward
        CarSprite.setPosition(position);
    }

    void moveCarRightToLeft() override
    {
        sf::Vector2f position = CarSprite.getPosition();
        position.x -= speed; // Move leftward
        CarSprite.setPosition(position);
    }

};





////////////////////////////////////////////////////////////////////////            Cars Related Stuff


//////////////////////              Cars Speed increase after every 5sec

void SpeedIncreaser(Car* carTB[], Car* carBT[], Car* carLR[], Car* carRL[], int& i1, int& i2, int& i3, int& i4)
{
    for (int i = 0; i < i1; i++)
    {
        if (!carTB[i]->OOO && carTB[i]->CarSpeedClock.getElapsedTime().asSeconds() >= 5 && carTB[i]->speed < 0.98)
        {
            carTB[i]->CarSpeedClock.restart();
            carTB[i]->speed += 0.02;
        }
    }

    for (int i = 0; i < i3; i++)
    {
        if (carBT[i]->CarSpeedClock.getElapsedTime().asSeconds() >= 5 && carBT[i]->speed < 0.98)
        {
            carBT[i]->CarSpeedClock.restart();
            carBT[i]->speed += 0.02;
        }
    }

    for (int i = 0; i < i2; i++)
    {
        if (carLR[i]->CarSpeedClock.getElapsedTime().asSeconds() >= 5 && carLR[i]->speed < 0.98)
        {
            carLR[i]->CarSpeedClock.restart();
            carLR[i]->speed += 0.02;
        }
    }

    for (int i = 0; i < i4; i++)
    {
        if (carRL[i]->CarSpeedClock.getElapsedTime().asSeconds() >= 5 && carRL[i]->speed < 0.98)
        {
            carRL[i]->CarSpeedClock.restart();
            carRL[i]->speed += 0.02;
        }
    }
}


//              Car Collision Thing

void Avoid_CollisionTB(Car* carTB[], int& i1, Car* carLR[], Car* carRL[], bool& t1)
{
    for (int i = 0; i < i1; i++)
    {
        if (carTB[i] != NULL)
        {
            // Variables for the current car's bounds
            float currCarRight = carTB[i]->CarSprite.getPosition().x + carTB[i]->CarSprite.getGlobalBounds().width;
            float currCarBottom = carTB[i]->CarSprite.getPosition().y + carTB[i]->CarSprite.getGlobalBounds().height + 20;

            bool collisionDetected = false; // Flag to track collision

            if (i == 0)
            {
                // Check collision with cars in carLR for the first car (carTB[0])
                for (int j = 0; j < 11; j++)
                {
                    if (carLR[j])
                    {
                        float otherCarRight = carLR[j]->CarSprite.getPosition().x + carLR[j]->CarSprite.getGlobalBounds().width;
                        float otherCarBottom = carLR[j]->CarSprite.getPosition().y + carLR[j]->CarSprite.getGlobalBounds().height;

                        if ((carTB[i]->CarSprite.getPosition().x < otherCarRight && currCarRight > carLR[j]->CarSprite.getPosition().x) &&
                            (carTB[i]->CarSprite.getPosition().y < otherCarBottom && currCarBottom > carLR[j]->CarSprite.getPosition().y))
                        {
                            collisionDetected = true;
                            break; // Exit loop if collision detected
                        }
                    }
                }

                // Check collision with cars in carRL for the first car (carTB[0])
                for (int j = 0; j < 10 && !collisionDetected; j++) // Skip if already detected
                {
                    if (carRL[j])
                    {
                        float otherCarRight = carRL[j]->CarSprite.getPosition().x + carRL[j]->CarSprite.getGlobalBounds().width;
                        float otherCarBottom = carRL[j]->CarSprite.getPosition().y + carRL[j]->CarSprite.getGlobalBounds().height;

                        if ((carTB[i]->CarSprite.getPosition().x < otherCarRight && currCarRight > carRL[j]->CarSprite.getPosition().x) &&
                            (carTB[i]->CarSprite.getPosition().y < otherCarBottom && currCarBottom > carRL[j]->CarSprite.getPosition().y))
                        {
                            collisionDetected = true;
                            break; // Exit loop if collision detected
                        }
                    }
                }
            }
            else
            {
                for (int l = i - 1; l >= 0 && !collisionDetected; l--)
                {
                    // Variables for the front car in carTB[i-1]
                    float frontCarRight = carTB[l]->CarSprite.getPosition().x + carTB[l]->CarSprite.getGlobalBounds().width;
                    float frontCarBottom = carTB[l]->CarSprite.getPosition().y + carTB[l]->CarSprite.getGlobalBounds().height;

                    if (carTB[l]->OOO && carTB[i]->EV)
                    {
                        break;
                        }

                    if ((carTB[i]->CarSprite.getPosition().x < frontCarRight && currCarRight > carTB[l]->CarSprite.getPosition().x) &&
                        (carTB[i]->CarSprite.getPosition().y < frontCarBottom && currCarBottom > carTB[l]->CarSprite.getPosition().y))
                    {
                        collisionDetected = true;
                    }
                }

                // Check collision with cars in carLR
                for (int j = 0; j < 10 && !collisionDetected; j++) // Skip if already detected
                {
                    if (carLR[j])
                    {
                        float otherCarRight = carLR[j]->CarSprite.getPosition().x + carLR[j]->CarSprite.getGlobalBounds().width;
                        float otherCarBottom = carLR[j]->CarSprite.getPosition().y + carLR[j]->CarSprite.getGlobalBounds().height;

                        if ((carTB[i]->CarSprite.getPosition().x < otherCarRight && currCarRight > carLR[j]->CarSprite.getPosition().x) &&
                            (carTB[i]->CarSprite.getPosition().y < otherCarBottom && currCarBottom > carLR[j]->CarSprite.getPosition().y))
                        {
                            collisionDetected = true;
                            break; // Exit loop if collision detected
                        }
                    }
                }

                // Check collision with cars in carRL
                for (int j = 0; j < 10 && !collisionDetected; j++) // Skip if already detected
                {
                    if (carRL[j])
                    {
                        float otherCarRight = carRL[j]->CarSprite.getPosition().x + carRL[j]->CarSprite.getGlobalBounds().width;
                        float otherCarBottom = carRL[j]->CarSprite.getPosition().y + carRL[j]->CarSprite.getGlobalBounds().height;

                        if ((carTB[i]->CarSprite.getPosition().x < otherCarRight && currCarRight > carRL[j]->CarSprite.getPosition().x) &&
                            (carTB[i]->CarSprite.getPosition().y < otherCarBottom && currCarBottom > carRL[j]->CarSprite.getPosition().y))
                        {
                            collisionDetected = true;
                            break; // Exit loop if collision detected
                        }
                    }
                }
            }


            //If collision detected, stop the car
            if (!collisionDetected)
            {
                if (t1 || (carTB[i]->CarSprite.getPosition().y + carTB[i]->CarSprite.getGlobalBounds().height) > 390)
                {
                    carTB[i]->moveCarTopToBottom(); // Assume stop() halts the car's movement
                }
                if (!t1 && (carTB[i]->CarSprite.getPosition().y + carTB[i]->CarSprite.getGlobalBounds().height) <= 380)
                {
                    carTB[i]->moveCarTopToBottom(); // Assume stop() halts the car's movement
                }
            }
        }

        //}
    }
}

void Avoid_CollisionLR(Car* carLR[], int& i2, Car* carTB[], Car* carBT[], bool& t3)
{
    for (int i = 0; i < i2; i++)
    {
        if (carLR[i] != NULL)
        {
            // Variables for the current car's bounds (focus on x-axis for left-to-right movement)
            float currCarLeft = carLR[i]->CarSprite.getPosition().x;
            float currCarRight = currCarLeft + carLR[i]->CarSprite.getGlobalBounds().width + 10;
            float currCarTop = carLR[i]->CarSprite.getPosition().y;
            float currCarBottom = currCarTop + carLR[i]->CarSprite.getGlobalBounds().height;

            bool collisionDetected = false; // Flag to track collision

            // Check collision with other cars in carLR (its own array)
            for (int j = 0; j < i2; j++)
            {
                if (j != i && carLR[j])
                {
                    float otherCarLeft = carLR[j]->CarSprite.getPosition().x;
                    float otherCarRight = otherCarLeft + carLR[j]->CarSprite.getGlobalBounds().width;
                    float otherCarTop = carLR[j]->CarSprite.getPosition().y;
                    float otherCarBottom = otherCarTop + carLR[j]->CarSprite.getGlobalBounds().height;

                    if ((currCarRight > otherCarLeft && currCarLeft < otherCarRight) && // Overlap in x-axis
                        (currCarBottom > otherCarTop && currCarTop < otherCarBottom))   // Overlap in y-axis
                    {
                        collisionDetected = true;
                        break; // Exit loop if collision detected
                    }
                }
            }

            // Check collision with cars in carTB
            for (int j = 0; j < 11 && !collisionDetected; j++) // Skip if already detected
            {
                if (carTB[j])
                {
                    float otherCarLeft = carTB[j]->CarSprite.getPosition().x;
                    float otherCarRight = otherCarLeft + carTB[j]->CarSprite.getGlobalBounds().width;
                    float otherCarTop = carTB[j]->CarSprite.getPosition().y;
                    float otherCarBottom = otherCarTop + carTB[j]->CarSprite.getGlobalBounds().height;

                    if ((currCarRight > otherCarLeft && currCarLeft < otherCarRight) && // Overlap in x-axis
                        (currCarBottom > otherCarTop && currCarTop < otherCarBottom))   // Overlap in y-axis
                    {
                        collisionDetected = true;
                        break; // Exit loop if collision detected
                    }
                }
            }

            // Check collision with cars in carBT
            for (int j = 0; j < 10 && !collisionDetected; j++) // Skip if already detected
            {
                if (carBT[j])
                {
                    float otherCarLeft = carBT[j]->CarSprite.getPosition().x;
                    float otherCarRight = otherCarLeft + carBT[j]->CarSprite.getGlobalBounds().width;
                    float otherCarTop = carBT[j]->CarSprite.getPosition().y;
                    float otherCarBottom = otherCarTop + carBT[j]->CarSprite.getGlobalBounds().height;

                    if ((currCarRight > otherCarLeft && currCarLeft < otherCarRight) && // Overlap in x-axis
                        (currCarBottom > otherCarTop && currCarTop < otherCarBottom))   // Overlap in y-axis
                    {
                        collisionDetected = true;
                        break; // Exit loop if collision detected
                    }
                }
            }

            //    If no collision detected, move the car

            if (!collisionDetected)
            {
                if (t3 || currCarRight > 405) // If condition is met, move the car
                {
                    carLR[i]->moveCarLeftToRight(); // Function to move left to right
                }
                if (!t3 && currCarRight <= 390) // If condition is not met
                {
                    carLR[i]->moveCarLeftToRight(); // Function to move left to right
                }
            }
        }
        //}


    }
}

void Avoid_CollisionBT(Car* carBT[], int& i3, Car* carLR[], Car* carBTRL[], bool& t4)
{
    for (int i = 0; i < i3; i++)
    {
        if (carBT[i] != NULL)
        {
            float currCarTop = carBT[i]->CarSprite.getPosition().y - 10;

            bool collisionDetected = false; // Flag for collision detection

            // Check collision with previous cars in carBT
            for (int j = i - 1; j >= 0 && !collisionDetected; j--)
            {
                if (carBT[j] != NULL)
                {
                    float otherCarBottom = carBT[j]->CarSprite.getPosition().y + carBT[j]->CarSprite.getGlobalBounds().height;

                    if ((carBT[i]->CarSprite.getPosition().x < carBT[j]->CarSprite.getPosition().x + carBT[j]->CarSprite.getGlobalBounds().width) &&
                        (carBT[i]->CarSprite.getPosition().x + carBT[i]->CarSprite.getGlobalBounds().width > carBT[j]->CarSprite.getPosition().x) &&
                        (currCarTop < otherCarBottom))
                    {
                        collisionDetected = true;
                    }
                }
            }

            // Check collision with cars in carLR
            for (int j = 0; j < 10 && !collisionDetected; j++)
            {
                if (carLR[j] != NULL)
                {
                    float otherCarBottom = carLR[j]->CarSprite.getPosition().y + carLR[j]->CarSprite.getGlobalBounds().height;

                    if ((carBT[i]->CarSprite.getPosition().x < carLR[j]->CarSprite.getPosition().x + carLR[j]->CarSprite.getGlobalBounds().width) &&
                        (carBT[i]->CarSprite.getPosition().x + carBT[i]->CarSprite.getGlobalBounds().width > carLR[j]->CarSprite.getPosition().x) &&
                        (currCarTop < otherCarBottom))
                    {
                        collisionDetected = true;
                    }
                }
            }

            // Check collision with cars in carBTRL
            for (int j = 0; j < 10 && !collisionDetected; j++)
            {
                if (carBTRL[j] != NULL)
                {
                    float otherCarBottom = carBTRL[j]->CarSprite.getPosition().y + carBTRL[j]->CarSprite.getGlobalBounds().height;

                    if ((carBT[i]->CarSprite.getPosition().x < carBTRL[j]->CarSprite.getPosition().x + carBTRL[j]->CarSprite.getGlobalBounds().width) &&
                        (carBT[i]->CarSprite.getPosition().x + carBT[i]->CarSprite.getGlobalBounds().width > carBTRL[j]->CarSprite.getPosition().x) &&
                        (currCarTop < otherCarBottom))
                    {
                        collisionDetected = true;
                    }
                }
            }


            // If collision is not detected, allow movement
            if (!collisionDetected)
            {
                if (t4 || currCarTop > 676)
                {
                    carBT[i]->moveCarBottomToTop(); // Move upward
                }
                if (!t4 && currCarTop <= 660)
                {
                    carBT[i]->moveCarBottomToTop(); // Continue moving upward
                }
            }
        }
        //}


    }
}

void Avoid_CollisionRL(Car* carRL[], int& i4, Car* carTB[], Car* carBT[], bool& t2)
{
    for (int i = 0; i < i4; i++)
    {
        if (carRL[i] != NULL)
        {
            float currCarLeft = carRL[i]->CarSprite.getPosition().x - 10;
            float currCarRight = currCarLeft + carRL[i]->CarSprite.getGlobalBounds().width;

            bool collisionDetected = false; // Flag for collision detection

            // Check collision with other cars in carRL
            for (int j = i - 1; j >= 0 && !collisionDetected; j--)
            {
                if (carRL[j] != NULL)
                {
                    float otherCarLeft = carRL[j]->CarSprite.getPosition().x;
                    float otherCarRight = otherCarLeft + carRL[j]->CarSprite.getGlobalBounds().width;

                    if ((currCarRight > otherCarLeft && currCarLeft < otherCarRight) && // Horizontal overlap
                        (carRL[i]->CarSprite.getPosition().y < carRL[j]->CarSprite.getPosition().y + carRL[j]->CarSprite.getGlobalBounds().height) &&
                        (carRL[i]->CarSprite.getPosition().y + carRL[i]->CarSprite.getGlobalBounds().height > carRL[j]->CarSprite.getPosition().y))
                    {
                        collisionDetected = true;
                    }
                }
            }

            // Check collision with cars in carTB
            for (int j = 0; j < 11 && !collisionDetected; j++)
            {
                if (carTB[j] != NULL)
                {
                    float otherCarTop = carTB[j]->CarSprite.getPosition().y;
                    float otherCarBottom = otherCarTop + carTB[j]->CarSprite.getGlobalBounds().height;

                    if ((currCarRight > carTB[j]->CarSprite.getPosition().x && currCarLeft < carTB[j]->CarSprite.getPosition().x + carTB[j]->CarSprite.getGlobalBounds().width) &&
                        (carRL[i]->CarSprite.getPosition().y < otherCarBottom && carRL[i]->CarSprite.getPosition().y + carRL[i]->CarSprite.getGlobalBounds().height > otherCarTop))
                    {
                        collisionDetected = true;
                    }
                }
            }

            // Check collision with cars in carBT
            for (int j = 0; j < 10 && !collisionDetected; j++)
            {
                if (carBT[j] != NULL)
                {
                    float otherCarTop = carBT[j]->CarSprite.getPosition().y;
                    float otherCarBottom = otherCarTop + carBT[j]->CarSprite.getGlobalBounds().height;

                    if ((currCarRight > carBT[j]->CarSprite.getPosition().x && currCarLeft < carBT[j]->CarSprite.getPosition().x + carBT[j]->CarSprite.getGlobalBounds().width) &&
                        (carRL[i]->CarSprite.getPosition().y < otherCarBottom && carRL[i]->CarSprite.getPosition().y + carRL[i]->CarSprite.getGlobalBounds().height > otherCarTop))
                    {
                        collisionDetected = true;
                    }
                }
            }


            // If no collision detected, move the car from right to left
            if (!collisionDetected)
            {
                if (t2 || currCarLeft > 668)
                {
                    carRL[i]->moveCarRightToLeft(); // Move leftward
                }
                if (!t2 && currCarLeft <= 650)
                {
                    carRL[i]->moveCarRightToLeft(); // Continue moving leftward
                }
            }
        }
        //}


    }
}





//              Car Allocation Thing

void FuncTB(Car* carTB[], int& i1, bool& LTBP, bool& PeekTime)
{

    srand(time(0));

    // Check for cars that have left the screen
    for (int k = 0; k < 11; k++)
    {
        if (carTB[k] != NULL)
        {

            if (carTB[k]->CarSprite.getPosition().y > 1080)
            {
                delete carTB[k];
                carTB[k] = NULL;
                for (int j = k; j < i1 - 1; j++)
                {
                    carTB[j] = carTB[j + 1];
                }

                carTB[i1 - 1] = nullptr;
                i1--;
                k--;
            }
        }
    }


    if (LaneTB && i1 < 11)
    {
        emergencyVehicleClockTB.restart();

        carTB[i1] = new SpecialCar;

        carTB[i1]->CarTexture.loadFromFile("Accessories/toeTruck3.png");
        carTB[i1]->CarSprite.setTextureRect(sf::IntRect(170, 70, 340 - 170, 508 - 70));
        carTB[i1]->CarSprite.setScale(0.2f, 0.16f);
        carTB[i1]->CarSprite.setPosition(475, -200 * i1);
        carTB[i1]->KamWalaTruck = true;

        // Prevent overlap
        if (i1 > 0 && carTB[i1]->CarSprite.getGlobalBounds().intersects(carTB[i1 - 1]->CarSprite.getGlobalBounds()))
        {
            carTB[i1]->CarSprite.setPosition(418, carTB[i1 - 1]->CarSprite.getPosition().y - 100);
        }

        carTB[i1]->GeneratePlate();

        i1++;
        LaneTB = false;
    }
    else
    {
        // Add a light vehicle every 2 seconds
        if (i1 < 10 && lightVehicleClockTB.getElapsedTime().asSeconds() >= 1.0f)
        {
            lightVehicleClockTB.restart();

            carTB[i1] = new LightCar;
            int pic_choose = (rand() % 6) + 1;

            switch (pic_choose)
            {
            case 1:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(73, 34, 89, 176));
                break;
            case 2:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(227, 213, 94, 173));
                break;
            case 3:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars3.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(346, 282, 82, 174));
                break;
            case 4:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(227, 213, 94, 173));
                break;
            case 5:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars1.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(103, 73, 91, 175));
                break;
            case 6:
                carTB[i1]->CarTexture.loadFromFile("Accessories/cars1.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(416, 72, 85, 169));
                break;
            }

            carTB[i1]->CarSprite.setPosition(420, -60 * i1);

            // Prevent overlap
            if (i1 > 0 && carTB[i1]->CarSprite.getGlobalBounds().intersects(carTB[i1 - 1]->CarSprite.getGlobalBounds()))
            {
                carTB[i1]->CarSprite.setPosition(420, carTB[i1 - 1]->CarSprite.getPosition().y - 100);
            }

            carTB[i1]->GeneratePlate();

            i1++;
        }

        // Add a heavy vehicle (truck) every 5 seconds
        if (i1 < 10 && heavyVehicleClockTB.getElapsedTime().asSeconds() >= 15.0f && !PeekTime)
        {
            heavyVehicleClockTB.restart();

            carTB[i1] = new HeavyCar;
            int pic_choose = (rand() % 5) + 1;

            switch (pic_choose)
            {
            case 1:
                carTB[i1]->CarTexture.loadFromFile("Accessories/trucks2.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(13, 153, 112, 335));
                break;
            case 2:
                carTB[i1]->CarTexture.loadFromFile("Accessories/trucks2.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(135, 152, 109, 336));
                break;
            case 3:
                carTB[i1]->CarTexture.loadFromFile("Accessories/trucks2.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(263, 226, 109, 263));
                break;
            case 4:
                carTB[i1]->CarTexture.loadFromFile("Accessories/trucks2.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(390, 271, 105, 218));
                break;
            case 5:
                carTB[i1]->CarTexture.loadFromFile("Accessories/trucks1.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(18, 16, 118, 477));
                break;
            }

            carTB[i1]->CarSprite.setPosition(470, -180 * i1);

            // Prevent overlap
            if (i1 > 0 && carTB[i1]->CarSprite.getGlobalBounds().intersects(carTB[i1 - 1]->CarSprite.getGlobalBounds()))
            {
                carTB[i1]->CarSprite.setPosition(470, carTB[i1 - 1]->CarSprite.getPosition().y - 100);
            }

            carTB[i1]->GeneratePlate();

            i1++;
        }

        // Add an emergency vehicle every 75 seconds
        if (i1 < 10 && emergencyVehicleClockTB.getElapsedTime().asSeconds() >= 75.0f)
        {
            emergencyVehicleClockTB.restart();

            carTB[i1] = new SpecialCar;

            int pic_choose = rand() % 3 + 1;

            // Emergency vehicle sprite assignments
            if (pic_choose == 1) {
                carTB[i1]->CarTexture.loadFromFile("Accessories/police3.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(131, 53, 205, 483));
                carTB[i1]->CarSprite.setScale(0.17f, 0.15f);
            }
            else if (pic_choose == 2) {
                carTB[i1]->CarTexture.loadFromFile("Accessories/toeTruck3.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(170, 70, 340 - 170, 508 - 70));
                carTB[i1]->CarSprite.setScale(0.2f, 0.16f);
            }
            else if (pic_choose == 3) {
                carTB[i1]->CarTexture.loadFromFile("Accessories/fire2.png");
                carTB[i1]->CarSprite.setTextureRect(sf::IntRect(45, 62, 283 - 45, 726 - 62));
                carTB[i1]->CarSprite.setScale(0.16f, 0.16f);
            }
            carTB[i1]->CarSprite.setPosition(475, -200 * i1);
            LTBP = true;


            // Prevent overlap
            if (i1 > 0 && carTB[i1]->CarSprite.getGlobalBounds().intersects(carTB[i1 - 1]->CarSprite.getGlobalBounds()))
            {
                carTB[i1]->CarSprite.setPosition(418, carTB[i1 - 1]->CarSprite.getPosition().y - 100);
            }

            carTB[i1]->GeneratePlate();

            i1++;
        }
    }
}

void FuncLR(Car* carLR[], int& i2, bool& LLRP, bool& PeekTime)          // Kam movement ka nahi hai iska
{
    // while (true)
     //{
    srand(time(0));

    // Check for cars that have left the screen
    for (int k = 0; k < 10; k++)
    {
        if (carLR[k] != NULL)
        {

            if (carLR[k]->CarSprite.getPosition().x > 1080)
            {
                delete carLR[k];
                carLR[k] = NULL;
                for (int j = k; j < i2 - 1; j++)
                {
                    carLR[j] = carLR[j + 1];
                }

                carLR[i2 - 1] = nullptr;
                i2--;
                k--;
            }
        }
    }

    // Add a light vehicle every 2 seconds
    if (i2 < 10 && lightVehicleClockLR.getElapsedTime().asSeconds() >= 2.0f)
    {
        lightVehicleClockLR.restart();

        carLR[i2] = new LightCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carLR[i2]->CarTexture.loadFromFile("Accessories/cars.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(350, 62, 526 - 350, 145 - 62));
            break;
        case 2:
            carLR[i2]->CarTexture.loadFromFile("Accessories/cars2.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(92, 364, 267 - 92, 449 - 364));
            break;
        case 3:
            carLR[i2]->CarTexture.loadFromFile("Accessories/cars2.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(270, 204, 442 - 270, 292 - 204));
            break;
        case 4:
            carLR[i2]->CarTexture.loadFromFile("Accessories/cars3.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(101, 7, 271 - 101, 89 - 7));
            break;
        case 5:
            carLR[i2]->CarTexture.loadFromFile("Accessories/cars3.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(101, 315, 280 - 101, 403 - 315));
            break;
        }

        carLR[i2]->CarSprite.setScale(0.33f, 0.34f);
        carLR[i2]->CarSprite.setPosition(-60 * 12, 566);

        // Prevent overlap
        if (carLR[i2 - 1] && i2 > 0 && carLR[i2]->CarSprite.getGlobalBounds().intersects(carLR[i2 - 1]->CarSprite.getGlobalBounds()))
        {
            carLR[i2]->CarSprite.setPosition(carLR[i2 - 1]->CarSprite.getPosition().x - 100, 566);
        }

        carLR[i2]->GeneratePlate();

        i2++;
    }

    // Add a heavy vehicle (truck) every 5 seconds
    if (i2 < 10 && heavyVehicleClockLR.getElapsedTime().asSeconds() >= 15.0f && !PeekTime)
    {
        heavyVehicleClockLR.restart();

        carLR[i2] = new HeavyCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carLR[i2]->CarTexture.loadFromFile("Accessories/trucks.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(17, 370, 496 - 17, 479 - 370));
            break;
        case 2:
            carLR[i2]->CarTexture.loadFromFile("Accessories/trucks1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(271, 4, 490 - 271, 110 - 4));
            break;
        case 3:
            carLR[i2]->CarTexture.loadFromFile("Accessories/trucks1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(225, 134, 490 - 225, 238 - 134));
            break;
        case 4:
            carLR[i2]->CarTexture.loadFromFile("Accessories/trucks1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(152, 259, 490 - 152, 364 - 259));
            break;
        case 5:
            carLR[i2]->CarTexture.loadFromFile("Accessories/trucks1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(155, 378, 489 - 155, 485 - 378));
            break;
        }

        carLR[i2]->CarSprite.setPosition(-180 * i2, 619);

        // Prevent overlap
        if (carLR[i2 - 1] && i2 > 0 && carLR[i2]->CarSprite.getGlobalBounds().intersects(carLR[i2 - 1]->CarSprite.getGlobalBounds()))
        {
            carLR[i2]->CarSprite.setPosition(carLR[i2 - 1]->CarSprite.getPosition().x - 100, 619);
        }

        carLR[i2]->GeneratePlate();

        i2++;
    }

    // Add an emergency vehicle every 75 seconds
    if (i2 < 10 && emergencyVehicleClockLR.getElapsedTime().asSeconds() >= 6.67f)
    {
        emergencyVehicleClockLR.restart();

        carLR[i2] = new SpecialCar;

        int pic_choose = rand() % 3 + 1;

        // Emergency vehicle sprite assignments
        if (pic_choose == 1) {
            carLR[i2]->CarTexture.loadFromFile("Accessories/police2.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(62, 93, 541 - 62, 277 - 93));
            carLR[i2]->CarSprite.setScale(0.15f, 0.17f);
        }
        else if (pic_choose == 2) {
            carLR[i2]->CarTexture.loadFromFile("Accessories/toeTruck1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(74, 148, 504 - 74, 300 - 148));
            carLR[i2]->CarSprite.setScale(0.16f, 0.2f);
        }
        else if (pic_choose == 3) {
            carLR[i2]->CarTexture.loadFromFile("Accessories/fire1.png");
            carLR[i2]->CarSprite.setTextureRect(sf::IntRect(65, 57, 723 - 65, 281 - 57));
            carLR[i2]->CarSprite.setScale(0.16f, 0.16f);
        }
        carLR[i2]->CarSprite.setPosition(-200 * i2, 619);
        LLRP = true;


        // Prevent overlap
        if (carLR[i2 - 1] && i2 > 0 && carLR[i2]->CarSprite.getGlobalBounds().intersects(carLR[i2 - 1]->CarSprite.getGlobalBounds()))
        {
            carLR[i2]->CarSprite.setPosition(carLR[i2 - 1]->CarSprite.getPosition().x - 100, 619);
        }

        carLR[i2]->GeneratePlate();

        i2++;
    }
    //}
}

void FuncBT(Car* carBT[], int& i3, bool& LBTP, bool& PeekTime)
{
    //while (true)
    //{
    srand(time(0));

    // Check for cars that have left the screen
    for (int k = 0; k < 10; k++)
    {
        if (carBT[k] != NULL)
        {

            if (carBT[k]->CarSprite.getPosition().y + carBT[k]->CarSprite.getGlobalBounds().height < 0)
            {
                delete carBT[k];
                carBT[k] = NULL;
                for (int j = k; j < i3 - 1; j++)
                {
                    carBT[j] = carBT[j + 1];
                }

                carBT[i3 - 1] = nullptr;
                i3--;
                k--;
            }
        }
    }

    // Add a light vehicle every 2 seconds
    if (i3 < 10 && lightVehicleClockBT.getElapsedTime().asSeconds() >= 2.0f)
    {
        lightVehicleClockBT.restart();

        carBT[i3] = new LightCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carBT[i3]->CarTexture.loadFromFile("Accessories/cars.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(75, 220, 162 - 75, 390 - 220));
            break;
        case 2:
            carBT[i3]->CarTexture.loadFromFile("Accessories/cars.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(381, 212, 473 - 381, 391 - 212));
            break;
        case 3:
            carBT[i3]->CarTexture.loadFromFile("Accessories/cars1.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(253, 74, 347 - 253, 248 - 74));
            break;
        case 4:
            carBT[i3]->CarTexture.loadFromFile("Accessories/cars1.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(415, 250, 501 - 415, 425 - 250));
            break;
        case 5:
            carBT[i3]->CarTexture.loadFromFile("Accessories/cars2.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(118, 0, 205 - 118, 175));
            break;
        }
        carBT[i3]->CarSprite.setPosition(565, 1080 + (60 * i3));
        // Prevent overlap
        if (carBT[i3 - 1] && i3 > 0 && carBT[i3]->CarSprite.getGlobalBounds().intersects(carBT[i3 - 1]->CarSprite.getGlobalBounds()))
        {
            carBT[i3]->CarSprite.setPosition(565, carBT[i3 - 1]->CarSprite.getPosition().y + 100);
        }

        carBT[i3]->GeneratePlate();

        i3++;
    }

    // Add a heavy vehicle (truck) every 5 seconds
    if (i3 < 10 && heavyVehicleClockBT.getElapsedTime().asSeconds() >= 15.0f && !PeekTime)
    {
        heavyVehicleClockBT.restart();

        carBT[i3] = new HeavyCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carBT[i3]->CarTexture.loadFromFile("Accessories/trucks.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(3, 9, 109 - 3, 227 - 9));
            break;
        case 2:
            carBT[i3]->CarTexture.loadFromFile("Accessories/trucks.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(131, 9, 238 - 131, 272 - 9));
            break;
        case 3:
            carBT[i3]->CarTexture.loadFromFile("Accessories/trucks.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(257, 9, 363 - 257, 346 - 9));
            break;
        case 4:
            carBT[i3]->CarTexture.loadFromFile("Accessories/trucks.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(379, 9, 486 - 379, 345 - 9));
            break;
        case 5:
            carBT[i3]->CarTexture.loadFromFile("Accessories/trucks3.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(371, 2, 478 - 371, 481 - 2));
            break;
        }

        carBT[i3]->CarSprite.setPosition(618, 1080 + (180 * i3));

        // Prevent overlap
        if (carBT[i3 - 1] && i3 > 0 && carBT[i3]->CarSprite.getGlobalBounds().intersects(carBT[i3 - 1]->CarSprite.getGlobalBounds()))
        {
            carBT[i3]->CarSprite.setPosition(620, carBT[i3 - 1]->CarSprite.getPosition().y + 100);
        }

        carBT[i3]->GeneratePlate();

        i3++;
    }

    // Add an emergency vehicle every 75 seconds
    if (i3 < 10 && emergencyVehicleClockBT.getElapsedTime().asSeconds() >= 35.0f)
    {
        emergencyVehicleClockBT.restart();

        carBT[i3] = new SpecialCar;

        int pic_choose = rand() % 3 + 1;

        // Emergency vehicle sprite assignments
        if (pic_choose == 1) {
            carBT[i3]->CarTexture.loadFromFile("Accessories/police1.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(88, 60, 275 - 88, 543 - 60));
            carBT[i3]->CarSprite.setScale(0.17f, 0.15f);
        }
        else if (pic_choose == 2) {
            carBT[i3]->CarTexture.loadFromFile("Accessories/toeTruck.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(144, 14, 305 - 144, 444 - 14));
            carBT[i3]->CarSprite.setScale(0.2f, 0.16f);
        }
        else if (pic_choose == 3) {
            carBT[i3]->CarTexture.loadFromFile("Accessories/fire.png");
            carBT[i3]->CarSprite.setTextureRect(sf::IntRect(50, 17, 281 - 50, 684 - 17));
            carBT[i3]->CarSprite.setScale(0.16f, 0.16f);
        }
        carBT[i3]->CarSprite.setPosition(623, 1080 + (200 * i3));
        LBTP = true;


        // Prevent overlap
        if (carBT[i3 - 1] && i3 > 0 && carBT[i3]->CarSprite.getGlobalBounds().intersects(carBT[i3 - 1]->CarSprite.getGlobalBounds()))
        {
            carBT[i3]->CarSprite.setPosition(620, carBT[i3 - 1]->CarSprite.getPosition().y + 100);
        }

        carBT[i3]->GeneratePlate();

        i3++;
    }
    // }
}

void FuncRL(Car* carRL[], int& i4, bool& LRLP, bool& PeekTime)
{
    srand(time(0));

    // Check for cars that have left the screen
    for (int k = 0; k < 10; k++)
    {
        if (carRL[k] != NULL)
        {

            if (carRL[k]->CarSprite.getPosition().x + carRL[k]->CarSprite.getGlobalBounds().width < 0)
            {
                delete carRL[k];
                carRL[k] = NULL;
                for (int j = k; j < i4 - 1; j++)
                {
                    carRL[j] = carRL[j + 1];
                }

                carRL[i4 - 1] = nullptr;
                i4--;
                k--;
            }
        }
    }

    // Add a light vehicle every 2 seconds
    if (i4 < 10 && lightVehicleClockRL.getElapsedTime().asSeconds() >= 1.5f)
    {
        lightVehicleClockRL.restart();

        carRL[i4] = new LightCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carRL[i4]->CarTexture.loadFromFile("Accessories/cars1.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(48, 311, 228 - 48, 401 - 311));
            break;
        case 2:
            carRL[i4]->CarTexture.loadFromFile("Accessories/cars2.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(267, 50, 449 - 267, 142 - 50));
            break;
        case 3:
            carRL[i4]->CarTexture.loadFromFile("Accessories/cars2.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(274, 363, 448 - 274, 450 - 363));
            break;
        case 4:
            carRL[i4]->CarTexture.loadFromFile("Accessories/cars3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(279, 4, 456 - 279, 93 - 4));
            break;
        case 5:
            carRL[i4]->CarTexture.loadFromFile("Accessories/cars3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(102, 157, 278 - 102, 254 - 157));
            break;
        }

        carRL[i4]->CarSprite.setScale(0.33f, 0.34f);
        carRL[i4]->CarSprite.setPosition(1080 + (60 * 12), 418);

        // Prevent overlap
        if (carRL[i4 - 1] && i4 > 0 && carRL[i4]->CarSprite.getGlobalBounds().intersects(carRL[i4 - 1]->CarSprite.getGlobalBounds()))
        {
            carRL[i4]->CarSprite.setPosition(carRL[i4 - 1]->CarSprite.getPosition().x + 100, 418);
        }

        carRL[i4]->GeneratePlate();

        i4++;
    }

    // Add a heavy vehicle (truck) every 5 seconds
    if (i4 < 10 && heavyVehicleClockRL.getElapsedTime().asSeconds() >= 15.0f && !PeekTime)
    {
        heavyVehicleClockRL.restart();

        carRL[i4] = new HeavyCar;
        int pic_choose = (rand() % 5) + 1;

        switch (pic_choose)
        {
        case 1:
            carRL[i4]->CarTexture.loadFromFile("Accessories/trucks2.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(2, 21, 483 - 2, 126 - 21));
            break;
        case 2:
            carRL[i4]->CarTexture.loadFromFile("Accessories/trucks3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(9, 13, 343 - 9, 120 - 13));
            break;
        case 3:
            carRL[i4]->CarTexture.loadFromFile("Accessories/trucks3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(9, 135, 349 - 9, 238 - 135));
            break;
        case 4:
            carRL[i4]->CarTexture.loadFromFile("Accessories/trucks3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(9, 261, 275 - 9, 370 - 261));
            break;
        case 5:
            carRL[i4]->CarTexture.loadFromFile("Accessories/trucks3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(9, 389, 230 - 9, 498 - 389));
            break;
        }

        carRL[i4]->CarSprite.setPosition(1080 + (180 * i4), 473);

        // Prevent overlap
        if (carRL[i4 - 1] && i4 > 0 && carRL[i4]->CarSprite.getGlobalBounds().intersects(carRL[i4 - 1]->CarSprite.getGlobalBounds()))
        {
            carRL[i4]->CarSprite.setPosition(carRL[i4 - 1]->CarSprite.getPosition().x + 100, 473);
        }

        carRL[i4]->GeneratePlate();

        i4++;
    }

    // Add an emergency vehicle every 75 seconds
    if (i4 < 10 && emergencyVehicleClockRL.getElapsedTime().asSeconds() >= 190.0f)
    {
        emergencyVehicleClockRL.restart();

        carRL[i4] = new SpecialCar;

        int pic_choose = rand() % 3 + 1;

        // Emergency vehicle sprite assignments
        if (pic_choose == 1) {
            carRL[i4]->CarTexture.loadFromFile("Accessories/police.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(59, 131, 543 - 59, 331 - 131));
            carRL[i4]->CarSprite.setScale(0.15f, 0.17f);
        }
        else if (pic_choose == 2) {
            carRL[i4]->CarTexture.loadFromFile("Accessories/toeTruck2.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(14, 175, 444 - 14, 337 - 175));
            carRL[i4]->CarSprite.setScale(0.16f, 0.2f);
        }
        else if (pic_choose == 3) {
            carRL[i4]->CarTexture.loadFromFile("Accessories/fire3.png");
            carRL[i4]->CarSprite.setTextureRect(sf::IntRect(17, 51, 681 - 17, 284 - 51));
            carRL[i4]->CarSprite.setScale(0.16f, 0.16f);
        }
        carRL[i4]->CarSprite.setPosition(1080 + (200 * i4), 473);
        LRLP = true;


        // Prevent overlap
        if (carRL[i4 - 1] && i4 > 0 && carRL[i4]->CarSprite.getGlobalBounds().intersects(carRL[i4 - 1]->CarSprite.getGlobalBounds()))
        {
            carRL[i4]->CarSprite.setPosition(carRL[i4 - 1]->CarSprite.getPosition().x + 100, 473);
        }

        carRL[i4]->GeneratePlate();

        i4++;
    }
    //}
}


////////////////////////////////////////////        Some Car Out of Order


void OOOO(Car* carTB[], Car* carBT[], Car* carLR[], Car* carRL[], int& i1, int& i2, int& i3, int& i4, bool& OutDone)
{

    srand(time(0));

    int random1 = rand() % i1;

    if (!(carTB[random1]->EV == true || carTB[random1]->CarSprite.getPosition().y < 500))
    {
        carTB[random1]->speed = 0; OutDone = true;
        carTB[random1]->OOO = true;
        //
         cout << "Car Detected : CarTB" << endl;
    }
}


//////////////////////////////////////////////              Car Drawing

void CarDrawing(Car* carTB[], Car* carBT[], Car* carLR[], Car* carRL[], sf::RenderWindow& window, int& i1, int& i2, int& i3, int& i4)
{

    for (int i = 0; i < i1; i++)
    {
        if (carTB[i])
        {
            window.draw(carTB[i]->CarSprite);
        }
    }

    for (int i = 0; i < i2; i++)
    {
        if (carLR[i])
        {
            window.draw(carLR[i]->CarSprite);
        }
    }

    for (int i = 0; i < i3; i++)
    {
        if (carBT[i])
        {
            window.draw(carBT[i]->CarSprite);
        }
    }

    for (int i = 0; i < i4; i++)
    {
        if (carRL[i])
        {
            window.draw(carRL[i]->CarSprite);
        }
    }
}


/////////////////////////////////////////////               Toe Truck bulao, sala kharab gari ki waja se traffic jam ho raha

void CarKharabEVCall(Car* carTB[], Car* carBT[], Car* carLR[], Car* carRL[], int& i1, int& i2, int& i3, int& i4)
{
    for (int i = 0; i < i1; i++)
    {
        if (carTB[i]->speed == 0)
        {
            LaneTB = true;
            return;
        }
    }

}


/////////////////////////////////////////////                   Kharab gari kheench kr ja raha

void ToeingTheOldOne(Car* carTB[], int& i1)
{
    for (int i = 0; i < i1; i++)
    {
        if (carTB[i] && carTB[i]->KamWalaTruck)
        {
            for (int j = 0; j < i1; j++)
            {
                if (carTB[j] && carTB[j]->OOO)
                {
                    if (carTB[i]->CarSprite.getPosition().y >= carTB[j]->CarSprite.getPosition().y)
                    {
                        carTB[j]->CarSprite.setPosition(carTB[i]->CarSprite.getPosition().x, carTB[i]->CarSprite.getPosition().y);
                    }
                }
            }
        }
    }
}


////////////////////////////////////////////                    Random Time pr gari ki speed increase kre ga

void Random_Speed_Increase(Car* carTB[], Car* carLR[], Car* carBT[], Car* carRL[], int& timer, int& Cdafa, bool& t1, bool& t2, bool& t3, bool& t4, HANDLE& hPipe)
{
    static bool tt1 = true, tt2 = false, tt3 = false, tt4 = false;
    srand(time(0));

    if (ChallanClock.getElapsedTime().asSeconds() >= timer)
    {
        if (t1 && tt1)
        {
            if (carTB[0] && !carTB[0]->EV)
            {
                int yy = carTB[0]->CarSprite.getPosition().y;
                carTB[0]->speed = 1;
                timer += rand() % 80 + 1;
                Cdafa++;
                //cout << "\nLaneTB car speeded !\n" << endl;
                tt1 = false;
                tt2 = true;

                PipeTransfer(carTB[0]->LicensePlate, hPipe);
            }

        }
        else if (t3 && tt2)
        {
            if (carLR[0] && !carLR[0]->EV)
            {
                int yy = carLR[0]->CarSprite.getPosition().x;
                carLR[0]->speed = 1;
                timer += rand() % 80 + 1;
                Cdafa++;
                //cout << "\nLaneLR car speeded !\n" << endl;
                tt2 = false;
                tt3 = true;
                PipeTransfer(carLR[0]->LicensePlate, hPipe);
            }
        }
        else if (t4 && tt3)
        {
            if (carBT[0] && !carBT[0]->EV)
            {
                int yy = carBT[0]->CarSprite.getPosition().y;
                carBT[0]->speed = 1;
                timer += rand() % 80 + 1;
                Cdafa++;
                //cout << "\nLaneBT car speeded !\n" << endl;
                tt3 = false;
                tt4 = true;
                PipeTransfer(carBT[0]->LicensePlate, hPipe);
            }
        }
        else if (t2 && tt4)
        {
            if (carRL[0] && !carRL[0]->EV)
            {
                int yy = carRL[0]->CarSprite.getPosition().x;
                carRL[0]->speed = 1;
                timer += rand() % 80 + 1;
                Cdafa++;
                //cout << "\nLaneRL car speeded !\n" << endl;
            }
            tt4 = false;
            tt1 = true;
            PipeTransfer(carRL[0]->LicensePlate, hPipe);
        }
    }

}


/////////////////////////////////////////                       Challan Data Transfer wala scene

void PipeTransfer(const std::string& Plate, HANDLE& hPipe)
{

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Invalid pipe handle." << std::endl;
        return;
    }

    // Dynamically allocate a char array to hold the string
    char* message = new char[8]; // +1 for null terminator

    // Copy the contents of the string into the char array
    for (size_t i = 0; i < 7; ++i) {
        message[i] = Plate[i];
    }

    message[7] = '\0';

    DWORD bytesWritten;

    // Write data to the pipe
    BOOL success = WriteFile(
        hPipe,                  // Handle to the pipe
        message,                // Data to send
        static_cast<DWORD>(8), // Size of the data
        &bytesWritten,          // Number of bytes written
        NULL                    // No overlapping
    );

    if (!success) {
        //std::cerr << "Failed to write to the pipe. Error: " << GetLastError() << std::endl;
    }
    else {
        //std::cout << "Message sent successfully: " << message << std::endl;
    }

    // Free dynamically allocated memory
    delete[] message;
}


/////////////////////////////////////////                           EV Priority Wala scene

void EVPriority(Car* carTB[], Car* carBT[], Car* carLR[], Car* carRL[], int& i1, int& i2, int& i3, int& i4, bool& LaneTBP, bool& LaneBTP, bool& LaneLRP, bool& LaneRLP, bool& t1, bool& t2, bool& t3, bool& t4, Traffic_Signal* Signal)
{
    Car* CARTB = nullptr, * CARBT = nullptr, * CARLR = nullptr, * CARRL = nullptr;

    if (LaneTBP == true)
    {
        for (int i = 0; i < i1; i++)
        {
            if (carTB[i]->EV)
            {
                CARTB = carTB[i];
                break;
            }
        }
    }

    if (LaneBTP == true)
    {
        for (int i = 0; i < i3; i++)
        {
            if (carBT[i]->EV)
            {
                CARBT = carBT[i];
                break;
            }
        }
    }

    if (LaneLRP == true)
    {
        for (int i = 0; i < i2; i++)
        {
            if (carLR[i]->EV)
            {
                CARLR = carLR[i];
                break;
            }
        }
    }

    if (LaneRLP == true)
    {
        for (int i = 0; i < i4; i++)
        {
            if (carRL[i]->EV)
            {
                CARRL = carRL[i];
                break;
            }
        }
    }


    /////////////////////////////////////////////////////////////



    if (LaneTBP && CARTB && CARTB->CarSprite.getPosition().y > 120 && CARTB->CarSprite.getPosition().y < 390 && !t1)
    {
        Signal[0].green.setOutlineColor(sf::Color::Green);
        bool b = true;


        Avoid_CollisionTB(carTB, i1, carLR, carRL, b);
        AvoidTB = true;

        if (CARTB->CarSprite.getPosition().y > 1080)
        {
            LaneTBP = false;
        }
    }
    else
    {
        AvoidTB = false;
    }

    if (CARTB && CARTB->CarSprite.getPosition().y > 400 && !t1)
    {
        Signal[0].green.setOutlineColor(sf::Color(64, 64, 64));
    }

    ///////////////////////////////////////////////////////////////////////     Lane Top to Bottom k liye Ended



    if (LaneBTP && CARBT && CARBT->CarSprite.getPosition().y < 880 && CARBT->CarSprite.getPosition().y > 666 && !t4)
    {
        Signal[3].green.setOutlineColor(sf::Color::Green);
        bool b = true;


        Avoid_CollisionBT(carBT, i3, carLR, carRL, b);
        AvoidBT = true;

        if (CARBT->CarSprite.getPosition().y < 0)
        {
            LaneBTP = false;
        }
    }
    else
    {
        AvoidBT = false;
    }

    if (CARBT && CARBT->CarSprite.getPosition().y < 666 && !t4)
    {
        Signal[3].green.setOutlineColor(sf::Color(64, 64, 64));
    }

    ///////////////////////////////////////////////////////////////////////     Lane Bottom to Top k liye Ended



    if (LaneRLP && CARRL && CARRL->CarSprite.getPosition().x < 880 && CARRL->CarSprite.getPosition().x > 658 && !t2)
    {
        Signal[1].green.setOutlineColor(sf::Color::Blue);
        bool b = true;


        Avoid_CollisionRL(carRL, i4, carTB, carBT, b);
        AvoidRL = true;

        if (CARRL->CarSprite.getPosition().y < 0)
        {
            LaneRLP = false;
        }
    }
    else
    {
        AvoidRL = false;
    }

    if (CARRL && CARRL->CarSprite.getPosition().x < 658 && !t2)
    {
        Signal[1].green.setOutlineColor(sf::Color(64, 64, 64));
    }

    ///////////////////////////////////////////////////////////////////////     Lane Right to Left k liye Ended




    if (LaneLRP && CARLR && CARLR->CarSprite.getPosition().x > 120 && CARLR->CarSprite.getPosition().x < 415 && !t3)
    {
        Signal[2].green.setOutlineColor(sf::Color::Blue);
        bool b = true;


        Avoid_CollisionLR(carLR, i2, carTB, carBT, b);
        AvoidLR = true;

        if (CARLR->CarSprite.getPosition().y > 1080)
        {
            LaneLRP = false;
        }
    }
    else
    {
        AvoidLR = false;
    }

    if (CARLR && CARLR->CarSprite.getPosition().x > 415 && !t3)
    {
        Signal[2].green.setOutlineColor(sf::Color(64, 64, 64));
    }

    ///////////////////////////////////////////////////////////////////////     Lane Right to Left k liye Ended

}
