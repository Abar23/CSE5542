#ifndef TORUS_H
#define TORUS_H

#include <vector>
#include "Shape.h"
#include "Mesh.h"

class Torus : public Shape
{
public:
	Torus(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color);
	
	~Torus();

private:
	std::vector<MeshVertex> SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color);

	std::vector<unsigned int> SetIndices(unsigned int stacks, unsigned int sectors);
};

#endif //TORUS_H