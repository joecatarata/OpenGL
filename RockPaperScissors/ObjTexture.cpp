#include "ObjTexture.h"

ObjTexture::ObjTexture(){}

ObjTexture::ObjTexture(std::string tf){
    init(tf);
}
void ObjTexture::init(std::string tf){
    GLfloat points[] = {
       -1.0f, -1.0f, 0.0f,//lower left
        1.0f, -1.0f, 0.0f,//lower right
       -1.0f,  1.0f, 0.0f,//upper left
        
        1.0f, -1.0f, 0.0f,//lower right
       -1.0f,  1.0f, 0.0f,//upper left
        1.0f,  1.0f, 0.0f,//upper right
    };

    //upper left is 0,0
    //lower right is 1,1
    GLfloat texturePoints[] = {
        0.0f,  1.0f,//lower left
        1.0f,  1.0f,//lower right
        0.0f,  0.0f,//upper left
        
        1.0f,  1.0f,//lower right
        0.0f,  0.0f,//upper left
        1.0f,  0.0f,//upper right
    };
    std::string vs = "shader/basicShaderTX.vs";
    std::string fs = "shader/basicShaderTX.fs";

    model.init(points, texturePoints, sizeof(points), tf);
    shader.init(vs, fs);
}

float ObjTexture::getX(){
    return model.getTranslationPtr()->x - getWidth()/2;
}
float ObjTexture::getY(){
    return model.getTranslationPtr()->y - getHeight()/2;
}
float ObjTexture::getWidth(){
    return 2*model.getScalePtr()->x;
}
float ObjTexture::getHeight(){
    return 2*model.getScalePtr()->y;
}

glm::vec3* ObjTexture::getTranslationPtr(){
    return model.getTranslationPtr();
}
glm::vec3* ObjTexture::getRotationPtr(){
    return model.getRotationPtr();
}
glm::vec3* ObjTexture::getScalePtr(){
    return model.getScalePtr();
}

void ObjTexture::draw(){
    shader.bind(model.getTransformationModel());
    model.draw();
}

void ObjTexture::draw(glm::mat4 camera){
    shader.bindCamera(camera, model.getTransformationModel());
    model.draw();
}
