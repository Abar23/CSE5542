#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <GLM\glm.hpp>
#include "Mesh.h"

class Sphere
{
public:
	Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);
	
	~Sphere();

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

#endif //SPHERE_H