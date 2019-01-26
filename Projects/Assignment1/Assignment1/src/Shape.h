#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Mesh.h"

class Shape
{
public:

	Shape(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices);

	virtual ~Shape();

	void Draw(bool wireFrame);

	glm::mat4 GetModelMatrix();

	void SetModelMatrix(glm::mat4 *matrix);

	void SetScale(glm::vec3 *scale);

protected:
	Mesh *mesh;
	glm::mat4 modelMatrix;
};

#endif //SHAPE_H