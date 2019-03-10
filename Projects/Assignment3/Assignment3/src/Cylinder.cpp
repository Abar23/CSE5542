#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include "GLM\gtx\transform.hpp"
#include "GLM\gtx\vector_angle.hpp"
#include "Cylinder.h"

Cylinder::Cylinder(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color) :
	Shape(SetVertices(stacks, sectors, &color), SetIndices(stacks, sectors))
{
	// Set model matrix of the cone to the initial position
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Cylinder::~Cylinder()
{
}

void Cylinder::PlaceCylinderBetweenPoints(glm::vec3 initialPoint, glm::vec3 endingPoint, float angle)
{
	this->modelMatrix = glm::mat4(1.0f);

	glm::vec3 midPoint = glm::vec3((initialPoint.x + endingPoint.x) / 2.0f, (initialPoint.y + endingPoint.y) / 2.0f, 0.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, midPoint);
	
	this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f));
	
	float yHeight = std::abs(endingPoint.y - initialPoint.y);
	float xHeight = std::abs(endingPoint.x - initialPoint.x);
	float yScale = std::sqrtf(std::powf(xHeight, 2) + std::powf(yHeight, 2));
	this->SetScale(&glm::vec3(0.5f, yScale, 0.5f));
}

std::vector<MeshVertex> Cylinder::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	// Determine sector and stack step to move based upon the stacks and sectors
	float stackStep = 1.0f / stacks;
	float sectorStep = (float)(2 * M_PI) / sectors;

	// Add center point for the top face of the cylinder
	vertex.position = glm::vec3(0.0f, 0.5f, 0.0f);
	vertices.push_back(vertex);

	// Set initial sector angle
	float sectorAngle = 0.0f;
	// Create point vector that will store the calculate x, y, and z values for each vertice
	glm::vec3 point = glm::vec3(0.0f);
	// Iterate through each stack
	for (unsigned int i = 0; i <= stacks; i++)
	{
		// Calculate y positon based on the current stack height
		point.y = 0.5f - (stackStep * i);
		// Iterate through each sector
		for (unsigned int j = 0; j <= sectors; j++)
		{
			// Calculate the curent sector angle
			sectorAngle = sectorStep * j;
			// Use parametric equation of a cylinder to calculate x and z
			point.x = 0.5f * cosf(sectorAngle);
			point.z = 0.5f * sinf(sectorAngle);
			vertex.position = point;
			// Add the calculated point to the set of vertices
			vertices.push_back(vertex);
		}
	}

	// Add the center point for the bottom face of the cylinder
	vertex.position = glm::vec3(0.0f, -0.5f, 0.0f);
	vertices.push_back(vertex);

	return vertices;
}

std::vector<unsigned int> Cylinder::SetIndices(unsigned int stacks, unsigned int sectors)
{
	std::vector<unsigned int> indices;
	unsigned int currentStackIndex = 0;
	unsigned int nextStackIndex = 0;

	// Setup top face indices
	nextStackIndex++;
	for (unsigned int i = 0; i < sectors; i++)
	{
		indices.push_back(currentStackIndex);
		indices.push_back(nextStackIndex);
		indices.push_back(nextStackIndex + 1);
		nextStackIndex++;
	}

	//Create indices for middle region
	for (unsigned int i = 0; i < stacks; i++)
	{
		currentStackIndex = (i * (sectors + 1)) + 1;
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

	//Setup bottom face indices
	nextStackIndex = ((sectors + 1) * (stacks + 1)) + 1;
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
