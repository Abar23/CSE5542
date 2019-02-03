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
	/**
	 * Creates a mesh object
	 * @param vertices
	 *		The set of vertices that define the geometry
	 * @param indices
	 *		The set of indices that define all triangles of the geometry
	 */
	Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices);
	
	~Mesh();
	
	/**
	 * Draws the mesh in fill mode
	 */
	void Draw();

	/**
	 * Draws the mesh in a wire frame mode
	 */
	void DrawWireFrame();

private:
	GLuint vertexArray, vertexBuffer, indexBuffer;

	std::vector<MeshVertex> meshVertices;
	std::vector<unsigned int> meshIndices;

	/**
	 * Creates vao, vbo, and vao from the passed in mesh vertices and indices
	 */
	void CreateMesh();
};

#endif //MESH_H