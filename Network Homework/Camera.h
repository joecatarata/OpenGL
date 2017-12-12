#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

class Camera{
    public:
	    Camera(float fieldOfView, float aspectRatio, float zNear, float zFar,
            float xPos, float yPos, float zPos);
        void updateCamera();
        glm::mat4 getProjection();
    private:
        glm::mat4 cameraModel, perspective;
        glm::vec3 position, forward, upDirection;
};

#endif /* CAMERA_H */
