#ifndef JUMA_TRANSFORM_INCLUDED
#define JUMA_TRANSFORM_INCLUDED
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stdio.h>
class JUMA_Transform{
private:
    glm::vec3 rotation = { 0.0,0.0,0.0 };
	glm::vec3 position = { 0.0,0.0,0.0 };
	glm::vec3 scale;
	glm::vec3 posOffset = {0.0,0.0,0.0};
	JUMA_Transform** children;
	int childcount=0;
public:
    JUMA_Transform(){
        scale = {1.0,1.0,1.0};
        children = new JUMA_Transform*[1];
    };
	void setPos(float x, float y, float z) {
		position = glm::vec3(x, y, z);
	};
	void translate(float x, float y, float z) {
		printf("\nposx :%f,y:%f,z:%f ", position.x, position.y, position.z);
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
	void setChild(JUMA_Transform *child){
        delete []children;
        children = new JUMA_Transform*[childcount+1];
        children[childcount] = child;
        childcount++;
	};
	void setParent(JUMA_Transform *parent){
        parent->setChild(this);
	};
	void printChildren(){
        for(int i=0;i<childcount;i++){
            children[i]->printChildren();
        }
        printf("transform: x=%f y=%f z=%f Rotation: x=%f y=%f z=%f Scale: x=%f y=%f z=%f",position.x,position.y,position.z,rotation.x,rotation.y,rotation.z,scale.x,scale.y,scale.z);
	};
	void updateChildren(){
        for(int i=0;i<childcount;i++){
            children[i]->posOffset.x = position.x;
            children[i]->posOffset.y = position.y;
            children[i]->posOffset.z = position.z;

            printf("x: %d y: %d z:%d\n",children[i]->posOffset.x,children[i]->posOffset.y,children[i]->posOffset.z);
            children[i]->updateChildren();
        }

	};
	glm::mat4 getMat(){
        glm::mat4 _this;
        updateChildren();
        _this = glm::translate(_this,glm::vec3(position.x+posOffset.x,position.y+posOffset.y,position.z+posOffset.z));
		//_this = glm::translate(_this,glm::vec3(position.x,posOffset.y,posOffset.z));

		_this = glm::rotate(_this, rotation.x, glm::vec3(1, 0, 0));
		_this = glm::rotate(_this, rotation.y, glm::vec3(0, 1, 0));
		_this = glm::rotate(_this, rotation.z, glm::vec3(0, 0, 1));
        _this = glm::scale(_this,glm::vec3(scale.x,scale.y,scale.z));
        return _this;
	};
};

#endif // JUMA_TRANSFORM_INCLUDED
