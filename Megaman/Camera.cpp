#include "Camera.h"

Camera::Camera(float fieldOfView, float aspectRatio, float zNear, float zFar,
        float xPos, float yPos, float zPos){
    perspective = glm::perspective(fieldOfView, aspectRatio, zNear, zFar);
    position = glm::vec3(xPos, yPos, zPos);
    forward = glm::vec3(0,0,-1);
    upDirection = glm::vec3(0,1,0);
    updateCamera();
}

void Camera::updateCamera(){
    cameraModel = perspective *
        glm::lookAt(position, position + forward, upDirection);
}

glm::mat4 Camera::getProjection(){
    return perspective *
        glm::lookAt(position, position + forward, upDirection);;
}
