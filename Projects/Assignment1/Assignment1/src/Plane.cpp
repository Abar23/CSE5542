#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include "GLM\gtx\transform.hpp"
#include "Plane.h"

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
	this->mesh->Draw();
}

void Plane::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
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

glm::mat4 Plane::GetModelMatrix()
{
	return this->modelMatrix;
}

void Plane::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}
