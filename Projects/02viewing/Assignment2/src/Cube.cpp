#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"
#include "Cube.h"

Cube::Cube(unsigned int faceSubdivisions, glm::vec3 position, glm::vec3 color) : 
	Shape(SetAllFaceVertices(faceSubdivisions, &color), SetAllFaceIndices(faceSubdivisions))
{
	// Set model matrix of the cone to the initial position
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Cube::~Cube()
{
}

std::vector<MeshVertex> Cube::SetAllFaceVertices(unsigned int faceSubdivisions, glm::vec3 *color)
{
	std::vector<MeshVertex> vertices;
	// Calculate the distance between vertices based on the faceSubdivisions
	float vertexStep = 1.0f / faceSubdivisions;

	// Create the top face
	CreateFaceVertices(
		&vertices,
		color,
		-0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the bottom face
	CreateFaceVertices(
		&vertices,
		color,
		-0.5f, -0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the front face
	CreateFaceVertices(
		&vertices,
		color,
		-0.5f, -0.5f, 0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the back face
	CreateFaceVertices(
		&vertices,
		color,
		-0.5f, -0.5f, -0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the left face
	CreateFaceVertices(
		&vertices,
		color,
		-0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	// Create the right face
	CreateFaceVertices(
		&vertices,
		color,
		0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	return vertices;
}

std::vector<unsigned int> Cube::SetAllFaceIndices(unsigned int faceSubdivisions)
{
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;

	unsigned int indexOffset = faceSubdivisions + 1;
	// Iterate through the number of faces that comprices that cube
	for (unsigned int i = 0; i < NUM_FACES; i++)
	{
		// Generate the indices that for each face of the cube
		for (unsigned int j = 0; j < faceSubdivisions; j++)
		{
			for (unsigned int k = 0; k < faceSubdivisions; k++)
			{
				indices.push_back(currentIndex);
				indices.push_back(currentIndex + 1);
				indices.push_back(currentIndex + indexOffset + 1);

				indices.push_back(currentIndex);
				indices.push_back(currentIndex + indexOffset + 1);
				indices.push_back(currentIndex + indexOffset);
				(currentIndex)++;
			}
			(currentIndex)++;
		}
		currentIndex += faceSubdivisions + 1;
	}

	return indices;
}

void Cube::CreateFaceVertices(
	std::vector<MeshVertex>* vertices, 
	glm::vec3 *color, 
	float x, float y, float z, 
	float xDirectionOuter, float yDirectionOuter, float zDirectionOuter, 
	float xDirectionInner, float yDirectionInner, float zDirectionInner, 
	unsigned int faceSubdivisions)
{
	MeshVertex vertex;
	vertex.color = *color;

	// Calculate all vertices of the face based upon the initial positoin and the inner/outer directions
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
}
