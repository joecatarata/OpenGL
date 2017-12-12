/*
Linux:
g++ main.cpp -o run.exe -lsfml-network && ./run.exe

Windows:
g++ main.cpp -o run.exe -IC:/sfml/include -LC:/sfml/lib -lsfml-network && run.exe
*/
#include <iostream>
#include <SFML/Network.hpp>

const unsigned short PORT = 54000;
const sf::IpAddress RECIPIENT = "127.0.0.1";
const int MESSAGE_LENGTH = 50;

void connectUDP(sf::UdpSocket& socket){
    // bind the socket to a port
    if (socket.bind(PORT) == sf::Socket::Done){
        std::cout << "successful reservation of port " << PORT << std::endl;
    }//end if
}//end func


void sendMessage(sf::UdpSocket& socket, char message[MESSAGE_LENGTH]){
    // send message to recipient
    if (socket.send(message, 100, RECIPIENT, PORT) == sf::Socket::Done){
        std::cout << "sending message to " << RECIPIENT << std::endl;
    }//end if
}//end func

void receiveMessage(sf::UdpSocket& socket){
    char dataReceived[MESSAGE_LENGTH];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short port;

    // receive message to recipient
    if (socket.receive(dataReceived, MESSAGE_LENGTH, received, sender, port) == sf::Socket::Done){
        std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
        std::cout << dataReceived << std::endl;
    }//end if
}//end func

int main(){
    sf::UdpSocket socket;
    connectUDP(socket);

    char dataMessage[MESSAGE_LENGTH] = "pork-Q-pine";
    sendMessage(socket, dataMessage);

    receiveMessage(socket);

    std::cout << "THE END" << std::endl;
    return 0;
}
