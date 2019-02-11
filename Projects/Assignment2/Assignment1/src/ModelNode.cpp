#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"
#include "ModelNode.h"

ModelNode::ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle, glm::vec3 localAxis, float localAngle)
{
	this->shape = shape;
	this->translation = translation;
	this->scale = scale;
	this->axisOfRotation = axis;
	this->angle = angle;
	this->nodeShouldRotate = true;
	this->localAxisOfRotation = localAxis;
	this->localAngle = localAngle;
	this->nodeShouldRotateLocally = true;
}

ModelNode::ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle)
{
	this->shape = shape;
	this->translation = translation;
	this->scale = scale;
	this->axisOfRotation = axis;
	this->angle = angle;
	this->nodeShouldRotate = true;
	this->localAxisOfRotation = glm::vec3(0.0f);
	this->localAngle = 0.0f;
	this->nodeShouldRotateLocally = false;
}

ModelNode::ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale)
{
	this->shape = shape;
	this->translation = translation;
	this->scale = scale;
	this->axisOfRotation = glm::vec3(0.0f);
	this->angle = 0.0f;
	this->nodeShouldRotate = false;
	this->localAxisOfRotation = glm::vec3(0.0f);
	this->localAngle = 0.0f;
	this->nodeShouldRotateLocally = false;
}

ModelNode::~ModelNode()
{
	this->childNodes.clear();
	delete this->shape;
}

glm::mat4 ModelNode::UpdateModelMatrix(glm::mat4 *transformation)
{
	// Create translation matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->translation);
	// Create scale matrix
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), this->scale);

	// Set rotation matrix to Identity
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	// If tation matrix is to be applied. create rotation matrix based upon the angle and axis of rotation
	if (this->nodeShouldRotate)
	{
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->angle), this->axisOfRotation);
	}

	// Createthe nodes transformation that has its translation and rotation matrix applied to the passed in tranform matrix
	glm::mat4 newTransformationMatrix = *transformation * rotationMatrix * translationMatrix;
	// Cache the matrix from above since it represents the transformation pertaining to the hierarchy
	glm::mat4 hierarchyMatrix = newTransformationMatrix;

	// Check it local rotation should be applied
	if (this->nodeShouldRotateLocally)
	{
		// Apply location roation to transform
		newTransformationMatrix = glm::rotate(newTransformationMatrix, glm::radians(this->localAngle), this->localAxisOfRotation);
	}

	// Apply scale to node tranformation matrix
	newTransformationMatrix *= scaleMatrix;
	// Set model shape model matrix that is stored at the node
	this->shape->SetModelMatrix(&newTransformationMatrix);

	return hierarchyMatrix;
}



void ModelNode::AddChildNode(ModelNode *childNode)
{
	this->childNodes.push_back(childNode);
}

ModelNode * ModelNode::GetChildAt(int index)
{
	return this->childNodes[index];
}

int ModelNode::NumberOfChildren()
{
	return this->childNodes.size();
}

Shape * ModelNode::GetShape()
{
	return this->shape;
}

glm::mat4 ModelNode::GetHierarchyMatrix()
{
	glm::mat4 hierarchyMatrix = glm::mat4(1.0f);

	// Create translation matrix
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), this->translation);

	// Set rotation matrix to Identity
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	// If tation matrix is to be applied. create rotation matrix based upon the angle and axis of rotation
	if (this->nodeShouldRotate)
	{
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(this->angle), this->axisOfRotation);
	}

	// Createthe nodes transformation that has its translation and rotation matrix applied to the passed in tranform matrix
	hierarchyMatrix = rotationMatrix * translationMatrix;


	return hierarchyMatrix;
}
