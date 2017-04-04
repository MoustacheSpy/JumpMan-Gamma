#ifndef JUMA_CAMERA_H_INCLUDED
#define JUMA_CAMERA_H_INCLUDED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <JUMA_transform.h>
class JUMA_Camera{
private:
    JUMA_Transform transform;
    glm::mat4 view;
    glm::mat4 proj;
    float fov;
    float clippingBack;
    float clippingFront;
public:
    JUMA_Camera( ){
        proj = view = glm::mat4();
        clippingBack = clippingFront = fov = 0;

    };
    JUMA_Camera(float fov,float clippingBack,float clippingFront,int windowx,int windowy);
    JUMA_Camera(float x,float y,float z,float fov,float clippingBack,float clippingFront,int windowx,int windowy);
    glm::mat4 getView();
    glm::mat4 getProj();
};

#endif // JUMA_CAMERA_H_INCLUDED
