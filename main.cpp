#include <math.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "FileOperator.hpp"
#include "CFrameCounter.hpp"
#include "Snake.hpp"
#include "CText.hpp"
#include "GUI.hpp"
#include "Game.hpp"
#include "Network.hpp"

using namespace std;

int main()
{
    int antialiasing=4,windowWidth=800,windowHeight=600;
    float speed=1.f;
    unsigned int hiScore=0;
    sf::Uint32 style;

    FileOperator fileOp;
    fileOp.loadConfig(antialiasing,windowWidth,windowHeight,style,speed);
    hiScore=fileOp.readBestScore();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),"Super Snake",style,sf::ContextSettings(0,0,antialiasing,2,0));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    bool run=true;
    bool menu=true;
    CFrameCounter fps;
    CText board,pointsBoard1,pointsBoard2,hiScoreBoard;
    Game game(&run,&menu, &window, speed);

    board.setPosition(10,10);
    pointsBoard1.setPosition(10,window.getSize().y-40);
    pointsBoard2.setPosition(window.getSize().x-200,window.getSize().y-40);
    hiScoreBoard.setPosition(window.getSize().x-200,10);

    while (window.isOpen() && run)
    {
        sf::Event event;

        board.setString(board.intToString(fps.frames_old));
        game.fps=fps.frames_old;
        pointsBoard1.setString("player 1 "+pointsBoard1.intToString(game.s[0]->score));
        pointsBoard2.setString("player 2 "+pointsBoard2.intToString(game.s[2]->score));
        hiScoreBoard.setString("hiscore "+pointsBoard2.intToString(hiScore));
        window.clear();
        if(menu)
        {
            while (window.pollEvent(event)) game.processMenuEvents(event);
            for(int i=0;i<game.mainMenu.buttons.size();i++){
                window.draw(game.mainMenu.buttons.at(i).body);
                window.draw(game.mainMenu.buttons.at(i).text);
            }
            game.mainMenu.scaleButtons();
        }else{
                while(window.pollEvent(event)) game.processEvents(event);
                game.processMovement(hiScore);

                window.draw(game.food);
                for(short i=0;i<4;i++){
                    if(game.s[i]->active) for(int j=0;j<game.s[i]->snakeDeque.size();j++) window.draw(game.s[i]->snakeDeque.at(j));
                }
                window.draw(board);
                window.draw(pointsBoard1);

                if(game.s[2]->active) window.draw(pointsBoard2);
                else window.draw(hiScoreBoard);


        }
        window.display();
        fps.count();
    }
    return 0;
}


