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
        //test();
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
        //test();

        if(snakeDeque.size()>60)
        {
            if(selfCollide()) tmp.setFillColor(sf::Color::Red);
        }


    }
    void test()
    {
        //cout << calculateDistance(sf::Vector2f(1,1),sf::Vector2f(10,10))<<" test"<<endl;

        if(snakeDeque.size()==10)
        {
            snakeDeque.pop_front();
            for(int i=0;i<9;i++) cout << "S frag "<<i<<" x:"<<snakeDeque.at(i).getPosition().x<<" y:"<<snakeDeque.at(i).getPosition().y<<endl;
        }
    }
    void reset()
    {
        snakeDeque.clear();
        tmp.setFillColor(sf::Color::White);
        tmp.setPosition(400,300);
        snakeDeque.push_back(tmp);
    }
private:
sf::CircleShape tmp;
    bool selfCollide()
    {
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        for(int i=0;i<snakeDeque.size()-50;i++)
        {
            if(calculateDistance(pos,snakeDeque.at(i).getPosition())<=(radius*2))
            {
                //cout << "pos: x:"<<pos.x<<" y:"<<pos.y<<endl;
                //cout << "collision: x:"<<snakeDeque.at(i).getPosition().x<<" y:"<<snakeDeque.at(i).getPosition().y<<endl;
                return true;
            }
        }
        return false;
    }
    float calculateDistance(sf::Vector2f a,sf::Vector2f b)
    {
        //cout <<"testing a:"<< (b.x-a.x)<<" b: "<<(b.y-a.y)<<" c:"<<sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y))<<endl;
        return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
    }
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
