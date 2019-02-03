#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "Cone.h"

Cone::Cone(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color) : 
	Shape(SetVertices(stacks, sectors, &color), SetIndices(stacks, sectors))
{
	// Set model matrix of the cone to the initial position
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Cone::~Cone()
{
}

std::vector<MeshVertex> Cone::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	// Determine step length to move based upon the stacks and sectors
	float stackStep = 1.0f / stacks;
	float sectorStep = (float)(2 * M_PI) / sectors;

	// Create point vector that will store the calculate x, y, and z values for each vertice
	glm::vec3 point = glm::vec3(0.0f);
	// Iterate through each stack
	for (unsigned int i = 0; i <= stacks; i++)
	{
		// Get height at current stack
		float heightParameter = 1.0f - (stackStep * i);
		// Calculate y positon based on the current stack height
		point.y = heightParameter - 0.5f;
		for (unsigned int j = 0; j <= sectors; j++)
		{
			// Calculate the based upon the current sector step
			float sectorAngle = sectorStep * j;
			// Calculate the height ratio that that will scale the radius to the proper length
			float heightRatio = (1.0f - heightParameter) / 1.0f;
			// Use the parametric equation of a cone to calculate x and z
			point.x = heightRatio * 0.5f * cosf(sectorAngle);
			point.z = heightRatio * 0.5f * sinf(sectorAngle);
			vertex.position = point;
			// Add the calculated point to the set of vertices
			vertices.push_back(vertex);
		}
	}

	// Add center positio of the bottom face to the set of vertices
	vertex.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertices.push_back(vertex);

	return vertices;
}

std::vector<unsigned int> Cone::SetIndices(unsigned int stacks, unsigned int sectors)
{
	std::vector<unsigned int> indices;
	unsigned int currentStackIndex = 0;
	unsigned int nextStackIndex = 0;

	// Setup indices from the top point of the cone to the bottom stack
	for (unsigned int i = 0; i < stacks; i++)
	{
		currentStackIndex = i * (sectors + 1);
		nextStackIndex = currentStackIndex + sectors + 1;
		for (unsigned int j = 0; j < sectors; j++)
		{
			// Set indices for the tip of the cone
			if (i == 0)
			{
				indices.push_back(currentStackIndex);
				indices.push_back(nextStackIndex);
				indices.push_back(nextStackIndex + 1);
			}
			// Set indices for the stacks that make up the body of the cone
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

	//Setup face indices for the bottom stach
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
