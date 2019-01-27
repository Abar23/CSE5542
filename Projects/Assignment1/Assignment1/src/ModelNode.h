#ifndef MODELNODE_H
#define MODELNODE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"

class ModelNode
{
public:
	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle, glm::vec3 localAxis, float localAngle);

	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle);

	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale);

	~ModelNode();

	glm::mat4 UpdateModelMatrix(glm::mat4 *transformation);

	void AddChildNode(ModelNode *childNode);

	ModelNode * GetChildAt(int index);

	int NumberOfChildren();

	Shape * GetShape();

private:
	Shape *shape;
	vector<ModelNode *> childNodes;
	glm::vec3 translation;
	glm::vec3 scale;
	glm::vec3 axisOfRotation;
	glm::vec3 localAxisOfRotation;
	float angle;
	float localAngle;
	bool nodeShouldRotate;
	bool nodeShouldRotateLocally;
};

#endif //MODELNODE_H