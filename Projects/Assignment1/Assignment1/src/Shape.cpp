#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"
#include "Shape.h"

Shape::Shape(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices)
{
	this->modelMatrix = glm::mat4(1.0f);
	this->mesh = new Mesh(vertices, indices);
}

Shape::~Shape()
{
	delete this->mesh;
}

void Shape::Draw()
{
	this->mesh->Draw();
}

void Shape::DrawWireFrame()
{
	this->mesh->DrawWireFrame();
}

glm::mat4 Shape::GetModelMatrix()
{
	return this->modelMatrix;
}

void Shape::SetScale(glm::vec3 scale)
{
	float xPosition = this->modelMatrix[0][3];
	float yPosition = this->modelMatrix[1][3];
	float zPosition = this->modelMatrix[2][3];
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(-xPosition, -yPosition, -zPosition));
	this->modelMatrix = glm::scale(this->modelMatrix, scale);
	this->modelMatrix = glm::translate(this->modelMatrix, glm::vec3(xPosition, yPosition, zPosition));
}
