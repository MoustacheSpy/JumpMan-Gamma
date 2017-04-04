#include <JUMA_camera.h>

JUMA_Camera::JUMA_Camera(float fov,float clippingBack,float clippingFront,int windowx,int windowy){
    proj = glm::perspective(this->fov = fov, (float)windowx / (float)windowy, this->clippingFront=clippingFront, this->clippingBack=clippingBack);
}
JUMA_Camera::JUMA_Camera(float x,float y,float z,float fov,float clippingBack,float clippingFront,int windowx,int windowy){
    proj = glm::perspective(this->fov = fov, (float)windowx / (float)windowy, this->clippingFront=clippingFront, this->clippingBack=clippingBack);
    transform.setPos(x,y,z);
}
glm::mat4 JUMA_Camera::getView(){
    return transform.getMat();
}
glm::mat4 JUMA_Camera::getProj(){
    return proj;
}
