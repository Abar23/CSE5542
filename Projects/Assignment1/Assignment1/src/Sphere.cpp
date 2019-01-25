#define GLM_ENABLE_EXPERIMENTAL
#include <GLM\gtx\transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Sphere.h"

Sphere::Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, position);

	std::vector<MeshVertex> vertices = SetVertices(stacks, sectors, &color);
	std::vector<unsigned int> indices = SetIndices(stacks, sectors);
	this->mesh = new Mesh(vertices, indices);
}

Sphere::~Sphere()
{
	delete this->mesh;
}

void Sphere::Draw()
{
	this->mesh->Draw();
}

void Sphere::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
}

glm::mat4 Sphere::GetModelMatrix()
{
	return this->modelMatrix;
}

void Sphere::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}

std::vector<MeshVertex> Sphere::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	float sectorStep = (2 * M_PI) / (float)sectors;
	float stackStep = (M_PI) / (float)stacks;
	float currentSectorAngle = 0.0f;
	float currentStackAngle = 0.0f;

	glm::vec3 point = glm::vec3(0.0f);
	for (unsigned int i = 0; i <= stacks; i++)
	{
		currentStackAngle = (float)M_PI_2 - (stackStep * i);
		float radiusTimeCosPhi = 0.5f * cosf(currentStackAngle);
		point.y = 0.5f * sinf(currentStackAngle);
		for (unsigned int j = 0; j <= sectors; j++)
		{
			currentSectorAngle = sectorStep * j;
			point.x = radiusTimeCosPhi * cosf(currentSectorAngle);
			point.z = radiusTimeCosPhi * sinf(currentSectorAngle);
			vertex.position = point;
			vertices.push_back(vertex);
		}
	}

	return vertices;
}

std::vector<unsigned int> Sphere::SetIndices(unsigned int stacks, unsigned int sectors)
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
				indices.push_back(currentStackIndex + 1);
			}
			else if (i == stacks - 1)
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(currentStackIndex + 1);
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

	return indices;
}
