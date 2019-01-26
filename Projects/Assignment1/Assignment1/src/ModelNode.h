#ifndef MODELNODE_H
#define MODELNODE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"

class ModelNode
{
public:
	ModelNode(Shape *shape, ModelNode *parentNode, glm::vec3 translation, glm::vec3 axis, float angle);

	ModelNode(Shape *shape, ModelNode *parentNode, glm::vec3 translation);

	~ModelNode();

	glm::mat4 UpdateModelMatrix(glm::mat4 *transformation);

	void AddChildNode(ModelNode *childNode);

	ModelNode * GetChildAt(int index);

	ModelNode * GetParent();

	int NumberOfChildren();

	Shape * GetShape();

private:
	Shape *shape;
	ModelNode *parentNode;
	vector<ModelNode *> childNodes;
	glm::vec3 translation;
	glm::vec3 axisOfRotation;
	float angle;
	bool nodeShouldRotate;
};

#endif //MODELNODE_H