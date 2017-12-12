/**
Linux
g++ *.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ *.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe
*/

//updated compile 
// g++ *.cpp -o run.exe -IC:/sfml/include -LC:/sfml/lib -lsfml-system -lsfml-network -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 
// && run.exe
#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "ObjTexture.h"
#include "Camera.h"
#include <vector>
bool checkWinner(int board[3][3]){
    bool winner = false;
    if((board[0][0]==board[0][1] && board[0][1] == board[0][2]) 
        ||(board[1][0]==board[1][1] && board[1][1] == board[1][2])
        || (board[2][0]==board[2][1] && board[2][1] == board[2][2]) 
        || (board[0][0] == board[1][0] && board[1][0] == board[2][0])
        || (board[0][1] == board[1][1] && board[1][1] == board[2][1])
        || (board[0][2] == board[1][2] && board[1][2] == board[2][2])
        || (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        || (board[0][2] == board[1][1] && board[1][1] == board[2][0])){
        return true;
    } 
    else{
        return false;
    }

}   

bool checkDraw(int board[3][3]){
    bool isDraw = true;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(board[i][j] > 1 ){
                isDraw = false;
            }
        }
    }
    return isDraw;
}

void nextTurn(int *turn){
    *turn = (*turn+1)%2;
}

void initBoard(int board[3][3]){
    int count = 0;
    for(int i=0; i<3;i++){
        for(int j=0; j<3; j++){
           board[i][j] = 2+count;
           count++;    
        }

    }
}
void printboard(int board[3][3]){
    for(int i=0; i<3;i++){
        for(int j=0; j<3; j++){
            std::cout << board[i][j];
        }
        std::cout << std::endl;
    }
}

int main(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    sf::Window window(sf::VideoMode(800, 600), "Tic-Tac-Toe", sf::Style::Default, settings);
    window.setPosition(sf::Vector2i(0,0));

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cout << "ERROR" << std::endl;


    int board[3][3];
    initBoard(board);
    int currXindex = 0;
    int currYindex = 1;     
    int turn=0;     
    bool winner;
    std::vector<ObjTexture> p1Tiles;
    p1Tiles.resize(5);
    int p1TilesIndex=-1;
    std::vector<ObjTexture> p2Tiles;
    p2Tiles.resize(5);
    int p2TilesIndex=-1;
    ObjTexture selectp1("./imgs/corporal-p1.png");
    ObjTexture selectp2("./imgs/corporal-p2.png");

    // ObjTexture p1Tile1("./imgs/corporal-p1.png");
    // ObjTexture p1Tile2("./imgs/corporal-p1.png");
    // ObjTexture p1Tile3("./imgs/corporal-p1.png");
    // ObjTexture p1Tile4("./imgs/corporal-p1.png");
    // ObjTexture p1Tile5("./imgs/corporal-p1.png");
    // ObjTexture selectp2("./imgs/corporal-p2.png");
    ObjTexture winp1("./imgs/corporal-p1.png");
    ObjTexture winp2("./imgs/corporal-p2.png");
    ObjTexture drawImg("./imgs/draw.png");
    // ObjTexture losep1("./imgs/thumb-down-p1.png");
    // ObjTexture losep2("./imgs/thumb-down-p2.png");
    drawImg.getScalePtr()->x = 0.5f;
    drawImg.getScalePtr()->y = 0.5f;    
    drawImg.getTranslationPtr()->x = 0.0f;
    drawImg.getTranslationPtr()->y = 0.0f;
    selectp1.getScalePtr()->x = 0.2f;
    selectp1.getScalePtr()->y = 0.2f;
    selectp1.getTranslationPtr()->x = -1.1f;
    selectp1.getTranslationPtr()->y = 0.0f;

    selectp2.getScalePtr()->x = 0.2f;
    selectp2.getScalePtr()->y = 0.2f;
    selectp2.getTranslationPtr()->x = -1.1f;
    selectp2.getTranslationPtr()->y = 0.0f;
    // selectp1.getScalePtr()->x = 0.45f;
    // selectp1.getScalePtr()->y = 0.45f;
    // selectp1.getTranslationPtr()->x = -1.1f;
    // selectp1.getTranslationPtr()->y = 0.6f;

    // selectp2.getScalePtr()->x = 0.45f;
    // selectp2.getScalePtr()->y = 0.45f;
    // selectp2.getTranslationPtr()->x = -1.1f;
    // selectp2.getTranslationPtr()->y = 0.6f;

    winp1.getScalePtr()->x = 0.75f;
    winp1.getScalePtr()->y = 0.75f;
    winp1.getTranslationPtr()->x = 0.0f;

    // losep1.getScalePtr()->x = 0.75f;
    // losep1.getScalePtr()->y = 0.75f;
    // losep1.getTranslationPtr()->x = -1.0f;

    winp2.getScalePtr()->x = 0.75f;
    winp2.getScalePtr()->y = 0.75f;
    winp2.getTranslationPtr()->x = 0.0f;

    // losep2.getScalePtr()->x = 0.75f;
    // losep2.getScalePtr()->y = 0.75f;
    // losep2.getTranslationPtr()->x = 1.0f;

    const int PHASE_1_PLAYER1_SELECT = 1;
    const int PHASE_2_PLAYER2_SELECT = 2;
    const int PHASE_3_RESULTS = 3;
    bool player1Win = false;
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
                if(turn==0&&currXindex-1>=0){
                    currXindex--;
                    selectp1.getTranslationPtr()->x -= 1.1f;
                }else if(turn==1&&currXindex-1>=0){
                    currXindex--;
                    selectp2.getTranslationPtr()->x -= 1.1f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(!isPressed){
                if(turn==0&&currXindex+1<=2){
                    currXindex++;
                    selectp1.getTranslationPtr()->x += 1.1f;
                }else if(turn==1&&currXindex+1<=2){
                    currXindex++;
                    selectp2.getTranslationPtr()->x += 1.1f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if(!isPressed){
                if(turn==0&&currYindex-1>=0){
                    currYindex--;
                    selectp1.getTranslationPtr()->y += 1.0f;
                }else if(turn==1&&currYindex-1>=0){
                    currYindex--;
                    selectp2.getTranslationPtr()->y += 1.0f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if(!isPressed){
                if(turn==0&&currYindex+1<=2){
                    currYindex++;
                    selectp1.getTranslationPtr()->y -= 1.0f;
                }else if(turn==1&&currYindex+1<=2){
                    currYindex++;
                    selectp2.getTranslationPtr()->y -= 1.0f;
                }//end else
                isPressed = true;
            }//end if
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if(!isPressed){
                if(board[currYindex][currXindex]==0 || board[currYindex][currXindex]==1){
                    continue;
                }
                board[currYindex][currXindex] = turn;
                //reset indices and translations
                currYindex = 1;
                currXindex = 0;
                if(turn==0){
                    p1TilesIndex++;
                    p1Tiles[p1TilesIndex].init("./imgs/corporal-p1.png");
                    p1Tiles[p1TilesIndex].getScalePtr()->x=0.3f;
                    p1Tiles[p1TilesIndex].getScalePtr()->y=0.3f;
                    p1Tiles[p1TilesIndex].getTranslationPtr()->x=selectp1.getTranslationPtr()->x;
                    p1Tiles[p1TilesIndex].getTranslationPtr()->y=selectp1.getTranslationPtr()->y;
                }
                else if(turn==1)
                {
                    p2TilesIndex++;
                    p2Tiles[p2TilesIndex].init("./imgs/corporal-p2.png");
                    p2Tiles[p2TilesIndex].getScalePtr()->x=0.3f;
                    p2Tiles[p2TilesIndex].getScalePtr()->y=0.3f;
                    p2Tiles[p2TilesIndex].getTranslationPtr()->x=selectp2.getTranslationPtr()->x;
                    p2Tiles[p2TilesIndex].getTranslationPtr()->y=selectp2.getTranslationPtr()->y;
                }
                selectp1.getTranslationPtr()->x = -1.1f;
                selectp2.getTranslationPtr()->x = -1.1f;
                selectp1.getTranslationPtr()->y = 0.0f;
                selectp2.getTranslationPtr()->y = 0.0f;
                isPressed = true;

                
                printboard(board);                
                if(checkWinner(board)==true){
                    if(turn==0)
                        player1Win=true;
                    if(turn==1)
                        player1Win=false;

                    //std::cout<< "Winner! Player: " << (turn+1);
                    phase = PHASE_3_RESULTS;
                }
                if(checkDraw(board)==true){
                    phase = PHASE_3_RESULTS;
                    //std::cout<< "Draw!";
                }
                nextTurn(&turn);
            }//end if
        }else{
            if(isPressed){
                isPressed = false;
            }//end if
        }//end else 

        if(phase == PHASE_3_RESULTS){
            time++;
            if(time > 120){
                //reset
                time = 0;
                selectedIndexP1 = selectedIndexP2 = 0;
                selectp1.getTranslationPtr()->x = -1.1f;
                selectp1.getTranslationPtr()->y = 0.0f;
                selectp2.getTranslationPtr()->x = -1.1f;
                selectp2.getTranslationPtr()->y = 0.0f;
                initBoard(board);
                currYindex=1;
                currXindex=0;
                p1Tiles.clear();
                p1Tiles.resize(5);
                p2Tiles.clear();
                p2Tiles.resize(5);
                p1TilesIndex=-1;
                p2TilesIndex=-1;
                phase = 0;
                turn = 0;

            }//end if
        }//end if

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        if(!checkWinner(board) && checkDraw(board) == false){

            switch(turn){
                case 0: selectp1.draw(camera.getProjection()); break;
                case 1: selectp2.draw(camera.getProjection()); break;        
            }

            if(p1TilesIndex>=0){
                for(int i=0; i<=p1TilesIndex; i++){
                    p1Tiles[i].draw(camera.getProjection());
                }
            }
            if(p2TilesIndex>=0){
                for(int i=0; i<=p2TilesIndex; i++){
                    p2Tiles[i].draw(camera.getProjection());
                }
            }
        }else if(checkWinner(board)){
            
            if(player1Win == true){
                winp1.draw(camera.getProjection()); 
            }
            else if(player1Win == false){
                winp2.draw(camera.getProjection());
            }
        }
        if(checkDraw(board)==true){
            drawImg.draw(camera.getProjection());
        }
        window.display();

        sf::sleep(sf::milliseconds(TIME_PER_FRAME-
            clock.getElapsedTime().asMilliseconds()));
        clock.restart();
    }//end while
    return 0;
}//end func
