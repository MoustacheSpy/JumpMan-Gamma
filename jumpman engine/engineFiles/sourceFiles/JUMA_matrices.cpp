#include "stdafx.h"
#include <JUMA_matrices.h>


JUMA_Mat3DCollectPlus JUMA_MakeCollection(glm::mat4 model, glm::mat4 view, glm::mat4 proj, char* modelName, char* viewname, char* projName) {
	JUMA_Mat3DCollectPlus collection;
	collection.model = model;
	collection.proj = proj;
	collection.view = view;
	collection.modelName = modelName;
	collection.viewName = viewname;
	collection.projName = projName;
	return collection;
}
