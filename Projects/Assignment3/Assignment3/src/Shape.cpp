#define GLM_ENABLE_EXPERIMENTAL
#include "GLM\gtx\transform.hpp"
#include "Shape.h"

Shape::Shape(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices)
{
	// Initialize the model matrix to the identity matrix
	this->modelMatrix = glm::mat4(1.0f);
	// Create matrix
	this->mesh = new Mesh(vertices, indices);
	this->globalRotationMatrix = glm::mat4(1.0f);
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
	this->modelMatrix = *matrix * this->globalRotationMatrix;
}

void Shape::SetScale(glm::vec3 *scale)
{
	this->modelMatrix = glm::scale(this->modelMatrix, *scale);
}

void Shape::RotateModelMatrixGlobally(glm::mat4 * matrix)
{
	this->globalRotationMatrix = *matrix;
	this->modelMatrix = this->globalRotationMatrix * this->modelMatrix;
}

void Shape::UpdateModelMatrix(glm::mat4 * matrix)
{
	this->modelMatrix *= *matrix;
}

glm::mat4 Shape::GetGlobalRotationMatrix()
{
	return this->globalRotationMatrix;
}

void Shape::SetPositionXAndZPosition(glm::vec3 position)
{
	glm::mat4 newModelMatrx = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, 0.0f, position.z));
	
	this->modelMatrix = newModelMatrx;
}
