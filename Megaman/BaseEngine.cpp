#include "BaseEngine.h"

BaseEngine::BaseEngine(){
	
}
void BaseEngine::startGame(){
	sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(800, 600), "MMBN", sf::Style::Default, settings);
    window.setPosition(sf::Vector2i(0,0));

    GLenum status = glewInit();
    if(status != GLEW_OK)
        std::cout << "ERROR" << std::endl;
	
    Camera camera(70,800.0f/600.0f,0.01f,100.0f,0,0,3);
    camera.updateCamera();

	init();
	
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
		update();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        render(camera);
        window.display();

        //regulates the frames to 60
        sf::sleep(sf::milliseconds(TIME_PER_FRAME-
            clock.getElapsedTime().asMilliseconds()));
        clock.restart();
    }//end while
	
}