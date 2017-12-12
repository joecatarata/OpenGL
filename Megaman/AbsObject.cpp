#include "AbsObject.h"

const glm::vec3 AbsObject::X_ROT_MATRIX = glm::vec3(1.0, 0.0, 0.0);
const glm::vec3 AbsObject::Y_ROT_MATRIX = glm::vec3(0.0, 1.0, 0.0);
const glm::vec3 AbsObject::Z_ROT_MATRIX = glm::vec3(0.0, 0.0, 1.0);

AbsObject::AbsObject(){
}

AbsObject::AbsObject(GLfloat points[],int size, float r, float g, float b){
    init(points,size,r,g,b);
}

void AbsObject::init(GLfloat points[],int size, float r, float g, float b){
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glBindVertexArray(0);

    arraySize = size/(sizeof(GLfloat)*3);

    const std::string vs = "attribute vec3 position;\nuniform mat4 transform;\n" \
        "void main(){gl_Position = transform * vec4(position, 1.0);}";

    char colorAppend[100];
    sprintf(colorAppend,"%f,%f,%f",r,g,b);
    std::string strColor(colorAppend);

    const std::string fs = "void main(){gl_FragColor = vec4("+strColor+", 1.0);}";

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexCharData = vs.c_str();
 	glShaderSource(vertexShader, 1, &vertexCharData , NULL);
 	glCompileShader(vertexShader);

    const char* fragCharData = fs.c_str();
 	glShaderSource(fragmentShader, 1, &fragCharData , NULL);
 	glCompileShader(fragmentShader);

    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);

	glBindAttribLocation(shader, 0, "position");

	glLinkProgram(shader);
	glValidateProgram(shader);

    uniformTransform = glGetUniformLocation(shader, "transform"); 

    translation.x = translation.y = translation.z = 0;
    rotation.x = rotation.y = rotation.z = 0;
    scale.x = scale.y = scale.z = 1;
}

AbsObject::~AbsObject(){
    glDetachShader(shader, vertexShader);
 	glDetachShader(shader, fragmentShader);
 	glDeleteShader(vertexShader);
 	glDeleteShader(fragmentShader);

    glDeleteVertexArrays(1, &vertexArrayID);
}

glm::vec3* AbsObject::getTranslationPtr(){ return &translation; }
glm::vec3* AbsObject::getRotationPtr(){ return &rotation; }
glm::vec3* AbsObject::getScalePtr(){ return &scale; }

glm::mat4 AbsObject::getTransformationModel(){ 
    return glm::translate(translation) * /* translation */
        (glm::rotate(rotation.x, X_ROT_MATRIX) * /* rotation */
            glm::rotate(rotation.y, Y_ROT_MATRIX) *
            glm::rotate(rotation.z, Z_ROT_MATRIX)) *
        glm::scale(scale); /* scale */
}

void AbsObject::draw(){
    glUseProgram(shader);
    glm::mat4 trans = getTransformationModel();
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &trans[0][0]);

    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,arraySize);
    glBindVertexArray(0);
}

void AbsObject::draw(glm::mat4 camera){
    glUseProgram(shader);
    glm::mat4 trans = camera* getTransformationModel();
    glUniformMatrix4fv(uniformTransform, 1, GL_FALSE, &trans[0][0]);

    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,arraySize);
    glBindVertexArray(0);
}
