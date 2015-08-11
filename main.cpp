#include <math.h>
#include <SFML/Graphics.hpp>
#include "CFrameCounter.hpp"
#include "Snake.hpp"
#include "CText.hpp"
using namespace std;

bool collideCircles();

int main()
{
    const int antialiasing=4;
    sf::RenderWindow window(sf::VideoMode(800, 600),"testing",sf::Style::Default,sf::ContextSettings(0,0,antialiasing,2,0));
    window.setFramerateLimit(50);

    bool run=true;

    bool add=false,go=true;
    bool left=false,right=false;
    sf::Vector2f pos;
    CFrameCounter fps;
    CText board;
    board.setPosition(10,10);
    Snake s;
    while (window.isOpen() && run)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::Escape) run=false;
            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::A)
                {
                    left=true;
                }
                if(event.key.code==sf::Keyboard::D)
                {
                    right=true;
                }
                if(event.key.code==sf::Keyboard::Add)
                {

                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::A)
                {
                    left=false;
                }
                if(event.key.code==sf::Keyboard::D)
                {
                    right=false;
                }
                //if(event.key.code==sf::Keyboard::A) cout << "a released\n";
            }
            if(event.type==sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    add=true;//start
                    /*{
                        float x,y;
                        sf::Mouse mouse;
                        pos=(sf::Vector2f)mouse.getPosition(window);
                        tmp.setPosition(pos);
                        tmp.setFillColor(sf::Color::White);
                        sv.push_back(tmp);
                    }*/
                }
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                    /*sv.clear();
                    float x,y;
                    sf::Mouse mouse;
                    pos=(sf::Vector2f)mouse.getPosition(window);
                    tmp.setPosition(pos);
                    tmp.setFillColor(sf::Color::White);
                    tmp.setRadius(10);
                    radius=10;
                    angle=0;
                    sv.push_back(tmp);
                    */
                    s.reset();
                }
            }
            if(event.type==sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {

                }
                if(event.mouseButton.button == sf::Mouse::Right)
                {
                }
            }
        }
        //sterowanie
        if(left) s.angle+=5;
        if(right) s.angle-=5;
        if(add)
        {
            s.addPiece();
        }
        board.setString(board.floatToString(fps.frames_old));
        window.clear();
        //cout <<s.snakeDeque.size()<<endl;
        for(int i=0;i<s.snakeDeque.size();i++) window.draw(s.snakeDeque.at(i));
        window.draw(board);
        window.display();
        fps.count();
    }
    return 0;
}


