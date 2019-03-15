#include "Mesh.h"

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices)
{
	this->meshVertices = vertices;
	this->meshIndices = indices;

	CreateMesh();
}

Mesh::~Mesh()
{
	// Delete vao, vbo, and ebo used to create the mesh
	glDeleteVertexArrays(1, &this->vertexArray);
	glDeleteBuffers(1, &this->vertexArray);
	glDeleteBuffers(1, &this->indexBuffer);
}

void Mesh::Draw()
{
	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glDrawElements(GL_TRIANGLES, this->meshIndices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Draw(int indexCount, int indexBufferOffset)
{
	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void *)indexBufferOffset);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::DrawWireFrame()
{
	// Enable wire fram rendering
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glDrawElements(GL_TRIANGLES, this->meshIndices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	// Restore original rendering mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int Mesh::GetCountOfMeshIndices()
{
	return this->meshIndices.size();
}

void Mesh::CreateMesh()
{
	// Create vao, vbo, and ebo
	glGenVertexArrays(1, &this->vertexArray);
	glGenBuffers(1, &this->vertexBuffer);
	glGenBuffers(1, &this->indexBuffer);

	// Bind vao, vbo, and ebo
	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	// Fill vertex buffer with the vector of MeshVertex structures
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * this->meshVertices.size(), &this->meshVertices[0], GL_STATIC_DRAW);
	
	// 0 corresponds to the "vertexPosition" input of the vertex shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, position));
	// 1 corresponds to the "vertexColor" input of the vertex shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, textureCoords));

	// Fill index buffer with the passed in indices
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->meshIndices.size(), &this->meshIndices[0], GL_STATIC_DRAW);

	// Unbind vao, vbo, and ebo
	glBindVertexArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
