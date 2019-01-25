#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "Sphere.h"

Sphere::Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color) : 
	Shape(SetVertices(stacks, sectors, &color), SetIndices(stacks, sectors))
{
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Sphere::~Sphere()
{
}

std::vector<MeshVertex> Sphere::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	float sectorStep = (float)(2 * M_PI) / (sectors);
	float stackStep = (float)(M_PI) / stacks;
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
