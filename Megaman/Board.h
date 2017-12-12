#ifndef BOARD_H
#define BOARD_H

#include <glm/glm.hpp>
#include <vector>
#include <fstream>
#include "Camera.h"
#include "AbsObject.h"

class Board{
	public:
	Board();	
	void init();
	~Board();
	void draw(glm::mat4 camera);
	char charAt(int x,int y);	
};
#endif