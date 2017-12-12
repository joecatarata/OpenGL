/**
Linux
g++ 01_thread_intro.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ 01_thread_intro.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

Start Window
This is code directly form the SFML website
*/
#include <SFML/System.hpp>
#include <iostream>

void func(){
    // this function is started when thread.launch() is called
    int sum = 0;
    for (int i = 0; i < 100; ++i){
        sum += i+1;
        std::cout << "One: "<<sum<< std::endl;
    }
}

int main(){
    // create a thread with func() as entry point
    sf::Thread thread(&func);

    // run it
    thread.launch();

    // the main thread continues to run...
    int sum = 0;
    for (int i = 0; i < 100; ++i){
        sum += i+1;
        std::cout << "Main :" <<sum<< std::endl;
    }
    return 0;
}