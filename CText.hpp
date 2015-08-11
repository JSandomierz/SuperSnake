#ifndef CText_HPP_INCLUDED
#define CText_HPP_INCLUDED
#include <sstream>
using namespace std;

class CText:public sf::Text
{
public:
    CText()
    {
        f.loadFromFile("OldNewspaperTypes.ttf");
        this->setFont(f);
    }
    string floatToString(short x)
    {
        std::ostringstream s;
        s<<x;
        return s.str();
    }
private:
    sf::Font f;
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
