#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "Cone.h"

Cone::Cone(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, position);

	std::vector<MeshVertex> vertices = SetVertices(stacks, sectors, &color);
	std::vector<unsigned int> indices = SetIndices(stacks, sectors);
	this->mesh = new Mesh(vertices, indices);
}

Cone::~Cone()
{
	delete this->mesh;
}

void Cone::Draw()
{
	this->mesh->Draw();
}

void Cone::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
}

glm::mat4 Cone::GetModelMatrix()
{
	return this->modelMatrix;
}

void Cone::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}

std::vector<MeshVertex> Cone::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	float stackStep = 1.0f / stacks;
	float sectorStep = (float)(2 * M_PI) / sectors;

	glm::vec3 point = glm::vec3(0.0f);
	for (unsigned int i = 0; i <= stacks; i++)
	{
		float heightParameter = 1.0f - (stackStep * i);
		point.y = heightParameter - 0.5f;
		for (unsigned int j = 0; j <= sectors; j++)
		{
			float sectorAngle = sectorStep * j;
			float heightRatio = (1.0f - heightParameter) / 1.0f;
			point.x = heightRatio * 0.5f * cosf(sectorAngle);
			point.z = heightRatio * 0.5f * sinf(sectorAngle);
			vertex.position = point;
			vertices.push_back(vertex);
		}
	}

	vertex.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertices.push_back(vertex);

	return vertices;
}

std::vector<unsigned int> Cone::SetIndices(unsigned int stacks, unsigned int sectors)
{
	std::vector<unsigned int> indices;
	unsigned int currentStackIndex = 0;
	unsigned int nextStackIndex = 0;

	for (unsigned int i = 0; i < stacks; i++)
	{
		currentStackIndex = i * (sectors + 1);
		nextStackIndex = currentStackIndex + sectors + 1;
		for (unsigned int j = 0; j < sectors; j++)
		{
			if (i == 0)
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(nextStackIndex + 1);
			}
			else
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(currentStackIndex + 1);
				indices.push_back(currentStackIndex + 1);
				indices.push_back(nextStackIndex);
				indices.push_back(nextStackIndex + 1);
			}
			currentStackIndex++;
			nextStackIndex++;
		}
	}
	//Setup bottom face indices
	nextStackIndex = (sectors + 1) * (stacks + 1);
	currentStackIndex = nextStackIndex - (sectors + 1);
	for (unsigned int i = 0; i < sectors; i++)
	{
		indices.push_back(currentStackIndex);
		indices.push_back(nextStackIndex);
		indices.push_back(currentStackIndex + 1);
		currentStackIndex++;
	}

	return indices;
}
