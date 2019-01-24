#ifndef MESH_H
#define MESH_H

#include <vector>
#include "GL\glew.h"
#include "GLM\glm.hpp"
#include "Shader.h"

typedef struct
{
	glm::vec3 position;
	glm::vec3 color;
} MeshVertex;

class Mesh
{
public:
	Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices);
	
	~Mesh();
	
	void Draw();

	void DrawWireFrame();

private:
	GLuint vertexArray, vertexBuffer, indexBuffer;

	std::vector<MeshVertex> meshVertices;
	std::vector<unsigned int> meshIndices;

	void CreateMesh();
};

#endif //MESH_H