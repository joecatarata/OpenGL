/**
Linux
g++ AbsObject.cpp Camera.cpp BaseEngine.cpp main.cpp -o run.exe -lGL -lGLEW -lsfml-graphics -lsfml-window -lsfml-system && ./run.exe

Windows
g++ AbsObject.cpp Camera.cpp BaseEngine.cpp main.cpp -o run.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32 && run.exe

Start Window
*/
#include <iostream>
#include "AbsObject.h"
#include "BaseEngine.h"
#include <stdlib.h>
#include <time.h>
class MyGame: public BaseEngine{	
	public:	
		bool shot = false;
		int bulletSize;
		AbsObject bullets[6];
		void init(){
			float tileSize = .15f;
			
			GLfloat points[] = {
				-0.5f, 0.5f, 0.0f,
				-0.5f,-0.5f, 0.0f,
				0.5f,-0.5f, 0.0f,
       
				-0.5f, 0.5f, 0.0f,
				0.5f,-0.5f, 0.0f,
				0.5f, 0.5f, 0.0f,
			};			
			
			for(int i=0;i<3;i++){
				for(int j=0;j<6;j++){
					if(i%2==0&&j%2==0 || i%2==1&&j%2==1)
						object[i][j].init(points,sizeof(points),1,1,1);
					else
						object[i][j].init(points,sizeof(points),.5,.5,.5);
					
					object[i][j].getScalePtr()->x = tileSize;
					object[i][j].getScalePtr()->y = tileSize;
					object[i][j].getTranslationPtr()->y = i*tileSize - tileSize*5;
					object[i][j].getTranslationPtr()->x = j*tileSize - tileSize*5;
					}
			}
			srand(time(NULL));
			for (int i=0;i<6;i++)
			{
				HPBar[i].init(points,sizeof(points),0,1,0);
				HPBar[i].getScalePtr()->x = tileSize;
				HPBar[i].getScalePtr()->y = tileSize;
				
				HPBar[i].getTranslationPtr()->y = -1.0f;
				HPBar[i].getTranslationPtr()->x = i*tileSize - tileSize*5;
			}		

			for (int i=0;i<6;i++)
			{
				EnemyHP[i].init(points,sizeof(points),1,0,0);
				EnemyHP[i].getScalePtr()->x = tileSize;
				EnemyHP[i].getScalePtr()->y = tileSize;
				
				EnemyHP[i].getTranslationPtr()->y = -0.3f;
				EnemyHP[i].getTranslationPtr()->x = i*tileSize - tileSize*5;
			}					
			player.init(points,sizeof(points),1,0,0);		
			player.getScalePtr()->x = tileSize;
			player.getScalePtr()->y = tileSize;
			player.getTranslationPtr()->y = -tileSize*5;
			player.getTranslationPtr()->x = -tileSize*5;
			
			Enemy.init(points,sizeof(points),1,1,0);		
			Enemy.getScalePtr()->x = tileSize;
			Enemy.getScalePtr()->y = tileSize;
// 			Enemy.getTranslationPtr()->y = -tileSize*5;
// //			Enemy.getTranslationPtr()->x = (-tileSize*5) + (tileSize * 3);
// 			Enemy.getTranslationPtr()->x = (tileSize * -1);

			 isPressed = false;

			 //Generates random x and y index for the enemy.
			Ex = rand() % (5 + 1 - 3) + 3; 
			Ey = rand() % (2 + 1 - 0) + 0;
			Enemy.getTranslationPtr()->x = Ex*tileSize - tileSize*5;
			Enemy.getTranslationPtr()->y = (Ey*tileSize - tileSize*5);
			std::cout << Ex << Ey;
		}
		//rand() % (max_number + 1 - minimum_number) + minimum_number
		void update(){	
			float tileSize = .15f;

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
				if(!isPressed && Py+1 < 3)
				{
					player.getTranslationPtr()->y += .15f;
					Py++;
					isPressed = true;
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
				if(!isPressed && Py-1 >= 0)
				{                
					player.getTranslationPtr()->y -= .15f;
					Py--;					
					isPressed = true;
				}
			}
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				if(!isPressed && Px-1 >= 0)
				{					
					player.getTranslationPtr()->x -= .15f;
					Px--;					
					isPressed = true;
				}
			}	
			else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				if(!isPressed && Px+1 < 3)
				{					
					player.getTranslationPtr()->x += .15f;
					Px++;					
					isPressed = true;
				}
        	}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				if(!isPressed)
				{		
						GLfloat points[] = {
						-0.5f, 0.5f, 0.0f,
						-0.5f,-0.5f, 0.0f,
						0.5f,-0.5f, 0.0f,
		       
						-0.5f, 0.5f, 0.0f,
						0.5f,-0.5f, 0.0f,
						0.5f, 0.5f, 0.0f,
					};				
					int tempX = Px+1;
					bulletSize = 6-Px;
					bullets[bulletSize];
					int ctr = 0;
					while(tempX < 6){
						bullets[ctr].init(points, sizeof(points),1,1,0);
						bullets[ctr].getScalePtr()->x = tileSize;
						bullets[ctr].getScalePtr()->y = tileSize;
						bullets[ctr].getTranslationPtr()->y = Py*tileSize - tileSize*5;
						bullets[ctr].getTranslationPtr()->x = tempX*tileSize - tileSize*5	;
						tempX++;
						ctr++;
					}
					shot = true;

					if(Ey == Py){
						eHpNum--;
					}

				}
			}
        	else if(isPressed){
	            isPressed = false;
	            Ex = rand() % (5 + 1 - 3) + 3;
				Ey = rand() % (2 + 1 - 0) + 0;
				Enemy.getTranslationPtr()->x = Ex*tileSize - tileSize*5;
				Enemy.getTranslationPtr()->y = (Ey*tileSize - tileSize*5);
			}				
			//std::cout<< isPressed << std::endl;
			
	}
		
		
		void render(Camera camera){				
			
			for(int i=0;i<3;i++)
				 for(int j=0;j<6;j++)
					object[i][j].draw(camera.getProjection());
				
			player.draw(camera.getProjection());
			Enemy.draw(camera.getProjection());
			
			if(shot){
				for(int i=0;i<bulletSize;i++)
					bullets[i].draw(camera.getProjection());

				shot=false;
			}

			for(int i=0;i<6;i++)
			{
				HPBar[i].draw(camera.getProjection());
			}

			//Draws enemy hp
			for(int i=0;i<eHpNum;i++)
			{
				EnemyHP[i].draw(camera.getProjection());
			}
			
		}
	private:
		int Px = 0;
		int Py = 0;
		
		int Ex;
		int Ey;
		AbsObject HPBar[6];
		AbsObject Enemy;

		//The graphics of the hp bar of the enemy
		AbsObject EnemyHP[6];
		// Value of hp bar of enemy
		int eHpNum = 6;

		AbsObject player;
		AbsObject object[3][6];
		bool isPressed;
};

int main(){
    MyGame game;
	game.startGame();
    return 0;
}//end func