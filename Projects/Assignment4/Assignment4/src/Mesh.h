#ifndef MESH_H
#define MESH_H

#include <vector>
#include "GL\glew.h"
#include "GLM\glm.hpp"
#include "Shader.h"

typedef struct
{
	glm::vec3 position;
	glm::vec2 textureCoords;
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
	 * Draw portion of the mesh defined by the number of indices and offset into the 
	 * index buffer
	 * @param indexCount
	 *		The number of indices to render
	 * @param indexBufferOffset
	 *		The offset into the buffer where the desired indices are located
	 */
	void Draw(int indexCount, int indexBufferOffset);

	/**
	 * Draws the mesh in a wire frame mode
	 */
	void DrawWireFrame();
	
	/**
	 * Get the number of indices that define the mesh
	 */
	int GetCountOfMeshIndices();

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