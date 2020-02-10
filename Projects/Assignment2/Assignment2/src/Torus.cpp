#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "Torus.h"

Torus::Torus(unsigned int stacks, unsigned int sectors,  glm::vec3 position, glm::vec3 color) :
	Shape(SetVertices(stacks, sectors, &color), SetIndices(stacks, sectors))
{
	// Set model matrix of the cone to the initial position
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Torus::~Torus()
{
}

std::vector<MeshVertex> Torus::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 *color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	// Cache 2 * M_PI
	float twoPi = (float)(2 * M_PI);
	// Calculate the sector and stack step based upon the number of stacks and sectors the geometry is divided into
	float sectorStep = twoPi / sectors;
	float stackStep = twoPi / stacks;

	// Set initial stack and sector angles
	float currentSectorAngle = 0.0f;
	float currentStackAngle = 0.0f;

	// Create point vector that will store the calculate x, y, and z values for each vertice
	glm::vec3 point = glm::vec3(0.0f);
	// Iterate through each stack
	for (unsigned int i = 0; i <= stacks; i++)
	{
		// Calculate the current stack angle
		currentStackAngle = twoPi - (stackStep * i);
		// Cache R * (a * cos(Phi)), this is part of the parametric equation of a torus
		float radiusTimeCosPhi = 0.35f + (0.15f * cosf(currentStackAngle));
		// Calculate the y positon with respect to the current stack angle
		point.y = 0.15f * sinf(currentStackAngle);
		// Iterate through each sector
		for (unsigned int j = 0; j <= sectors; j++)
		{
			// Calculate the current sector angle
			currentSectorAngle = sectorStep * j;
			// Use the parametric equation of a torus to find x and z
			point.x = radiusTimeCosPhi * cosf(currentSectorAngle);
			point.z = radiusTimeCosPhi * sinf(currentSectorAngle);
			vertex.position = point;
			// Add the calculate point to eh set of vertices
			vertices.push_back(vertex);
		}
	}

	return vertices;
}

std::vector<unsigned int> Torus::SetIndices(unsigned int stacks, unsigned int sectors)
{
	std::vector<unsigned int> indices;
	unsigned int currentStackIndex = 0;
	unsigned int nextStackIndex = 0;

	// Setup indices for each stack that comprises the torus
	for (unsigned int i = 0; i < stacks; i++)
	{
		currentStackIndex = i * (sectors + 1);
		nextStackIndex = currentStackIndex + sectors + 1;
		for (unsigned int j = 0; j < sectors; j++)
		{
			indices.push_back(currentStackIndex);
			indices.push_back(nextStackIndex);
			indices.push_back(currentStackIndex + 1);
			indices.push_back(currentStackIndex + 1);
			indices.push_back(nextStackIndex);
			indices.push_back(nextStackIndex + 1);
			currentStackIndex++;
			nextStackIndex++;
		}
	}

	return indices;
}
