#define GLM_ENABLE_EXPERIMENTAL
#include <GLM\gtx\transform.hpp>
#include "Cube.h"

Cube::Cube(unsigned int faceSubdivisions, glm::vec3 position, glm::vec3 color)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, position);

	std::vector<MeshVertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;
	float vertexStep = 1.0f / faceSubdivisions;

	// Top face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		-0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Bottom face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		-0.5f, -0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Front face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		-0.5f, -0.5f, 0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Back face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		-0.5f, -0.5f, -0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Left face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		-0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	// Right face
	CreateFace(
		&vertices,
		&indices,
		&color,
		&currentIndex,
		0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	this->mesh = new Mesh(vertices, indices);
}

Cube::~Cube()
{
	delete this->mesh;
}

void Cube::Draw()
{
	this->mesh->Draw();
}

void Cube::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
}

void Cube::CreateFace(
	std::vector<MeshVertex>* vertices, 
	std::vector<unsigned int>* indices, 
	glm::vec3 *color, 
	unsigned int *currentIndex, 
	float x, float y, float z, 
	float xDirectionOuter, float yDirectionOuter, float zDirectionOuter, 
	float xDirectionInner, float yDirectionInner, float zDirectionInner, 
	unsigned int faceSubdivisions)
{
	MeshVertex vertex;
	vertex.color = *color;

	for (unsigned int i = 0; i <= faceSubdivisions; i++)
	{
		for (unsigned int j = 0; j <= faceSubdivisions; j++)
		{
			vertex.position = glm::vec3(x + (xDirectionInner * j), y + (yDirectionInner * j), z + (zDirectionInner * j));
			vertices->push_back(vertex);
		}
		x += xDirectionOuter;
		y += yDirectionOuter;
		z += zDirectionOuter;
	}

	unsigned int indexOffset = faceSubdivisions + 1;
	for (unsigned int i = 0; i < faceSubdivisions; i++)
	{
		for (unsigned int j = 0; j < faceSubdivisions; j++)
		{
			indices->push_back(*currentIndex);
			indices->push_back(*currentIndex + 1);
			indices->push_back(*currentIndex + indexOffset + 1);

			indices->push_back(*currentIndex);
			indices->push_back(*currentIndex + indexOffset + 1);
			indices->push_back(*currentIndex + indexOffset);
			(*currentIndex)++;
		}
		(*currentIndex)++;
	}
	*currentIndex = vertices->size();
}

glm::mat4 Cube::GetModelMatrix()
{
	return this->modelMatrix;
}

void Cube::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}
