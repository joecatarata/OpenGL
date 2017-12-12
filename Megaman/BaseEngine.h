#ifndef BASE_ENGINE_H
#define BASE_ENGINE_H

#include <iostream>
#include <GL/glew.h>
#include <SFML/Window.hpp>
#include "AbsObject.h"
#include "Camera.h"

class BaseEngine{
    public:
		//! constructor for engine
		BaseEngine();
		//! initalizes data used by game
		virtual void init() = 0;
		//! moves objects before drawing
		virtual void update() = 0;
		//! draws things on screen
		virtual void render(Camera camera) = 0;
		//! starts the game itself
		void startGame();
    private:

};

#endif /* BASE_ENGINE_H */
