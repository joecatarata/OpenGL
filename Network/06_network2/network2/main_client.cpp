/*
Linux:
g++ NetworkThread.cpp main_client.cpp -o runC.exe -lsfml-system -lsfml-network && ./runC.exe

Windows:
g++ NetworkThread.cpp main_client.cpp -o runC.exe -IC:/sfml/include -LC:/sfml/lib -lsfml-system -lsfml-network && runC.exe
*/
#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "NetworkThread.h"

const unsigned short PORT = 54000;
const sf::IpAddress RECIPIENT = "127.0.0.1";

int main(){
    NetworkThread network(PORT);
    sf::Thread thread(&NetworkThread::threadRun, &network);
    thread.launch();

    std::cout << "THE END" << std::endl;
    return 0;
}//end main
