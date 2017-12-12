#ifndef SPLIT_SHADER_SC_H
#define SPLIT_SHADER_SC_H

#include <iostream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>
#include <stdio.h>
#include <SFML/Graphics.hpp>

class SplitShaderSC{
    public:
        SplitShaderSC();
        SplitShaderSC(std::string shaderV,std::string shaderF);
        void init(std::string shaderV,std::string shaderF);
        ~SplitShaderSC();

        void bind(glm::mat4 tranModel);
        void bindCamera(glm::mat4 camera,glm::mat4 tranModel);
    private:
        GLuint uniformTransform;
        GLuint uniformColor;

        GLuint shader;
        GLuint vertexShader;
        GLuint fragmentShader;

        std::string getFileContent(std::string fileName);
};

#endif /* SPLIT_SHADER_SC_H */
