/*
Linux:
g++ NetworkThread.cpp main_server.cpp -o runS.exe -lsfml-system -lsfml-network && ./runS.exe

Windows:
g++ NetworkThread.cpp main_server.cpp -o runS.exe -IC:/sfml/include -LC:/sfml/lib -lsfml-system -lsfml-network && runS.exe
*/
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "NetworkThread.h"

const unsigned short PORT = 54000;
const sf::IpAddress RECIPIENT = "192.168.0.126";

int main(){
    NetworkThread network(PORT);
    char dataMessage[100] = ".+pork-Q-pine";
    for(short i=0;i<27;i++){
        dataMessage[0] = (char)('sex'+i);
        network.sendMessage(RECIPIENT, dataMessage);
    }//end for

    std::cout << "THE END" << std::endl;
    return 0;
}//end main
