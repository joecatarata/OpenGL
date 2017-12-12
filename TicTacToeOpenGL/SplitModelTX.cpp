#include "SplitModelTX.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const glm::vec3 SplitModelTX::X_ROT_MATRIX = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 SplitModelTX::Y_ROT_MATRIX = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 SplitModelTX::Z_ROT_MATRIX = glm::vec3(0.0, 0.0, 1.0);

SplitModelTX::SplitModelTX(){
}

SplitModelTX::SplitModelTX(GLfloat points[],GLfloat texturePoints[],int size,std::string textureFile){
    init(points,texturePoints,size,textureFile);
}

void SplitModelTX::init(GLfloat points[],GLfloat texturePoints[],int size,std::string textureFile){
    //ID used to indicate what to use
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glGenBuffers(2, &all_buffers[0]);

    glBindBuffer(GL_ARRAY_BUFFER, all_buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    //the points of the mapping should be loaded into the GPU
    glBindBuffer(GL_ARRAY_BUFFER, all_buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texturePoints[0]) * size,
        &texturePoints[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);

    arraySize = size/(sizeof(GLfloat)*3);

    translation.x = translation.y = translation.z = 0;
    rotation.x = rotation.y = rotation.z = 0;
    scale.x = scale.y = scale.z = 1;

    //The texture image should be loaded on the GPU
    int width, height, numComponents;
    unsigned char* imageData = stbi_load(textureFile.c_str(), &width, &height, &numComponents, 4);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    //optional steps
    //it controlls the texture wrapping
    //if GL_REPEAT, it will repeat when texture is too small
    //if GL_BLANK, it will display black at exceeded areas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //used when the image takes in less than the image
    //GL_LINEAR - linearly interpolate
    //GL_NEAREST - no filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //used when the image takes in more than the image
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

SplitModelTX::~SplitModelTX(){
    glDeleteVertexArrays(1, &vertexArrayID);
    //texture clean-up
    glDeleteTextures(1, &texture);
}

glm::vec3* SplitModelTX::getTranslationPtr(){ return &translation; }
glm::vec3* SplitModelTX::getRotationPtr(){ return &rotation; }
glm::vec3* SplitModelTX::getScalePtr(){ return &scale; }

glm::mat4 SplitModelTX::getTransformationModel(){ 
    return glm::translate(translation) * /* translation */
        (glm::rotate(rotation.x, X_ROT_MATRIX) * /* rotation */
            glm::rotate(rotation.y, Y_ROT_MATRIX) *
            glm::rotate(rotation.z, Z_ROT_MATRIX)) *
        glm::scale(scale); /* scale */
}

void SplitModelTX::draw(){
    //texture part
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //mesh data
    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,arraySize);
    glBindVertexArray(0);
}
