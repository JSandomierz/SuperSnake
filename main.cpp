#include <math.h>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "CFrameCounter.hpp"
#include "Snake.hpp"
#include "CText.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "Network.hpp"

using namespace std;

bool collideCircles();

int main()
{
    const int antialiasing=4;
    sf::RenderWindow window(sf::VideoMode(800, 600),"Super Snake",sf::Style::Titlebar|sf::Style::Close,sf::ContextSettings(0,0,antialiasing,2,0));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    bool run=true;
    bool menu=true;
    bool isServer=false;
    bool isClient=false;
    CFrameCounter fps;
    CText board,pointsBoard;
    Game game(&run,&menu, &window);
    Client client;

    board.setPosition(10,10);
    pointsBoard.setPosition(10,570);

    while (window.isOpen() && run)
    {
        sf::Event event;

        board.setString(board.intToString(fps.frames_old));
        game.fps=fps.frames_old;
        pointsBoard.setString(pointsBoard.intToString(game.s[0]->score));
        window.clear();
        if(menu)
        {
            while (window.pollEvent(event)) game.processMenuEvents(event, &isServer, &isClient);
            for(int i=0;i<game.mainMenu.buttons.size();i++)
            {
                window.draw(game.mainMenu.buttons.at(i).body);
                window.draw(game.mainMenu.buttons.at(i).text);
            }
            game.mainMenu.scaleButtons();
        }
        else
        {
            if(isServer)
            {
                Server server;
                cout << "server created\n";
                while(true)
                {
                    while (window.pollEvent(event))
                    {
                        if(event.type==sf::Event::Closed) window.close();
                    }
                    server.mainActivity(game);
                    cout <<fps.frames<<endl;
                }
            }
            else
            {
                while(window.pollEvent(event)) game.processEvents(event);
                if(isClient)
                {
                    if(!client.connected)
                    {
                        if(client.connect(game,"127.0.0.1")) client.connected=true;
                        else
                        {
                            isClient=false;
                            menu=true;
                        }
                    }

                    while(window.pollEvent(event)) game.processEvents(event);
                    client.updateSnakes(game);
                }
                else
                {
                    game.processMovement();
                }
                window.draw(game.food);
                for(short i=0;i<4;i++)
                {
                    //if(game.s[i]->active)
                    for(int j=0;j<game.s[i]->snakeDeque.size();j++) window.draw(game.s[i]->snakeDeque.at(j));
                }
                window.draw(board);
                window.draw(pointsBoard);
            }
        }
        window.display();
        fps.count();
    }
    return 0;
}


