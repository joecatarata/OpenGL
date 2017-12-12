#ifndef SCV_H
#define SCV_H

#include <SFML/System.hpp>
#include <iostream>

class SCV{
    public:
        SCV(): myThread(&SCV::run, this){
            willRun = true;
        }
        
        void init(int id,int* sum,sf::Mutex* mutexVal){
            willRun = true;
            idNo = id;
            ptrSum = sum;
            mutex = mutexVal;
        }

        void run(){
            while(willRun){
                mutex->lock();
                if(*ptrSum>=1000)
                    willRun = false;
                else
                    *ptrSum += 10;
                std::cout << idNo<< " : " <<*ptrSum<< std::endl;
                mutex->unlock();
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
        int* ptrSum;
        sf::Mutex* mutex;
};

#endif /*SCV_H*/