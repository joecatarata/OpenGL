/**
Linux
g++ *.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ *.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe
*/
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "ObjTexture.h"
#include "Camera.h"

int main(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "RPS Game", sf::Style::Default, settings);
    window.setPosition(sf::Vector2i(0,0));

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cout << "ERROR" << std::endl;

    ObjTexture rock("./imgs/rock.png");
    ObjTexture paper("./imgs/paper.png");
    ObjTexture scissor("./imgs/scissors.png");
    ObjTexture selectp1("./imgs/corporal-p1.png");
    ObjTexture selectp2("./imgs/corporal-p2.png");
    ObjTexture winp1("./imgs/thumb-up-p1.png");
    ObjTexture winp2("./imgs/thumb-up-p2.png");
    ObjTexture losep1("./imgs/thumb-down-p1.png");
    ObjTexture losep2("./imgs/thumb-down-p2.png");
    ObjTexture p1icon("./imgs/corporal-p1.png");
    ObjTexture p2icon("./imgs/corporal-p2.png");

    rock.getScalePtr()->x = 0.45f;
    rock.getScalePtr()->y = 0.45f;
    rock.getTranslationPtr()->x = -1.1f;
    rock.getTranslationPtr()->y = -0.2f;

    paper.getScalePtr()->x = 0.45f;
    paper.getScalePtr()->y = 0.45f;
    paper.getTranslationPtr()->y = -0.2f;

    scissor.getScalePtr()->x = 0.45f;
    scissor.getScalePtr()->y = 0.45f;
    scissor.getTranslationPtr()->x = 1.1f;
    scissor.getTranslationPtr()->y = -0.2f;

    selectp1.getScalePtr()->x = 0.45f;
    selectp1.getScalePtr()->y = 0.45f;
    selectp1.getTranslationPtr()->x = -1.1f;
    selectp1.getTranslationPtr()->y = 0.6f;

    selectp2.getScalePtr()->x = 0.45f;
    selectp2.getScalePtr()->y = 0.45f;
    selectp2.getTranslationPtr()->x = -1.1f;
    selectp2.getTranslationPtr()->y = 0.6f;

    winp1.getScalePtr()->x = 0.75f;
    winp1.getScalePtr()->y = 0.75f;
    winp1.getTranslationPtr()->x = -1.0f;

    losep1.getScalePtr()->x = 0.75f;
    losep1.getScalePtr()->y = 0.75f;
    losep1.getTranslationPtr()->x = -1.0f;

    winp2.getScalePtr()->x = 0.75f;
    winp2.getScalePtr()->y = 0.75f;
    winp2.getTranslationPtr()->x = 1.0f;

    losep2.getScalePtr()->x = 0.75f;
    losep2.getScalePtr()->y = 0.75f;
    losep2.getTranslationPtr()->x = 1.0f;

    const int board[3][3];
    const int PHASE_1_PLAYER1_SELECT = 1;
    const int PHASE_2_PLAYER2_SELECT = 2;
    const int PHASE_3_RESULTS = 3;
    bool player1Win = true;
    bool player1Turn = true;
    int time = 0;
    int selectedIndexP1 = 0;
    int selectedIndexP2 = 0;
    int phase = PHASE_1_PLAYER1_SELECT;
    bool isPressed = false;

    Camera camera(70,800.0f/600.0f,0.01f,100.0f,0,0,3);
    camera.updateCamera();

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(!isPressed){
                if(phase==PHASE_1_PLAYER1_SELECT&&selectedIndexP1-1>=0){
                    selectedIndexP1--;
                    selectp1.getTranslationPtr()->x -= 1.1f;
                }else if(phase==PHASE_2_PLAYER2_SELECT&&selectedIndexP2-1>=0){
                    selectedIndexP2--;
                    selectp2.getTranslationPtr()->x -= 1.1f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(!isPressed){
                if(phase==PHASE_1_PLAYER1_SELECT&&selectedIndexP1+1<=2){
                    selectedIndexP1++;
                    selectp1.getTranslationPtr()->x += 1.1f;
                }else if(phase==PHASE_2_PLAYER2_SELECT&&selectedIndexP2+1<=2){
                    selectedIndexP2++;
                    selectp2.getTranslationPtr()->x += 1.1f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(!isPressed){
                if(phase==PHASE_1_PLAYER1_SELECT){
                    phase = PHASE_2_PLAYER2_SELECT;
                }else if(phase==PHASE_2_PLAYER2_SELECT){
                    phase = PHASE_3_RESULTS;
                    player1Win = selectedIndexP1==selectedIndexP2+1 ||selectedIndexP1==selectedIndexP2-2;
                    time = 0;
                }//end else
                isPressed = true;
            }//end if
        }else{
            if(isPressed){
                isPressed = false;
            }//end if
        }//end else

        if(phase == PHASE_3_RESULTS){
            time++;
            if(time > 120){
                time = 0;
                selectedIndexP1 = selectedIndexP2 = 0;
                selectp1.getTranslationPtr()->x = -1.1f;
                selectp2.getTranslationPtr()->x = -1.1f;
                phase = PHASE_1_PLAYER1_SELECT;
            }//end if
        }//end if

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        switch(phase){
            case PHASE_1_PLAYER1_SELECT:{
                rock.draw(camera.getProjection());
                paper.draw(camera.getProjection());
                scissor.draw(camera.getProjection());
                selectp1.draw(camera.getProjection());
            }break;
            case PHASE_2_PLAYER2_SELECT:{
                rock.draw(camera.getProjection());
                paper.draw(camera.getProjection());
                scissor.draw(camera.getProjection());
                selectp2.draw(camera.getProjection());
            }break;
            case PHASE_3_RESULTS:{
                if(player1Win){
                    winp1.draw(camera.getProjection());
                    losep2.draw(camera.getProjection());
                }else{
                    losep1.draw(camera.getProjection());
                    winp2.draw(camera.getProjection());
                }//end else
            }break;
        }//end switch

        window.display();

        sf::sleep(sf::milliseconds(TIME_PER_FRAME-
            clock.getElapsedTime().asMilliseconds()));
        clock.restart();
    }//end while
    return 0;
}//end func
