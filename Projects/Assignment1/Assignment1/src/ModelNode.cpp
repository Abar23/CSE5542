#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"
#include "ModelNode.h"

ModelNode::ModelNode(Shape *shape, ModelNode *parentNode, glm::vec3 translation, glm::vec3 axis, float angle)
{
	this->shape = shape;
	this->parentNode = parentNode;
	this->translation = translation;
	this->axisOfRotation = axis;
	this->angle = angle;
	this->nodeShouldRotate = true;
}

ModelNode::ModelNode(Shape *shape, ModelNode *parentNode, glm::vec3 translation)
{
	this->shape = shape;
	this->parentNode = parentNode;
	this->translation = translation;
	this->axisOfRotation = glm::vec3(0.0f);
	this->angle = 0.0f;
	this->nodeShouldRotate = false;
}

ModelNode::~ModelNode()
{
	this->parentNode = NULL;
	this->childNodes.clear();
	delete this->shape;
}

glm::mat4 ModelNode::UpdateModelMatrix(glm::mat4 *transformation)
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->translation);
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	if (this->nodeShouldRotate)
	{
		rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->angle), this->axisOfRotation);
	}
	glm::mat4 newTransformationMatrix = *transformation * rotationMatrix * translationMatrix;
	this->shape->SetModelMatrix(&newTransformationMatrix);
	return newTransformationMatrix;
}

void ModelNode::AddChildNode(ModelNode *childNode)
{
	this->childNodes.push_back(childNode);
}

ModelNode * ModelNode::GetChildAt(int index)
{
	return this->childNodes[index];
}

ModelNode * ModelNode::GetParent()
{
	return this->parentNode;
}

int ModelNode::NumberOfChildren()
{
	return this->childNodes.size();
}

Shape * ModelNode::GetShape()
{
	return this->shape;
}
