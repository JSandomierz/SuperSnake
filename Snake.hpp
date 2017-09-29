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
float speed=1.0f;
float radius=5;
bool left,right;
float radiusChange=1;
unsigned int score=0;
unsigned int limit=150;
    Snake(sf::Vector2f position,sf::Color color,float &speedRating):tmp(radius,1000)
    {
        speed=speedRating;
        tmp.setOrigin(radius/2,radius/2);
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
        if(speed>0 && fps!=0)
        {
            float finalSpeed=60.f/fps*speed;
            if(finalSpeed>6.1f) finalSpeed=6.1f;
            if(snakeDeque.size()>limit) snakeDeque.pop_front();
            float tmpangle=angle*2*3.14/360;
            tmp.move(sf::Vector2f(sin(tmpangle)*finalSpeed,cos(tmpangle)*finalSpeed));
            snakeDeque.push_back(tmp);
            //cout <<fps<<", speed: "<<finalSpeed<<", pos:"<<tmp.getPosition().x << ", "<<tmp.getPosition().y<<endl;
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
    bool selfCollide(Snake *s[],int thisSnake, sf::Vector2u windowSize)
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
        if(pos.x<radius || pos.x>windowSize.x-radius || pos.y<radius || pos.y>windowSize.y-radius) return true;
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
