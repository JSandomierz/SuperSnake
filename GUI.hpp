#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED
using namespace std;

class Button
{
public:
sf::RectangleShape body;
sf::Text text;
float min_scale=1;
float max_scale=1.5;
    Button(string content,sf::Vector2f position,sf::Vector2f buttonSize,sf::Font *font)
    {
        //content="TESTING";
        //f.loadFromFile("OldNewspaperTypes.ttf");
        text.setFont(*font);
        text.setString(content);

        //text.setColor(sf::Color::Black);
        body.setFillColor(sf::Color::Green);

        body.setSize(buttonSize);

        body.setOrigin(sf::Vector2f(buttonSize.x/2,buttonSize.y/2));
        text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height/2+8);

        text.setPosition(position);
        body.setPosition(position);
    }
    Button()
    {
        sf::Vector2f position=sf::Vector2f(300,300);
        sf::Vector2f buttonSize=sf::Vector2f(300,300);

        //text.setFont(f);
        text.setString("TESTING");

        text.setColor(sf::Color::White);
        body.setFillColor(sf::Color::Green);

        body.setSize(buttonSize);

        body.setOrigin(sf::Vector2f(buttonSize.x/2,buttonSize.y/2));
        text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height/2+8);

        text.setPosition(position);
        body.setPosition(position);
    }
private:
};

class GUI
{
public:
    vector<Button> buttons;
    vector<CText> boards;
    int current;
    GUI()
    {
        if(!f.loadFromFile("OldNewspaperTypes.ttf")) cout <<"broken";
    }
    void createMainMenu()
    {
        buttons.clear();
        buttons.push_back(*new Button("1 player",sf::Vector2f (400,100),sf::Vector2f(200,60),&f));
        buttons.push_back(*new Button("2 players",sf::Vector2f (400,200),sf::Vector2f(200,60),&f));
        buttons.push_back(*new Button("Server",sf::Vector2f (400,300),sf::Vector2f(200,60),&f));
        buttons.push_back(*new Button("Client",sf::Vector2f (400,400),sf::Vector2f(200,60),&f));
        buttons.push_back(*new Button("Exit",sf::Vector2f (400,500),sf::Vector2f(200,60),&f));
    }
    int checkHits(sf::Vector2f pos)
    {
        for(int i=0;i<buttons.size();i++)
        {
            sf::FloatRect hitbox=buttons.at(i).body.getLocalBounds();
            hitbox.top=buttons.at(i).body.getPosition().y;
            hitbox.left=buttons.at(i).body.getPosition().x-buttons.at(i).body.getSize().x/2;
            if(hitbox.contains(pos))
            {
                return i;
            }
        }
        return -1;
    }
    void scaleButtons()
    {
        float scaleFactor=0.05f;
        for(int i=0;i<buttons.size();i++)
        {
            if(current == i)
            {
                if(buttons.at(i).body.getScale().x<buttons.at(i).max_scale)
                {
                    buttons.at(i).body.setScale(buttons.at(i).body.getScale().x+scaleFactor,buttons.at(i).body.getScale().y+scaleFactor);
                    buttons.at(i).text.setScale(buttons.at(i).text.getScale().x+scaleFactor,buttons.at(i).text.getScale().y+scaleFactor);
                }
            }
            else if(buttons.at(i).body.getScale().x>buttons.at(i).min_scale)
            {
                buttons.at(i).body.setScale(buttons.at(i).body.getScale().x-scaleFactor,buttons.at(i).body.getScale().y-scaleFactor);
                buttons.at(i).text.setScale(buttons.at(i).text.getScale().x-scaleFactor,buttons.at(i).text.getScale().y-scaleFactor);
            }
        }
    }
private:
    sf::Font f;
};

#endif
