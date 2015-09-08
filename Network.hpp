#ifndef Network_HPP_INCLUDED
#define Network_HPP_INCLUDED
#include <list>
using namespace std;

class Player
{
public:
    int ID;
};

class Server
{
    public:
    sf::TcpListener listener;
    list<sf::TcpSocket*> sockets;
    sf::SocketSelector selector;

    Server()
    {
        listener.listen(port);
        selector.add(listener);
    }
    void mainActivity(Game &game)
    {
        while(selector.wait(sf::Time(sf::seconds(1))))
        {
            if(selector.isReady(listener))
            {
                sf::TcpSocket* tmp=new sf::TcpSocket;
                tmp->setBlocking(false);
                if(listener.accept(*tmp)==sf::Socket::Done)
                {
                    sockets.push_back(tmp);
                    selector.add(*tmp);
                }
                else delete tmp;
            }
            else
            {
                int counter=0;
                for(list<sf::TcpSocket*>::iterator i=sockets.begin();i!=sockets.end();i++)
                {
                    sf::TcpSocket* tmp=*i;
                    if(selector.isReady(*tmp))
                    {
                        sf::Packet packet,out;
                        if(tmp->receive(packet)==sf::Socket::Done)
                        {
                            int id,playerID;
                            packet>>id;
                            switch(id)
                            {
                                case 0:
                                {
                                    //odbior
                                    //packet>>playerID;
                                    playerID=counter;
                                    bool left,right;
                                    packet>>left>>right;
                                    //cout << "\nReceived info from snake "<<counter;
                                    game.processOnlineMovement(left,right,playerID);
                                    //odpowiedz
                                    sf::Vector2f playerHead;
                                    out<<(int)0;
                                    for(short j=0;j<4;j++)//nadanie glow 4 wezy po aktualizacji
                                    {
                                        playerHead=game.s[j]->snakeDeque.at(game.s[j]->snakeDeque.size()-1).getPosition();
                                        out<<playerHead.x<<playerHead.y;
                                        //cout << "Head "<<j<< " "<<playerHead.x<<", "<<playerHead.y<<endl;
                                    }
                                }
                                break;
                                case 100:
                                    out<<counter;
                                break;
                            }
                            //cout << "\nSent info to snake "<<counter;
                            tmp->send(out);
                        }
                    }
                    counter++;
                }
            }
        }
    }

    private:
    const short port=1337;

};

class Client
{
public:
    bool connected;
    sf::TcpSocket socket;
    Client()
    {
        socket.setBlocking(false);
        connected=false;
    }
    bool connect(Game &game,string ip)
    {
        sf::IpAddress a=sf::IpAddress(ip);
        sf::Time t = sf::seconds(10.f);
        if(socket.connect(sf::IpAddress::LocalHost,port,t)!=sf::Socket::Done) return false;
        else
        {
            sf::Packet in,out;
            out<<(int)100;
            cout << "connect attempt!\n";
            socket.send(out);
            cout << "sent!\n";
            socket.receive(in);
            in>>game.playerID;
            game.s[game.playerID]->active=true;
            cout << "connected with id "<<game.playerID<<endl;
            return true;
        }
    }
    bool updateSnakes(Game &game)
    {
        //sf::sleep(sf::Time(sf::milliseconds(10)));
        sf::Packet in,out;
        int messageID=0;
        out<<messageID<<game.s[game.playerID]->left<<game.s[game.playerID]->right;
        socket.send(out);
        socket.receive(in);
        in>>messageID;
        sf::Vector2f heads[4];
        for(short i=0;i<4;i++)
        {
            in>>heads[i].x>>heads[i].y;
            //cout << "Head "<<i<< " "<<heads[i].x<<", "<<heads[i].y<<endl;
        }
        game.updateOnlineMovement(heads);
        if(messageID==1) return false;
        else return true;
    }
private:
    const short port=1337;
};

#endif //Network_HPP_INCLUDED
