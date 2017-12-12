#include "NetworkThread.h"

NetworkThread::NetworkThread(unsigned short port){
    if (socket.bind(port) == sf::Socket::Done){
        std::cout << "successful reservation of port " << port << std::endl;
        isAlive = true;
        sysPort = port;
    }//end if
}//end func

void NetworkThread::sendMessage(sf::IpAddress recipient, char message[100]){
    // send message to recipient
    if (socket.send(message, 100, recipient, sysPort) == sf::Socket::Done){
        std::cout << "sending message to " << recipient << std::endl;
    }//end if
}//end func

void NetworkThread::threadRun(){
    while(isAlive){
        std::cout << "." << std::endl;
        receiveMessage();
    }//end while
}//end func

void NetworkThread::receiveMessage(){
    char dataReceived[100];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    // receive message to recipient
    if (socket.receive(dataReceived, 100, received, sender, port) == sf::Socket::Done){
        std::cout << dataReceived << std::endl;
        if(dataReceived[0]=='z')
            isAlive = false;
    }//end if
}//end func

