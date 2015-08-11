#ifndef Snake_HPP_INCLUDED
#define Snake_HPP_INCLUDED
#include <deque>
using namespace std;

class Snake
{
public:
std::deque<sf::CircleShape> snakeDeque;
float angle=0;
float speed=2.5;
float radius=10;
float radiusChange=1;
unsigned int limit=200;

    Snake():tmp(radius,1000)
    {
        tmp.setPosition(400,300);
        snakeDeque.push_back(tmp);
    }
    void resizeSnake(bool increase)
    {
        if(!increase)
        {
            if((radius-radiusChange)>0) radius-=radiusChange;
        }
        else radius+=radiusChange;
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        //tmp.setRotation(angle);
        float tmpangle=angle*2*3.14/360-90;
        tmp.setRadius(radius);
        tmp.move(sf::Vector2f(sin(tmpangle)*radiusChange,cos(tmpangle)*radiusChange));
    }
    void addPiece()
    {
        if(snakeDeque.size()>limit) snakeDeque.pop_front();
        //tmp.setFillColor(sf::Color::Red);
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        //tmp.setRotation(angle);
        float tmpangle=angle*2*3.14/360;
        tmp.move(sf::Vector2f(sin(tmpangle)*speed,cos(tmpangle)*speed));
        snakeDeque.push_back(tmp);
    }
private:
sf::CircleShape tmp;
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
