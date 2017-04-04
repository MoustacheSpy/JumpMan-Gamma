#ifndef JUMA_TRANSFORM_INCLUDED
#define JUMA_TRANSFORM_INCLUDED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class JUMA_Transform{
private:
    glm::vec3 rotation = { 0.0,0.0,0.0 };
	glm::vec3 position = { 0.0,0.0,0.0 };
	glm::vec3 scale;
public:
    JUMA_Transform(){
        scale = {1.0,1.0,1.0};
    };

	void setPos(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	};
	void translate(float x, float y, float z) {
		//printf("\nposx :%f,y:%f,z:%f ", position.x, position.y, position.z);
		position += glm::vec3{ x,y,z };
	};
	void setRot(float x, float y, float z) {
		rotation = glm::vec3(x,y,z);
	};
	void setRot_slow(float x, float y, float z) {


	};
	void setScale(float sx,float sy,float sz){
        scale = glm::vec3(sx,sy,sz);
	};
	glm::mat4 getMat(){
        glm::mat4 _this;
        _this = glm::translate(_this,glm::vec3(position.x,position.y,position.z));
		_this = glm::rotate(_this, rotation.x, glm::vec3(1, 0, 0));
		_this = glm::rotate(_this, rotation.y, glm::vec3(0, 1, 0));
		_this = glm::rotate(_this, rotation.z, glm::vec3(0, 0, 1));
        _this = glm::scale(_this,glm::vec3(scale.x,scale.y,scale.z));
        return _this;
	};
};

#endif // JUMA_TRANSFORM_INCLUDED
