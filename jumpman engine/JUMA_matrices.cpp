#include "stdafx.h"
#include "JUMA_matrices.h"


JUMA_Mat3DCollect JUMA_MakeCollection(glm::mat4 model, glm::mat4 view, glm::mat4 proj, char* modelName, char* viewname, char* projName) {
	JUMA_Mat3DCollect collection;
	collection.model = model;
	collection.proj = proj;
	collection.view = view;
	strcpy(collection.modelName ,modelName);
	strcpy(collection.viewName, viewname);
	strcpy(collection.projName, projName);
	return collection;
}