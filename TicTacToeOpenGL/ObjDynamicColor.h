#ifndef OBJ_DYNAMIC_COLOR_H
#define OBJ_DYNAMIC_COLOR_H

#include <string>
#include "SplitModelDC.h"
#include "SplitShaderDC.h"

class ObjDynamicColor{
    public:
        ObjDynamicColor();

        glm::vec3* getTranslationPtr();
        glm::vec3* getRotationPtr();
        glm::vec3* getScalePtr();
        
        void setColor(float rV,float gV,float bV);
        
        float getX();
        float getY();
        float getWidth();
        float getHeight();
        
        void draw();
        void draw(glm::mat4 camera);
    private:
        SplitModelDC model;
        SplitShaderDC shader;
        float r,g,b;
};

#endif /* OBJ_DYNAMIC_COLOR_H */
