/**
Linux
g++ 03_class_and_thread.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ 03_class_and_thread.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

This is code directly form the SFML website
*/
#include <SFML/System.hpp>
#include <iostream>

int sum = 0;
sf::Mutex mutex;

class CSV{
    public:
        CSV(): myThread(&CSV::run, this){
            willRun = true;
        }
        
        void init(int id){
            willRun = true;
            idNo = id;
        }

        void run(){
            while(willRun){
                mutex.lock();
                if(sum>=1000)
                    willRun = false;
                else
                    sum += 10;
                std::cout << idNo<< " : " <<sum<< std::endl;
                mutex.unlock();
                sf::sleep(sf::milliseconds(1));
            }
            
        }
        void start(){
            myThread.launch();
        }
    private:
        sf::Thread myThread;
        bool willRun;
        int idNo;
};

int main(){
    CSV csv[20];
    for(int i=0;i<20;i++){
        csv[i].init(i+1);
        csv[i].start();
    }
    return 0;
}