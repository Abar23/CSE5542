#ifndef MODELNODE_H
#define MODELNODE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"

class ModelNode
{
public:
	/**
	 * Creates a hierarchy node structure
	 * @param shape
	 *		Pointer to the shape object
	 * @param translation
	 *		Vector to translate the shape object
	 * @param scale
	 *		Vector to scale the shape object
	 * @param axis
	 *		Vector that represents the axis to rotate hierarchy about
	 * @param angle
	 *		Angle to rotate the hierachry
	 * @param localAxis
	 *		Local axis to rotate shape object about
	 * @param localAngle
	 *		Local angle to rotate shape object
	 */
	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle, glm::vec3 localAxis, float localAngle);

	/**
	 * Creates a hierarchy node structure
	 * @param shape
	 *		Pointer to the shape object
	 * @param translation
	 *		Vector to translate the shape object
	 * @param scale
	 *		Vector to scale the shape object
	 * @param axis
	 *		Vector that represents the axis to rotate hierarchy about
	 * @param angle
	 *		Angle to rotate the hierachry
	 */
	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale, glm::vec3 axis, float angle);

	/**
	 * Creates a hierarchy node structure
	 * @param shape
	 *		Pointer to the shape object
	 * @param translation
	 *		Vector to translate the shape object
	 * @param scale
	 *		Vector to scale the shape object
	 */
	ModelNode(Shape *shape, glm::vec3 translation, glm::vec3 scale);

	~ModelNode();

	/**
	 * Applies tranform to node
	 * @param transformation
	 *		Pointer to the tranformation matrix
	 *		
	 * Returns matrix with contatination of trandorms from node
	 */
	glm::mat4 UpdateModelMatrix(glm::mat4 *transformation);

	/**
	 * Adds a child to the node
	 */
	void AddChildNode(ModelNode *childNode);

	/**
	 * Get the child at a given index
	 * @param index
	 *		Index of the desired child
	 * 
	 * Returns ModelNode
	 */
	ModelNode * GetChildAt(int index);

	/**
	 * Returns the number of children of the node
	 */
	int NumberOfChildren();

	/**
	 * Returns the shape object of the node
	 */
	Shape * GetShape();

	glm::mat4 GetHierarchyMatrix();

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