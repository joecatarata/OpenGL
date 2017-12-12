/**
Linux
g++ 02_mutex.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ 02_mutex.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

This is code directly form the SFML website
*/
#include <SFML/System.hpp>
#include <iostream>

int sum = 0;
sf::Mutex mutex;

void func(int num){
    // this function is started when thread.launch() is called
    for (int i = 0; i < 100; ++i){
        mutex.lock();
        sum += i+1;
        std::cout << num<<"XXX: "<<sum<< std::endl;
        mutex.unlock();
        sf::sleep(sf::milliseconds(1));
    }
}

int main(){
    std::cout << "expected:" <<(5050*11)<< std::endl;
    
    // create a thread with func() as entry point
    sf::Thread thread1(&func,1);
    thread1.launch();
    sf::Thread thread2(&func,2);
    thread2.launch();
    sf::Thread thread3(&func,3);
    thread3.launch();
    sf::Thread thread4(&func,4);
    thread4.launch();
    sf::Thread thread5(&func,5);
    thread5.launch();
    sf::Thread thread6(&func,6);
    thread6.launch();
    sf::Thread thread7(&func,7);
    thread7.launch();
    sf::Thread thread8(&func,8);
    thread8.launch();
    sf::Thread thread9(&func,9);
    thread9.launch();
    sf::Thread thread10(&func,10);
    thread10.launch();

    // the main thread continues to run...
    for (int i = 0; i < 100; ++i){
        mutex.lock();
        sum += i+1;
        std::cout << "Main :" <<sum<< std::endl;
        mutex.unlock();
        sf::sleep(sf::milliseconds(1));
    }
    return 0;
}