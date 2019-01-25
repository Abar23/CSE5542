#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "GLM\gtx\transform.hpp"
#include "Plane.h"

Plane::Plane(unsigned int heightSubdivisions, unsigned int widthSubdivisions, glm::vec3 position, glm::vec3 color) : 
	Shape(SetVertices(heightSubdivisions, widthSubdivisions, color), SetIndices(heightSubdivisions, widthSubdivisions))
{
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Plane::~Plane()
{
}

std::vector<MeshVertex> Plane::SetVertices(unsigned int heightSubdivisions, unsigned int widthSubdivisions, glm::vec3 color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = color;

	float widthStep = 1.0f / (float)widthSubdivisions;
	float heightStep = 1.0f / (float)heightSubdivisions;

	for (unsigned int i = 0; i <= heightSubdivisions; i++)
	{
		float zPosition = 0.5f - ((float)i * heightStep);
		for (unsigned int j = 0; j <= widthSubdivisions; j++)
		{
			float xPosition = ((float)j * widthStep) - 0.5f;
			vertex.position = glm::vec3(xPosition, 0.0f, zPosition);
			vertices.push_back(vertex);
		}
	}

	return vertices;
}

std::vector<unsigned int> Plane::SetIndices(unsigned int heightSubdivisions, unsigned int widthSubdivisions)
{
	std::vector<unsigned int> indices;

	unsigned int currentIndex = 0;
	unsigned int indexOffset = widthSubdivisions + 1;

	for (unsigned int i = 0; i < heightSubdivisions; i++, currentIndex++)
	{
		for (unsigned int j = 0; j < widthSubdivisions; j++, currentIndex++)
		{
			indices.push_back(currentIndex);
			indices.push_back(currentIndex + 1);
			indices.push_back(currentIndex + indexOffset + 1);

			indices.push_back(currentIndex);
			indices.push_back(currentIndex + indexOffset + 1);
			indices.push_back(currentIndex + indexOffset);
		}
	}

	return indices;
}
