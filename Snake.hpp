#ifndef Snake_HPP_INCLUDED
#define Snake_HPP_INCLUDED
#include <deque>
using namespace std;

class Snake
{
public:
bool active;
std::deque<sf::CircleShape> snakeDeque;
float angle=0;
float speed=4.1f;
float radius=5;
bool left,right;
float radiusChange=1;
unsigned int score=0;
unsigned int limit=150;
    Snake(sf::Vector2f position,sf::Color color):tmp(radius,1000)
    {
        tmp.setPosition(position);
        tmp.setFillColor(color);
        snakeDeque.push_back(tmp);
        right=false;
        left=false;
        active=false;
    }
    void resizeSnake(bool increase)
    {
        if(!increase)
        {
            if((radius-radiusChange)>0) radius-=radiusChange;
        }
        else radius+=radiusChange;
        //sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        //tmp.setRotation(angle);
        float tmpangle=angle*2*3.14/360-90;
        tmp.setRadius(radius);
        tmp.move(sf::Vector2f(sin(tmpangle)*radiusChange,cos(tmpangle)*radiusChange));
    }
    void addPiece(short fps)
    {
        if(speed>0)
        {
            float finalSpeed=fps*speed/60;
            if(snakeDeque.size()>limit) snakeDeque.pop_front();
            float tmpangle=angle*2*3.14/360;
            tmp.move(sf::Vector2f(sin(tmpangle)*finalSpeed,cos(tmpangle)*finalSpeed));
            snakeDeque.push_back(tmp);
        }
    }
    void onlineAddPiece(sf::Vector2f head)
    {
        if(speed>0)
        {
            //float finalSpeed=fps*speed/60;
            //if(snakeDeque.size()>limit) snakeDeque.pop_front();
            //float tmpangle=angle*2*3.14/360;
            tmp.setPosition(head);
            snakeDeque.push_back(tmp);
        }
    }
    void test()
    {
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
    bool checkFoodHit(sf::Vector2f foodPos, float rad)
    {
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        if(calculateDistance(pos,foodPos) < (rad+radius)) return true;
        else return false;
    }
    bool selfCollide(Snake *s[],int thisSnake)
    {
        if(snakeDeque.size()<60) return false;
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();

        sf::Vector2f others[3];
        short id[3];
        short counter=0;
        for(short j=0;j<4;j++)
        {
            if(j!=thisSnake)
            {
                others[counter]=s[j]->snakeDeque.at(s[j]->snakeDeque.size()-1).getPosition();
                id[counter]=j;
                counter++;
            }
        }
        for(int i=0;i<snakeDeque.size();i++)
        {
            if(i<snakeDeque.size()-50)
            {
                if(calculateDistance(pos,snakeDeque.at(i).getPosition())<=(radius*2))
                {
                    return true;
                }
            }
            for(short j=0;j<3;j++)
            {
                //if(i==0 && thisSnake==2) cout << "distance: "<<calculateDistance(others[j],snakeDeque.at(i).getPosition())<<endl;
                if(s[id[j]]->active)
                {
                    if(calculateDistance(others[j],snakeDeque.at(i).getPosition())<=(radius*2))
                    {
                        s[id[j]]->die();
                    }
                }
            }
        }
        if(pos.x<0 || pos.x>800 || pos.y<0 || pos.y>600)
        {
            //cout << "pos: x:"<<pos.x<<" y:"<<pos.y<<endl;
            return true;
        }
        return false;
    }
    void die()
    {
        speed=0;
    }
private:
sf::CircleShape tmp;
    float calculateDistance(sf::Vector2f a,sf::Vector2f b)
    {
        return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
    }
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
/*
bool selfCollide()
    {
        if(snakeDeque.size()<60) return false;
        sf::Vector2f pos=snakeDeque.at(snakeDeque.size()-1).getPosition();
        for(int i=0;i<snakeDeque.size()-50;i++)
        {
            if(calculateDistance(pos,snakeDeque.at(i).getPosition())<=(radius*2))
            {
                return true;
            }
        }
        if(pos.x<0 || pos.x>800 || pos.y<0 || pos.y>600)
        {
            //cout << "pos: x:"<<pos.x<<" y:"<<pos.y<<endl;
            return true;
        }
        return false;
    }
*/
