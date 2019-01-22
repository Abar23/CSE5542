#ifndef CUBE_H
#define CUBE_H

#include <GLM\glm.hpp>
#include "Mesh.h"

class Cube
{
public:
	Cube();
	~Cube();

private:
	Mesh *mesh;
	glm::mat4 modelMatrix;
};

#endif //CUBE_H