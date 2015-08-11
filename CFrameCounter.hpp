#ifndef CFRAMECOUNTER_HPP_INCLUDED
#define CFRAMECOUNTER_HPP_INCLUDED

#include <iostream>

using namespace std;

class CFrameCounter
{
 public:
    sf::Clock fpscounter;
    sf::Time seconds;
    short frames;
    short frames_old;
    CFrameCounter() : frames(0)
    {
    }
    void count()
    {
        frames++;
        seconds=fpscounter.getElapsedTime();
        if(seconds.asSeconds()>=1){
            frames_old=frames;
            frames=0;
            fpscounter.restart();
        }
    }
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
