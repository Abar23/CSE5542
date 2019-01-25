#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Sphere : public Shape
{
public:
	Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);
	
	~Sphere();

private:
	static std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	static std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //SPHERE_H