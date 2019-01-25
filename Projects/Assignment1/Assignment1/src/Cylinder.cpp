#define GLM_ENABLE_EXPERIMENTAL
#include <GLM\gtx\transform.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Cylinder.h"

Cylinder::Cylinder(unsigned int stacks, unsigned int sectors, glm::vec3 position, glm::vec3 color)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->modelMatrix = glm::translate(this->modelMatrix, position);

	std::vector<MeshVertex> vertices = SetVertices(stacks, sectors, &color);
	std::vector<unsigned int> indices = SetIndices(stacks, sectors);
	this->mesh = new Mesh(vertices, indices);
}

Cylinder::~Cylinder()
{
	delete this->mesh;
}

void Cylinder::Draw()
{
	this->mesh->Draw();
}

void Cylinder::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
}

glm::mat4 Cylinder::GetModelMatrix()
{
	return this->modelMatrix;
}

void Cylinder::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}

std::vector<MeshVertex> Cylinder::SetVertices(unsigned int stacks, unsigned int sectors, glm::vec3 * color)
{
	std::vector<MeshVertex> vertices;
	MeshVertex vertex;
	vertex.color = *color;

	float stackStep = 1.0f / stacks;
	float sectorStep = (2 * M_PI) / sectors;

	vertex.position = glm::vec3(0.0f, 0.5f, 0.0f);
	vertices.push_back(vertex);

	float currentSectorAngle = 0.0f;
	glm::vec3 point = glm::vec3(0.0f);
	for (unsigned int i = 0; i <= stacks; i++)
	{
		point.y = 0.5f - (stackStep * i);
		
		for (unsigned int j = 0; j <= sectors; j++)
		{
			currentSectorAngle = sectorStep * j;
			point.x = 0.5f * cosf(currentSectorAngle);
			point.z = 0.5f * sinf(currentSectorAngle);
			vertex.position = point;
			vertices.push_back(vertex);
		}
	}

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
			indices.push_back(nextStackIndex + 1);
			indices.push_back(nextStackIndex + 1);
			indices.push_back(currentStackIndex);
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
