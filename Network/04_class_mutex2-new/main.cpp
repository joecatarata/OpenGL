/**
Linux
g++ main.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ main.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

This is code directly form the SFML website
*/
#include <SFML/System.hpp>
#include <iostream>
#include "SCV.h"

int main(){
    int sum = 0;
    sf::Mutex mutex;
    
    SCV scv[20];
    for(int i=0;i<20;i++){
        scv[i].init(i+1,&sum,&mutex);
        scv[i].start();
    }
	
	//make sure that the main is not dead because
	//it may clean the mutex in the stack
	bool isDone = false;
	while(!isDone){
		mutex.lock();
		if(sum>=1000)isDone = true;
        mutex.unlock();
		sf::sleep(sf::milliseconds(5));
	}
	std::cout<<"done"<<std::endl;
    return 0;
}