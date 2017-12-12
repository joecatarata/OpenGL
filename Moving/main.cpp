/**
Linux
g++ AbsObject.cpp Camera.cpp main.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ AbsObject.cpp Camera.cpp main.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

Start Window
*/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "AbsObject.h"
#include "Camera.h"

int main(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    srand(time(NULL));
    sf::Window window(sf::VideoMode(800, 600), "SFML Board Movement", sf::Style::Default, settings);
    window.setPosition(sf::Vector2i(0,0));

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cout << "ERROR" << std::endl;

    GLfloat points[] = {
      -0.5f, 0.5f, 0.0f,
      -0.5f,-0.5f, 0.0f,
       0.5f,-0.5f, 0.0f,
       
      -0.5f, 0.5f, 0.0f,
       0.5f,-0.5f, 0.0f,
       0.5f, 0.5f, 0.0f,
    };
    const int BOARD_LENGTH = 10;
    const float TILE_SIZE = 0.2f;
    const float MOVER_SIZE = TILE_SIZE*0.76f;
    bool isPressed = false;
    int xPos = 0;
    int yPos = 9;
    
    AbsObject object[BOARD_LENGTH][BOARD_LENGTH];
    
    AbsObject mover(points,sizeof(points),1,0,0);
    mover.getScalePtr()->x = MOVER_SIZE;
    mover.getScalePtr()->y = MOVER_SIZE;
    mover.getTranslationPtr()->y = - TILE_SIZE*5;
    mover.getTranslationPtr()->x = - TILE_SIZE*5;
    int teleX, prevX;
    float transX, prevTransX;
    int teleY, prevY;
    float transY, prevTransY;
    float red;
    float green;
    float blue;


    //Initialize teleport tiles
    for(int i=0; i<10; i++){
        red = static_cast<float>(rand()%255)/255.0;
        blue = static_cast<float>(rand()%255)/255.0;
        green = static_cast<float>(rand()%255)/255.0;
        
        for(int j=0; j<2; j++){
            teleX = rand()%9+1;
            teleY = rand()%9+1;
            printf("%d, %d\n", teleY, teleX);
            object[teleY][teleX].init(points, sizeof(points), red, green, blue); 
            object[teleY][teleX].getScalePtr()->x = TILE_SIZE;
            object[teleY][teleX].getScalePtr()->y = TILE_SIZE;
            object[teleY][teleX].getTranslationPtr()->y = teleY*TILE_SIZE - TILE_SIZE*5;
            object[teleY][teleX].getTranslationPtr()->x = teleX*TILE_SIZE - TILE_SIZE*5;
            object[teleY][teleX].teleportTile = true;
            if(j==0){
                prevX = teleX;
                prevY = teleY;
                prevTransX = object[teleY][teleX].getTranslationPtr()->x;
                prevTransY = object[teleY][teleX].getTranslationPtr()->y;
            }   

            if(j==1){
                object[prevY][prevX].partnerXpos = teleX;
                object[prevY][prevX].partnerYpos = teleY;
                object[prevY][prevX].partnerTransX = object[teleY][teleX].getTranslationPtr()->x;
                object[prevY][prevX].partnerTransY = object[teleY][teleX].getTranslationPtr()->y;

                object[teleY][teleX].partnerXpos = prevX;
                object[teleY][teleX].partnerYpos = prevY;
                object[teleY][teleX].partnerTransX = prevTransX;
                object[teleY][teleX].partnerTransY = prevTransY;
            }
        }
     }
    
    //Initialize other tiles
    for(int i=0;i<BOARD_LENGTH;i++){
        for(int j=0;j<BOARD_LENGTH;j++){
            if(object[i][j].teleportTile == false){
                if(i == 9 && j == 9)
                    object[i][j].init(points, sizeof(points), 0, 0, 0);
                else if(i%2==0&&j%2==0 || i%2==1&&j%2==1)
                    object[i][j].init(points,sizeof(points),1,1,1);
                else
                    object[i][j].init(points,sizeof(points),0,1,0);
                object[i][j].getScalePtr()->x = TILE_SIZE;
                object[i][j].getScalePtr()->y = TILE_SIZE;
                object[i][j].getTranslationPtr()->y = i*TILE_SIZE - TILE_SIZE*5;
                object[i][j].getTranslationPtr()->x = j*TILE_SIZE - TILE_SIZE*5;
            }
        }
    }

    Camera camera(70,800.0f/600.0f,0.01f,100.0f,0,0,3);
    camera.updateCamera();

    //makes sure the program runs at 60 FPS
    const float TIME_PER_FRAME = 1.0f/60*1000;
    sf::Clock clock;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }else if (event.type == sf::Event::Resized){
                glViewport(0, 0, event.size.width, event.size.height);
            }//end else if
        }//end while

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(!isPressed && yPos-1 >= 0){
                std::cout << "UP" << std::endl;
                mover.getTranslationPtr()->y += TILE_SIZE;
                yPos--;
                std::cout <<"(" <<xPos<< "," << yPos<< ")" << std::endl;
                isPressed = true;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(!isPressed && yPos+1 < BOARD_LENGTH){
                std::cout << "DOWN" << std::endl;
                mover.getTranslationPtr()->y -= TILE_SIZE;
                yPos++;
                std::cout <<"(" <<xPos<< "," << yPos<< ")" << std::endl;
                isPressed = true;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(!isPressed && xPos-1 >= 0){
                std::cout << "LEFT" << std::endl;
                mover.getTranslationPtr()->x -= TILE_SIZE;
                xPos--;
                std::cout <<"(" <<xPos<< "," << yPos<< ")" << std::endl;
                isPressed = true;
            }
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(!isPressed && xPos+1 < BOARD_LENGTH){
                std::cout << "RIGHT" << std::endl;
                mover.getTranslationPtr()->x += TILE_SIZE;
                xPos++;
                std::cout <<"(" <<xPos<< "," << yPos<< ")" << std::endl;
                isPressed = true;
            }
        }else if(isPressed){
            isPressed = false;
        }
        //teleport mechanic
        // if(object[yPos][xPos].teleportTile == true){
        //     printf("teleport!\n");
        //     mover.getTranslationPtr()->x = object[yPos][xPos].partnerTransX;
        //     mover.getTranslationPtr()->y = object[yPos][xPos].partnerTransY;
        //     xPos = object[yPos][xPos].partnerXpos;
        //     yPos = object[yPos][xPos].partnerYpos;
        //     std::cout <<"(" <<xPos<< "," << yPos<< ")" << std::endl;
        //     isPressed = true;
        // }
        //win
        if(xPos == 9 && yPos == 0){
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        for(int i=0;i<BOARD_LENGTH;i++)
            for(int j=0;j<BOARD_LENGTH;j++)
                object[i][j].draw(camera.getProjection());

        mover.draw(camera.getProjection());
        window.display();

        //regulates the frames to 60
        sf::sleep(sf::milliseconds(TIME_PER_FRAME-
            clock.getElapsedTime().asMilliseconds()));
        clock.restart();
    }//end while
    return 0;
}//end func

/*
  (Ｔ▽Ｔ) - proper response!
FPS regulator now allows a specific rate of refresh. This makes
game behaviour more understandable.
*/
