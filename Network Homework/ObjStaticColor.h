#ifndef OBJECT_SAMPLE_H
#define OBJECT_SAMPLE_H

#include <string>
#include "SplitModelSC.h"
#include "SplitShaderSC.h"

class ObjStaticColor{
    public:
        ObjStaticColor();
        
        glm::vec3* getTranslationPtr();
        glm::vec3* getRotationPtr();
        glm::vec3* getScalePtr();
        
        float getX();
        float getY();
        float getWidth();
        float getHeight();
        
        void draw();
        void draw(glm::mat4 camera);
    private:
        SplitModelSC model;
        SplitShaderSC shader;
};

#endif /* OBJECT_SAMPLE_H */
