#include <math.h>
#include <SFML/Graphics.hpp>
#include <deque>
#include "CFrameCounter.hpp"
using namespace std;

bool collideCircles();

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600),"testing",sf::Style::Default,sf::ContextSettings(0,0,4,2,0));
    bool run=true;
    bool set=false;
    window.setFramerateLimit(50);
    sf::VertexArray a;
    std::deque<sf::CircleShape> sv;
    bool add=false,go=true;
    bool left=false,right=false;
    sf::Vector2f pos;
    float angle=0;
    float speed=2.5;
    float radius=10;
    float radiusC=10;
    sf::CircleShape tmp(radius,1000);
    tmp.setPosition(400,300);
    sv.push_back(tmp);
    CFrameCounter fps;
    while (window.isOpen() && run)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed)
            {
                //if(event.key.code==sf::Keyboard::Escape) run=false;

            }

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code==sf::Keyboard::A)
                {
                    left=true;
                    //cout <<angle<<"\n";
                }
                if(event.key.code==sf::Keyboard::D)
                {
                    right=true;
                }
                if(event.key.code==sf::Keyboard::Add)
                {
                    radius+=radiusC;
                    sf::Vector2f pos=sv.at(sv.size()-1).getPosition();
                    //tmp.setRotation(angle);
                    float tmpangle=angle*2*3.14/360-90;
                    tmp.setRadius(radius);
                    tmp.move(sf::Vector2f(sin(tmpangle)*radiusC,cos(tmpangle)*radiusC));

                }
            }
            if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code==sf::Keyboard::A)
                {
                    left=false;
                    //cout <<angle<<"\n";
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
                    //angle=0;
                    add=true;
                    /*if(add)
                    {
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
                    sv.clear();
                    float x,y;
                    sf::Mouse mouse;
                    pos=(sf::Vector2f)mouse.getPosition(window);
                    tmp.setPosition(pos);
                    tmp.setFillColor(sf::Color::White);
                    tmp.setRadius(10);
                    radius=10;
                    angle=0;
                    sv.push_back(tmp);
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
        if(left) angle+=5;
        if(right) angle-=5;
        if(add)
        {
            tmp.setFillColor(sf::Color::Red);
            sf::Vector2f pos=sv.at(sv.size()-1).getPosition();
            //tmp.setRotation(angle);
            float tmpangle=angle*2*3.14/360;
            tmp.move(sf::Vector2f(sin(tmpangle)*speed,cos(tmpangle)*speed));
            sv.push_back(tmp);
        }
        //if(sv.size()>400) sv.pop_front();
        window.clear();
        //cout <<sv.size()<<endl;
        for(int i=0;i<sv.size();i++) window.draw(sv.at(i));
        window.display();
        fps.count();
    }
    return 0;
}


