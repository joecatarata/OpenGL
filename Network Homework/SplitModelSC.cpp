#include "SplitModelSC.h"

const glm::vec3 SplitModelSC::X_ROT_MATRIX = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 SplitModelSC::Y_ROT_MATRIX = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 SplitModelSC::Z_ROT_MATRIX = glm::vec3(0.0, 0.0, 1.0);

SplitModelSC::SplitModelSC(){
}

SplitModelSC::SplitModelSC(GLfloat points[],int size, int r,int g, int b){
    init(points,size,r,g,b);
}

void SplitModelSC::init(GLfloat points[],int size, int r,int g, int b){
    GLfloat colors[size];
    for(int i=0;i<size;i+=3){
        colors[i] = r;
        colors[i+1] = g;
        colors[i+2] = b;
    }

    //ID used to indicate what to use
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    //create the needed buffers
    glGenBuffers(2, &all_buffers[0]);

    //connect the positions to the second part of the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, all_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    //enable the first buffer to be used
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    //connect the colors to the second part of the vertex array
    glBindBuffer(GL_ARRAY_BUFFER, all_buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, size, colors, GL_STATIC_DRAW);

    //enable the second buffer to be used
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,0);

    //once all has been saved, close the vertex array's bindings
    glBindVertexArray(0);

    arraySize = size/(sizeof(GLfloat)*3);

    translation.x = translation.y = translation.z = 0;
    rotation.x = rotation.y = rotation.z = 0;
    scale.x = scale.y = scale.z = 1;
}

SplitModelSC::~SplitModelSC(){
    glDeleteVertexArrays(1, &vertexArrayID);
}

glm::vec3* SplitModelSC::getTranslationPtr(){ return &translation; }
glm::vec3* SplitModelSC::getRotationPtr(){ return &rotation; }
glm::vec3* SplitModelSC::getScalePtr(){ return &scale; }

glm::mat4 SplitModelSC::getTransformationModel(){ 
    return glm::translate(translation) * /* translation */
        (glm::rotate(rotation.x, X_ROT_MATRIX) * /* rotation */
            glm::rotate(rotation.y, Y_ROT_MATRIX) *
            glm::rotate(rotation.z, Z_ROT_MATRIX)) *
        glm::scale(scale); /* scale */
}

void SplitModelSC::draw(){
    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,arraySize);
    glBindVertexArray(0);
}
