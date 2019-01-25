#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Shape.h"
#include "Mesh.h"

#define NUM_FACES 6

class Cube : public Shape
{
public:
	Cube(unsigned int faceSubdivisions, glm::vec3 position, glm::vec3 color);
	
	~Cube();

private:
	static std::vector<MeshVertex> SetAllFaceVertices(unsigned int faceSubdivisions, glm::vec3 *color);

	static std::vector<unsigned int> SetAllFaceIndices(unsigned int faceSubdivisions);

	static void CreateFaceVertices(
		std::vector<MeshVertex> *vertices, 
		glm::vec3 *color, 
		float x, float y, float z,
		float xDirectionOuter, float yDirectionOuter, float zDirectionOuter,
		float xDirectionInner, float yDirectionInner, float zDirectionInner, 
		unsigned int faceSubdivisions);
};

#endif //CUBE_H