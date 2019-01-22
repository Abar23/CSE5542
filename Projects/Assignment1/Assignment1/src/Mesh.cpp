#include "Mesh.h"

Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices)
{
	this->meshVertices = vertices;
	this->meshIndices = indices;

	CreateMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->vertexArray);
	glDeleteBuffers(1, &this->vertexArray);
	glDeleteBuffers(1, &this->indexBuffer);
}

void Mesh::RenderMesh()
{
	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
	glDrawElements(GL_TRIANGLES, this->meshIndices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::CreateMesh()
{
	glGenVertexArrays(1, &this->vertexArray);
	glGenBuffers(1, &this->vertexBuffer);
	glGenBuffers(1, &this->indexBuffer);

	glBindVertexArray(this->vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshVertex) * this->meshVertices.size(), &this->meshVertices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void *)offsetof(MeshVertex, color));

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->meshIndices.size(), &this->meshIndices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
