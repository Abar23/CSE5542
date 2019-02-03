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

void Shape::Draw(bool wireFrame)
{
	if (wireFrame)
	{
		this->mesh->DrawWireFrame();
	}
	else
	{
		this->mesh->Draw();
	}
}

glm::mat4 Shape::GetModelMatrix()
{
	return this->modelMatrix;
}

void Shape::SetModelMatrix(glm::mat4 *matrix)
{
	this->modelMatrix = *matrix;
}

void Shape::SetScale(glm::vec3 *scale)
{
	this->modelMatrix = glm::scale(this->modelMatrix, *scale);
}
