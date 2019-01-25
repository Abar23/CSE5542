#ifndef PLANE_H
#define PLANE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Plane : public Shape
{
public:
	Plane(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 position, glm::vec3 color);
	
	~Plane();

private:
	static std::vector<MeshVertex> SetVertices(unsigned int heightSubdivision, unsigned int widthSubdivision, glm::vec3 color);

	static std::vector<unsigned int> SetIndices(unsigned int heightSubdivision, unsigned int widthSubdivision);
};

#endif