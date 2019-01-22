#include <iostream>
#include "Plane.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"

Plane::Plane(unsigned int heightSubdivisions, unsigned int widthSubdivisions, glm::vec3 position, glm::vec3 color)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, position);

	std::vector<MeshVertex> planeVertices = SetVertices(heightSubdivisions, widthSubdivisions, color);
	std::vector<unsigned int> planeIndices = SetIndices(heightSubdivisions, widthSubdivisions);
	this->mesh = new Mesh(planeVertices, planeIndices);
}

Plane::~Plane()
{
	delete this->mesh;
}

void Plane::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	this->mesh->Draw();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

std::vector<MeshVertex> Plane::SetVertices(unsigned int heightSubdivisions, unsigned int widthSubdivisions, glm::vec3 color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	float widthStep = 1.0f / (float)widthSubdivisions;
	float heightStep = 1.0f / (float)heightSubdivisions;

	for (unsigned int i = 0; i <= heightSubdivisions; i++)
	{
		float zPosition = ((float)i * heightStep) - 0.5f;
		for (unsigned int j = 0; j <= widthSubdivisions; j++)
		{
			float xPosition = ((float)j * widthStep) - 0.5f;
			vertex.position = glm::vec3(xPosition, zPosition, 0.0f);
			vertex.color = color;
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
