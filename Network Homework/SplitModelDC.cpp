#include "SplitModelDC.h"

const glm::vec3 SplitModelDC::X_ROT_MATRIX = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 SplitModelDC::Y_ROT_MATRIX = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 SplitModelDC::Z_ROT_MATRIX = glm::vec3(0.0, 0.0, 1.0);

SplitModelDC::SplitModelDC(){
}

SplitModelDC::SplitModelDC(GLfloat points[],int size){
    init(points,size);
}

void SplitModelDC::init(GLfloat points[],int size){
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glBindVertexArray(0);

    arraySize = size/(sizeof(GLfloat)*3);

    translation.x = translation.y = translation.z = 0;
    rotation.x = rotation.y = rotation.z = 0;
    scale.x = scale.y = scale.z = 1;
}

SplitModelDC::~SplitModelDC(){
    glDeleteVertexArrays(1, &vertexArrayID);
}

glm::vec3* SplitModelDC::getTranslationPtr(){ return &translation; }
glm::vec3* SplitModelDC::getRotationPtr(){ return &rotation; }
glm::vec3* SplitModelDC::getScalePtr(){ return &scale; }

glm::mat4 SplitModelDC::getTransformationModel(){ 
    return glm::translate(translation) * /* translation */
        (glm::rotate(rotation.x, X_ROT_MATRIX) * /* rotation */
            glm::rotate(rotation.y, Y_ROT_MATRIX) *
            glm::rotate(rotation.z, Z_ROT_MATRIX)) *
        glm::scale(scale); /* scale */
}

void SplitModelDC::draw(){
    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,arraySize);
    glBindVertexArray(0);
}