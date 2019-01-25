#ifndef CYLINDER_H
#define CYLINDER_H

#include <GLM\glm.hpp>
#include "Mesh.h"

class Cylinder
{
public:
	Cylinder(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);

	~Cylinder();

	void Draw();

	void DrawWireFrame();

	glm::mat4 GetModelMatrix();

	void SetScale(glm::vec3 scale);

private:
	Mesh *mesh;
	glm::mat4 modelMatrix;

	std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //CYLINDER_H