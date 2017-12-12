#include "ObjDynamicColor.h"

ObjDynamicColor::ObjDynamicColor(){
    GLfloat points[] = {
       -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
       -1.0f,  1.0f, 0.0f,
        
        1.0f, -1.0f, 0.0f,
       -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };
    r = g = b = 0;
    std::string vs = "shader/basicShaderDC.vs";
    std::string fs = "shader/basicShaderDC.fs";

    model.init(points, sizeof(points));
    shader.init(vs, fs);
}

float ObjDynamicColor::getX(){
    return model.getTranslationPtr()->x - getWidth()/2;
}
float ObjDynamicColor::getY(){
    return model.getTranslationPtr()->y - getHeight()/2;
}
float ObjDynamicColor::getWidth(){
    return 2*model.getScalePtr()->x;
}
float ObjDynamicColor::getHeight(){
    return 2*model.getScalePtr()->y;
}

glm::vec3* ObjDynamicColor::getTranslationPtr(){
    return model.getTranslationPtr();
}
glm::vec3* ObjDynamicColor::getRotationPtr(){
    return model.getRotationPtr();
 }
glm::vec3* ObjDynamicColor::getScalePtr(){
    return model.getScalePtr();
}

void ObjDynamicColor::setColor(float rV,float gV,float bV){
    r = rV;
    g = gV;
    b = bV;
}

void ObjDynamicColor::draw(){
    shader.bind(model.getTransformationModel(),r,g,b);
    model.draw();
}

void ObjDynamicColor::draw(glm::mat4 camera){
    shader.bindCamera(camera, model.getTransformationModel(),r,g,b);
    model.draw();
}
