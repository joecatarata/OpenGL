#include "SplitShaderDC.h"

SplitShaderDC::SplitShaderDC(){
}

SplitShaderDC::SplitShaderDC(std::string shaderV,std::string shaderF){
    init(shaderV,shaderF);
}

void SplitShaderDC::init(std::string shaderV,std::string shaderF){
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string contentV = getFileContent(shaderV);
    const char* vertexCharData = contentV.c_str();
    glShaderSource(vertexShader, 1, &vertexCharData , NULL);
    glCompileShader(vertexShader);

    std::string contentF = getFileContent(shaderF);
    const char* fragmentCharData = contentF.c_str();
    glShaderSource(fragmentShader, 1, &fragmentCharData , NULL);
    glCompileShader(fragmentShader);

    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);

    glBindAttribLocation(shader, 0, "position");

    glLinkProgram(shader);
    glValidateProgram(shader);

    uniformTransform = glGetUniformLocation(shader, "transform"); 
    uniformColor = glGetUniformLocation(shader, "color"); 
}

SplitShaderDC::~SplitShaderDC(){
    glDetachShader(shader, vertexShader);
    glDetachShader(shader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void SplitShaderDC::bind(glm::mat4 tranModel,float r,float g,float b){
    glUseProgram(shader);
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &tranModel[0][0]);
    glUniform3f(uniformColor,r,g,b);
}

void SplitShaderDC::bindCamera(glm::mat4 camera,glm::mat4 tranModel,float r,float g,float b){
    glUseProgram(shader);
    glm::mat4 trans = camera* tranModel;
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &trans[0][0]);
    glUniform3f(uniformColor,r,g,b);
}

std::string SplitShaderDC::getFileContent(std::string fileName){
    std::string line;
    std::string output = "";
    std::ifstream file (fileName.c_str());
    if(file.is_open()){
        while(getline(file, line)){
            output.append(line);
            output.append("\n");
        }//end while
        file.close();
    }//end if
    return output;
}
