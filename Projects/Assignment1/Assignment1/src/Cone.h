#ifndef CONE_H
#define CONE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

class Cone : public Shape
{
public:
	Cone(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);

	~Cone();

private:
	static std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	static std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //CONE_H