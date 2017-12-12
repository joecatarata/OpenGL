#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class NetworkThread{
public:
    NetworkThread(unsigned short port);
    void sendMessage(sf::IpAddress recipient, char message[100]);
    void threadRun();
private:
    sf::UdpSocket socket;
    void receiveMessage();
    sf::Mutex mutex;
    bool isAlive;
    unsigned short sysPort;
};

#endif
