#ifndef FileOperator_HPP_INCLUDED
#define FileOperator_HPP_INCLUDED
#include <sstream>
using namespace std;
class FileOperator
{
public:
    void loadConfig(int &antialiasing, int &width, int &height, sf::Uint32 &style, float &speedRating)
    {
        ifstream in;
        in.open("config.txt");
        int tmp;
        in>>tmp;
        if(tmp==1) style=sf::Style::Fullscreen;
        else style=sf::Style::Titlebar|sf::Style::Close;
        in>>tmp;
        if(tmp>0&&tmp<2000) width=tmp;
        in>>tmp;
        if(tmp>0&&tmp<2000) height=tmp;
        in>>tmp;
        if(tmp>0&&tmp<32) antialiasing=tmp;
        float ftmp;
        in>>ftmp;
        if(ftmp>0&&ftmp<10) speedRating=ftmp;

        in.close();
    }
    unsigned int readBestScore()
    {
        ifstream in;
        in.open("highscore");
        if(!in.good())
        {
            ofstream out("highscore");
            out<<(int)0;
            out.close();
            return 0;
        }
        unsigned int tmp;
        in>>tmp;
        return tmp;
    }
    void writeBestScore(unsigned int &hiScore)
    {
        ofstream out("highscore");
        out<<hiScore;
        out.close();
    }
};
#endif //FileOperator_HPP_INCLUDED
