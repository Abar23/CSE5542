#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "GLM\glm.hpp"
#include "Mesh.h"

class Cube
{
public:
	Cube(unsigned int faceSubdivisions, glm::vec3 position, glm::vec3 color);
	
	~Cube();

	void Draw();

	void DrawWireFrame();

	glm::mat4 GetModelMatrix();

	void SetScale(glm::vec3 scale);

private:
	Mesh *mesh;
	glm::mat4 modelMatrix;

	static void CreateFace(
		std::vector<MeshVertex> *vertices, 
		std::vector<unsigned int> *indices, 
		glm::vec3 *color, 
		unsigned int *currentIndex, 
		float x, float y, float z,
		float xDirectionOuter, float yDirectionOuter, float zDirectionOuter,
		float xDirectionInner, float yDirectionInner, float zDirectionInner, 
		unsigned int faceSubdivisions);
};

#endif //CUBE_H