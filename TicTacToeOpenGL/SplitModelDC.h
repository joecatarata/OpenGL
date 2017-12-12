#ifndef SPLIT_MODEL_DC_H
#define SPLIT_MODEL_DC_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class SplitModelDC{
    public:
        SplitModelDC();
        SplitModelDC(GLfloat points[],int size);
        void init(GLfloat points[],int size);
        ~SplitModelDC();

        glm::vec3* getTranslationPtr();
        glm::vec3* getRotationPtr();
        glm::vec3* getScalePtr();

        glm::mat4 getTransformationModel();
        void draw();
    private:
        glm::vec3 translation, rotation, scale;
        const static glm::vec3 X_ROT_MATRIX, Y_ROT_MATRIX, Z_ROT_MATRIX;

        GLuint vertexArrayID;
        GLuint positionBuffer;
        int arraySize;
};

#endif /* SPLIT_MODEL_DC_H */
