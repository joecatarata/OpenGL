#ifndef OBJECT_TEXTURE_H
#define OBJECT_TEXTURE_H

#include <string>
#include "SplitModelTX.h"
#include "SplitShaderTX.h"

class ObjTexture{
    public:
        ObjTexture();
        ObjTexture(std::string tf);
        void init(std::string tf);
        
        float getX();
        float getY();
        float getWidth();
        float getHeight();
        
        glm::vec3* getTranslationPtr();
        glm::vec3* getRotationPtr();
        glm::vec3* getScalePtr();
        
        void draw();
        void draw(glm::mat4 camera);
    private:
        SplitModelTX model;
        SplitShaderTX shader;
};

#endif /* OBJECT_TEXTURE_H */
