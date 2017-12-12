#include "SplitShaderSC.h"

SplitShaderSC::SplitShaderSC(){
}

SplitShaderSC::SplitShaderSC(std::string shaderV,std::string shaderF){
    init(shaderV,shaderF);
}

void SplitShaderSC::init(std::string shaderV,std::string shaderF){
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
    glBindAttribLocation(shader, 1, "color");

    glLinkProgram(shader);
    glValidateProgram(shader);

    uniformTransform = glGetUniformLocation(shader, "transform"); 
}

SplitShaderSC::~SplitShaderSC(){
    glDetachShader(shader, vertexShader);
    glDetachShader(shader, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void SplitShaderSC::bind(glm::mat4 tranModel){
    glUseProgram(shader);
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &tranModel[0][0]);
}

void SplitShaderSC::bindCamera(glm::mat4 camera,glm::mat4 tranModel){
    glUseProgram(shader);
    glm::mat4 trans = camera* tranModel;
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &trans[0][0]);
}

std::string SplitShaderSC::getFileContent(std::string fileName){
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
