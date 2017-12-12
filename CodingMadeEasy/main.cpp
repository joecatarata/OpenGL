#include <SFML/Graphics.hpp>
#include <iostream>
//compiling with sfml
//g++ -DSFML_STATIC main.cpp -o main.exe -IC:/sfml/include -LC:/sfml/lib -lopengl32 -lglu32 -lsfml-graphics -lsfml-window -lsfml-system
//compling with sfml and glew
//g++ -DGLEW_STATIC -DSFML_STATIC Shader.cpp gwx.cpp -o main.exe -IC:/glew/include -LC:/glew/lib -IC:/sfml/include -LC:/sfml/lib -IC:/glm -lsfml-window -lsfml-graphics -lsfml-system -lglew32 -lopengl32 -lglu32

int main()
{
	sf::RenderWindow Window(sf::VideoMode(1024,768), "Sample Game");

	sf::Vector2u size(400,400);
	std::cout << size.x << " " << size.y << std::endl;

	Window.setSize(size);
	Window.setTitle("Lol not sample game");
	Window.setPosition(sf::Vector2i(200,100));


	//event loop
	while(Window.isOpen())
	{
		sf::Event Event;
		while(Window.pollEvent(Event)){
			//if the window is closed
			if(Event.type == sf::Event::Closed){
				Window.close();
			}
		}
		Window.display();
	}
	
}