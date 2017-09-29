#ifndef Game_HPP_INCLUDED
#define Game_HPP_INCLUDED
using namespace std;

class FoodPiece: public sf::CircleShape
{
public:
    int value;
private:
};

class Game
{
public:
    Snake *s[4];
    GUI mainMenu;
    FoodPiece food;
    short fps;
    int playerID;
    float snakeSpeed;
    //sf::Vector2u arenaSize;
    Game(bool *run, bool *menu, sf::RenderWindow *window, float &speedRating)
    {
        srand(time(NULL));
        this->window=window;
        this->menu=menu;
        isActive=run;
        snakeSpeed=speedRating;
        mainMenu.createMainMenu(window->getSize());
        food.setOrigin(15,15);
        food.setPointCount(300);
        food.setRadius(15);
        food.setFillColor(sf::Color(255,255,51));
        colors[0]=sf::Color(255,55,50);
        colors[1]=sf::Color(21,253,253);
        colors[2]=sf::Color(255,211,0);
        colors[3]=sf::Color(71,242,19);
        init();
    }
    void init()
    {
        food.setPosition(rand()%(800-(int)food.getRadius())+1,rand()%600-(int)food.getRadius()+1);
        food.value=rand()%50+1;
        s[0]=new Snake(sf::Vector2f(50,50),colors[0],snakeSpeed);
        s[1]=new Snake(sf::Vector2f(750,50),colors[1],snakeSpeed);
        s[2]=new Snake(sf::Vector2f(750,550),colors[2],snakeSpeed);
        s[3]=new Snake(sf::Vector2f(50,550),colors[3],snakeSpeed);
        for(short i=0;i<4;i++)
        {
            s[i]->angle=90*i;
        }
    }
    void processEvents(sf::Event &event)
    {
        if(event.type==sf::Event::Closed) *isActive=false;
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::Escape) *menu=true;
                //*isActive=false;
        }
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::A)
            {
                s[0]->left=true;
            }
            if(event.key.code==sf::Keyboard::D)
            {
                s[0]->right=true;
            }
            if(event.key.code==sf::Keyboard::Left)
            {
                s[2]->left=true;
            }
            if(event.key.code==sf::Keyboard::Right)
            {
                s[2]->right=true;
            }
            if(event.key.code==sf::Keyboard::Add)
            {
                //s[0]->resizeSnake(true);
            }
            if(event.key.code==sf::Keyboard::BackSpace)
            {
                init();
                s[0]->active=true;
            }
        }
        if(event.type == sf::Event::KeyReleased)
        {
            if(event.key.code==sf::Keyboard::A)
            {
                s[0]->left=false;
            }
            if(event.key.code==sf::Keyboard::D)
            {
                s[0]->right=false;
            }
            if(event.key.code==sf::Keyboard::Left)
            {
                s[2]->left=false;
            }
            if(event.key.code==sf::Keyboard::Right)
            {
                s[2]->right=false;
            }
            //if(event.key.code==sf::Keyboard::A) cout << "a released\n";
        }
        if(event.type==sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                {
                    float x,y;
                    sf::Mouse mouse;
                    pos=(sf::Vector2f)mouse.getPosition()-(sf::Vector2f)window->getPosition();
                }
            }
            /*if(event.mouseButton.button == sf::Mouse::Right)
            {
                s[0]=new Snake(sf::Vector2f(100,100),colors[0]);
                s[0]->active=true;
            }*/
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
    void processMenuEvents(sf::Event &event)
    {
        float x,y;
        sf::Mouse mouse;
        pos=(sf::Vector2f)mouse.getPosition()-(sf::Vector2f)window->getPosition();
        mainMenu.current=mainMenu.checkHits(pos);

        if(event.type==sf::Event::Closed) *isActive=false;
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::Escape) *isActive=false;
        }

        if(event.type == sf::Event::KeyReleased)
        {
            //if(event.key.code==sf::Keyboard::A) cout << "a released\n";
        }
        if(event.type==sf::Event::MouseButtonPressed)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
            }
            if(event.mouseButton.button == sf::Mouse::Right)
            {
            }
        }
        if(event.type==sf::Event::MouseButtonReleased)
        {
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                switch(mainMenu.current)
                {
                case 0:
                    init();
                    *menu=false;
                    s[0]->active=true;
                break;
                case 1:
                    init();
                    *menu=false;
                    s[0]->active=true;
                    s[2]->active=true;

                break;
                case 2:
                    *isActive=false;
                break;
                }
            }

            if(event.mouseButton.button == sf::Mouse::Right)
            {
            }
        }
    }
    void processMovement(unsigned int &hiScore)
    {
        for(short i=0;i<4;i++)
        {
            if(s[i]->active)
            {
                if(s[i]->left) s[i]->angle+=5;
                if(s[i]->right) s[i]->angle-=5;
                s[i]->addPiece(fps);
                if(s[i]->checkFoodHit(food.getPosition(),food.getRadius()))
                {
                    s[i]->limit+=food.value;
                    s[i]->score+=food.value;
                    if(s[i]->speed<5.1f) s[i]->speed+=0.1f;
                    food.setPosition(rand()%(800-(int)food.getRadius()*2)+(int)food.getRadius(),rand()%(600-(int)food.getRadius()*2)+(int)food.getRadius());
                    food.value=rand()%50+1;
                    food.setFillColor(sf::Color(food.value*4+50,0,255));
                }
                if(s[i]->selfCollide(s,i,window->getSize()))
                {
                    s[i]->die();
                    if(i==0 && s[i]->score>hiScore)
                    {
                        hiScore=s[i]->score;
                        FileOperator tmpOp;
                        tmpOp.writeBestScore(hiScore);
                    }

                }
            }
        }
    }
private:
//wskazniki na zmienne z mainu
sf::RenderWindow *window;
bool *isActive,*menu;
sf::Vector2f pos;
sf::Color colors[4];
};
#endif //CFRAMECOUNTER_HPP_INCLUDED
