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

	void Draw();

	void DrawWireFrame();

	glm::mat4 GetModelMatrix();

	void SetScale(glm::vec3 scale);

protected:
	Mesh *mesh;
	glm::mat4 modelMatrix;
};

#endif //SHAPE_H