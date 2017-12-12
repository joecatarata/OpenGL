#ifndef ABS_OBJECT_H
#define ABS_OBJECT_H

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class AbsObject{
    public:
        AbsObject();
        AbsObject(GLfloat points[],int size, float r, float g, float b);
        void init(GLfloat points[],int size, float r, float g, float b);
        ~AbsObject();

        glm::vec3* getTranslationPtr();
        glm::vec3* getRotationPtr();
        glm::vec3* getScalePtr();

        glm::mat4 getTransformationModel();

        void draw();
        void draw(glm::mat4 camera);
        bool teleportTile = false;
        int partnerXpos = -1;
        int partnerYpos = -1;
        float partnerTransX;
        float partnerTransY;

    private:
        glm::vec3 translation, rotation, scale;
        const static glm::vec3 X_ROT_MATRIX, Y_ROT_MATRIX, Z_ROT_MATRIX;

        GLuint vertexArrayID;
        GLuint positionBuffer;
        GLuint uniformTransform;
        int arraySize;
        GLuint shader;
        GLuint vertexShader;
        GLuint fragmentShader;
};

#endif /* ABS_OBJECT_H */
