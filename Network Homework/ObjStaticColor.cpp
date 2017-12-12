#include "ObjStaticColor.h"

ObjStaticColor::ObjStaticColor(){
    GLfloat points[] = {
       -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
       -1.0f,  1.0f, 0.0f,
        
        1.0f, -1.0f, 0.0f,
       -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };
    std::string vs = "shader/basicShaderSC.vs";
    std::string fs = "shader/basicShaderSC.fs";

    model.init(points, sizeof(points),1,0,1);
    shader.init(vs, fs);
}

float ObjStaticColor::getX(){
    return model.getTranslationPtr()->x - getWidth()/2;
}
float ObjStaticColor::getY(){
    return model.getTranslationPtr()->y - getHeight()/2;
}
float ObjStaticColor::getWidth(){
    return 2*model.getScalePtr()->x;
}
float ObjStaticColor::getHeight(){
    return 2*model.getScalePtr()->y;
}

glm::vec3* ObjStaticColor::getTranslationPtr(){
    return model.getTranslationPtr();
}
glm::vec3* ObjStaticColor::getRotationPtr(){
    return model.getRotationPtr();
}
glm::vec3* ObjStaticColor::getScalePtr(){
    return model.getScalePtr();
}

void ObjStaticColor::draw(){
    shader.bind(model.getTransformationModel());
    model.draw();
}

void ObjStaticColor::draw(glm::mat4 camera){
    shader.bindCamera(camera, model.getTransformationModel());
    model.draw();
}
