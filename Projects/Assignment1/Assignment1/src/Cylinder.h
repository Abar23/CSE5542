#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Cylinder : public Shape
{
public:
	Cylinder(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);

	~Cylinder();

private:
	static std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	static std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //CYLINDER_H