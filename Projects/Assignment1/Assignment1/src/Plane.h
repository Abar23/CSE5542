#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Mesh.h"

class Plane
{
public:
	Plane(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 position, glm::vec3 color);
	
	~Plane(); 

	void Draw();

private:
	Mesh *mesh;
	glm::mat4 modelMatrix;

	std::vector<MeshVertex> SetVertices(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 color);

	std::vector<unsigned int> SetIndices(unsigned int heightSubdivision, unsigned int widthSubdivision);
};

#endif