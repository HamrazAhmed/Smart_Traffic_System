#pragma once
#include<thread>
#include<time.h>
#include<mutex>
#include<chrono>
#include"Cars.h"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include <windows.h>

std::mutex mtx;
const wchar_t* pipeName = L"\\\\.\\pipe\\challan_pipe";


void Traffic_Change(int& turn, Traffic_Signal*& Signal)
{
    while (Main_Clock.getElapsedTime().asSeconds() < 300)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (turn == 4)                                                  //      Lane 1 Time
        {
            Signal[0].red.setOutlineColor(sf::Color(64, 64, 64));
            Signal[0].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[0].green.setOutlineColor(sf::Color::Green);


            Signal[3].red.setOutlineColor(sf::Color::Red);
            Signal[3].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[3].green.setOutlineColor(sf::Color(64, 64, 64));

        }
        else if (turn == 1)                                                  //      Lane 2 Time
        {
            Signal[1].red.setOutlineColor(sf::Color(64, 64, 64));
            Signal[1].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[1].green.setOutlineColor(sf::Color::Green);


            Signal[0].red.setOutlineColor(sf::Color::Red);
            Signal[0].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[0].green.setOutlineColor(sf::Color(64, 64, 64));

        }
        else if (turn == 2)                                                  //      Lane 3 Time
        {
            Signal[2].red.setOutlineColor(sf::Color(64, 64, 64));
            Signal[2].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[2].green.setOutlineColor(sf::Color::Green);


            Signal[1].red.setOutlineColor(sf::Color::Red);
            Signal[1].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[1].green.setOutlineColor(sf::Color(64, 64, 64));

        }
        else if (turn == 3)                                                  //      Lane 4 Time
        {
            Signal[3].red.setOutlineColor(sf::Color(64, 64, 64));
            Signal[3].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[3].green.setOutlineColor(sf::Color::Green);


            Signal[2].red.setOutlineColor(sf::Color::Red);
            Signal[2].yellow.setOutlineColor(sf::Color(64, 64, 64));
            Signal[2].green.setOutlineColor(sf::Color(64, 64, 64));

        }
    }
}

class TrafSim
{

    Traffic_Signal* Signal;
    Car* carTB[11], * carBT[10], * carLR[10], * carRL[10]; int i1, i2, i3, i4;
    HANDLE hPipe;
    bool PeekTime = false;

    // Load font
    sf::Font font;

    // Heading text: Cars Challan List
    sf::Text PeekTimeText;

public:

    TrafSim()
    {
        Signal = new Traffic_Signal[4];

        for (int i = 0; i < 11; i++)
        {
            carTB[i] = NULL;
            carBT[i] = NULL;
            carLR[i] = NULL;
            carRL[i] = NULL;
        }

        i1 = i2 = i3 = i4 = 0;



        hPipe = CreateNamedPipe(
            pipeName,               // Name of the pipe
            PIPE_ACCESS_OUTBOUND,   // Write-only access
            PIPE_TYPE_MESSAGE |     // Message-type pipe
            PIPE_READMODE_MESSAGE | // Message read mode
            PIPE_WAIT,              // Blocking mode
            1,                      // Max instances
            512,                    // Output buffer size
            0,                      // Input buffer size (not needed for write-only)
            0,                      // Default timeout
            NULL                    // Default security attributes
        );

        if (hPipe == INVALID_HANDLE_VALUE) {
            //std::cerr << "Failed to create named pipe. Error: " << GetLastError() << std::endl;
            return;
        }

        if (!font.loadFromFile("C:/Users/Salman Ahmed/Documents/SFML/Accessories/DIGI.ttf")) { // Replace with your font path
            std::cerr << "Error loading font!" << std::endl;
            return;
        }

    }

    /// <summary>
    /// ------------------------------------Main Kam to ab shuru hua hai-------------------------------
    /// </summary>

    void start()
    {
        Main_Clock.restart();                           ///     5 min timer started

        srand(time(0));
        int turn;

        int RunOutTime = rand() % 250 + 1; bool OutDone = false; bool eikdafa = false;
        int ChallanTime = rand() % 40 + 10; int Cdafa = 0;
        bool LaneTBP = 0, LaneLRP = 0, LaneBTP = 0, LaneRLP = 0;


        sf::RenderWindow window(sf::VideoMode(1080, 1050), "Smart Traffic");

        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("Accessories/map.png");

        sf::Sprite backgroundSprite;
        backgroundSprite.setTexture(backgroundTexture);

        ////        Peek Time Ki properties set kr raha tha

        {
            PeekTimeText.setFont(font);
            PeekTimeText.setCharacterSize(40);
            PeekTimeText.setFillColor(sf::Color::White);
            PeekTimeText.setStyle(sf::Text::Bold);
            PeekTimeText.setPosition(800, 20.0f);
        }                           


        //////////////////
        sf::Clock clock;
        bool t1 = 1, t2 = 0, t3 = 0, t4 = 0;
        //////////////////

                                                                        // Image fitting
        float scaleX = static_cast<float>(1080) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(1080) / backgroundTexture.getSize().y;

        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setPosition(0, 0);

        ///////
        {
            Signal[1].red.setPosition(863.5, 236);
            Signal[1].yellow.setPosition(863.5, 256);
            Signal[1].green.setPosition(863.5, 276);

            Signal[2].red.setPosition(193.5, 705);
            Signal[2].yellow.setPosition(193.5, 725);
            Signal[2].green.setPosition(193.5, 745);

            Signal[3].red.setPosition(714, 805);
            Signal[3].yellow.setPosition(714, 825);
            Signal[3].green.setPosition(714, 845);
        }
        ///////
        std::thread trafficThread(Traffic_Change, std::ref(turn), std::ref(Signal));
        std::thread PeekTimeThread(PeekHrsTiming, std::ref(window), std::ref(PeekTime), std::ref(Main_Clock), std::ref(PeekTimeText));


        // Main loop
        clock.restart();


        while (Main_Clock.getElapsedTime().asSeconds() < 300)
        {
            sf::Event event;

            SpeedIncreaser(carTB, carBT, carLR, carRL, i1, i2, i3, i4);

            turn = isOPEN(clock, t1, t2, t3, t4, Signal);

            ////////////////#####################################################################
            FuncTB(carTB, i1, LaneTBP, PeekTime);
            FuncLR(carLR, i2, LaneLRP, PeekTime);
            FuncBT(carBT, i3, LaneBTP, PeekTime);
            FuncRL(carRL, i4, LaneRLP, PeekTime);
            ////////////////#####################################################################


            /////////////////////////////////////////      Jab band krna hoga
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // Clear the window
            window.clear();

            // Draw the background
            window.draw(backgroundSprite);



            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (AvoidTB == false)
            {
                Avoid_CollisionTB(carTB, i1, carLR, carRL, t1);
            }

            if (AvoidLR == false)
            {
                Avoid_CollisionLR(carLR, i2, carTB, carBT, t3);
            }

            if (AvoidBT == false)
            {
                Avoid_CollisionBT(carBT, i3, carLR, carRL, t4);
            }

            if (AvoidRL == false)
            {
                Avoid_CollisionRL(carRL, i4, carTB, carBT, t2);
            }
            /////``````````````````````000000000000000098765432345678965423456789865432345678986543234567890987654323456789987654323456789876543

            if (Main_Clock.getElapsedTime().asSeconds() >= RunOutTime && !OutDone)      // Thread ban skta hai
            {
                OOOO(carTB, carBT, carLR, carRL, i1, i2, i3, i4, OutDone);
            }

            if (eikdafa == false && OutDone == true)
            {
                CarKharabEVCall(carTB, carBT, carLR, carRL, i1, i2, i3, i4);                // Kharab gari ne call kr di hai Truck ko, jld hi aa jaye ga
                eikdafa = true;
            }


            ToeingTheOldOne(carTB, i1);                                  //   Gari ko apne oopr dal kr le ke ja raha

            if (Cdafa < 4)
                Random_Speed_Increase(carTB, carBT, carLR, carRL, ChallanTime, Cdafa, t1, t2, t3, t4, hPipe);


            ///////////////////////////////////////////////////////////////////////////////////

            EVPriority(carTB, carBT, carLR, carRL, i1, i2, i3, i4, LaneTBP, LaneBTP, LaneLRP, LaneRLP, t1, t2, t3, t4, Signal);

            ///////////////////////////////////////////////////////////////////////////////////


            //////////////////////////////////////////////////////////////////////////////////      Almost cheezein draw wala scene hai

            for (int i = 0; i < 4; i++)
            {
                window.draw(Signal[i].red);
                window.draw(Signal[i].yellow);
                window.draw(Signal[i].green);
            }

            CarDrawing(carTB, carBT, carLR, carRL, window, i1, i2, i3, i4);

            for (int i = 0; i < 11;i++)
            {
                if (carTB[i] && carTB[i]->OOO)
                {
                    window.draw(carTB[i]->CarSprite);
                }
            }
            window.draw(PeekTimeText);

            // Display the content
            window.display();
        }

        trafficThread.join();
        PeekTimeThread.join();
    }

    ///////////////////////////////         Some Other Functions





    int isOPEN(sf::Clock& clock, bool& t1, bool& t2, bool& t3, bool& t4, Traffic_Signal*& Signal)
    {
        std::lock_guard<std::mutex> lock(mtx);

        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 10 && t1)
        {
            cout << "Lane 1 timing ended!" << endl;
            t1 = 0; t2 = 1;
            clock.restart();
            return 1;
        }
        else if (elapsed.asSeconds() >= 10 && t2)
        {
            cout << "Lane 2 timing ended!" << endl;
            t2 = 0; t3 = 1;
            clock.restart();
            return 2;
        }
        else if (elapsed.asSeconds() >= 10 && t3)
        {
            cout << "Lane 3 timing ended!" << endl;
            t3 = 0; t4 = 1;
            clock.restart();
            return 3;
        }
        else if (elapsed.asSeconds() >= 10 && t4)
        {
            cout << "Lane 4 timing ended!" << endl;
            t4 = 0; t1 = 1;
            clock.restart();
            return 4;
        }

        ///////////////

        if (elapsed.asSeconds() >= 8 && elapsed.asSeconds() <= 10 && t4)
        {
            Signal[0].yellow.setOutlineColor(sf::Color::Yellow);
        }
        else if (elapsed.asSeconds() >= 8 && elapsed.asSeconds() <= 10 && t1)
        {
            Signal[1].yellow.setOutlineColor(sf::Color::Yellow);
        }
        else if (elapsed.asSeconds() >= 8 && elapsed.asSeconds() <= 10 && t2)
        {
            Signal[2].yellow.setOutlineColor(sf::Color::Yellow);
        }
        else if (elapsed.asSeconds() >= 8 && elapsed.asSeconds() <= 10 && t3)
        {
            Signal[3].yellow.setOutlineColor(sf::Color::Yellow);
        }
    }

};