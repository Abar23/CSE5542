#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "Sphere.h"

Sphere::Sphere(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color) : 
	Shape(SetVertices(stacks, sectors, &color), SetIndices(stacks, sectors))
{
	// Set model matrix of the cone to the initial position
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

	// Determine sector and stack step to move based upon the stacks and sectors subdivisions passed in
	float sectorStep = (float)(2 * M_PI) / (sectors);
	float stackStep = (float)(M_PI) / stacks;

	// Set the initial sector and stack angle
	float currentSectorAngle = 0.0f;
	float currentStackAngle = 0.0f;

	// Create point vector that will store the calculate x, y, and z values for each vertice
	glm::vec3 point = glm::vec3(0.0f);
	// Iterate through each stack
	for (unsigned int i = 0; i <= stacks; i++)
	{
		// Calculate the current sector angle
		currentStackAngle = (float)M_PI_2 - (stackStep * i);
		// Cache R * cos(Phi), based on the parametric equation for a sphere
		float radiusTimeCosPhi = 0.5f * cosf(currentStackAngle);
		// Calculate the y position based on the current stackangle
		point.y = 0.5f * sinf(currentStackAngle);
		// Iterate through each sector
		for (unsigned int j = 0; j <= sectors; j++)
		{
			// Calculate the current sector angle
			currentSectorAngle = sectorStep * j;
			// Use the parametric equation of a sphere to calculate x and z
			point.x = radiusTimeCosPhi * cosf(currentSectorAngle);
			point.z = radiusTimeCosPhi * sinf(currentSectorAngle);
			vertex.position = point;
			// Add the calculated point to the set of vertices
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

	// Setup indices for the Sphere
	for (unsigned int i = 0; i < stacks; i++)
	{
		currentStackIndex = i * (sectors + 1);
		nextStackIndex = currentStackIndex + sectors + 1;
		for (unsigned int j = 0; j < sectors; j++)
		{
			// Set the indices for top part of the sphere
			if (i == 0)
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(currentStackIndex + 1);
			}
			// Set the indices for the middle region of the sphere
			else if (i == stacks - 1)
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(currentStackIndex + 1);
			}
			// Set the indices for the bottom part of the sphere
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
