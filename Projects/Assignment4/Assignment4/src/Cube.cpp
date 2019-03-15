#define GLM_ENABLE_EXPERIMENTAL
#include <cassert>
#include "GLM\gtx\transform.hpp"
#include "Cube.h"

Cube::Cube(unsigned int faceSubdivisions, glm::vec3 position) : 
	Shape(SetAllFaceVertices(faceSubdivisions), SetAllFaceIndices(faceSubdivisions))
{
	// Set model matrix of the cone to the initial position
	this->modelMatrix = glm::translate(this->modelMatrix, position);
}

Cube::~Cube()
{
}

void Cube::DrawCubeWithTexture(Texture * texture, Shader *shader)
{
	// Bind the texture
	texture->BindTexture(0);
	// Set the texture to the sampler2D uniform in the shader program
	shader->SetUniformToTextureUnit("cubeTexture", 0);
	// Render the cube
	this->Draw(false);
	// Unbind the texture since it is no longer needed
	texture->UnbindTexture();
}

void Cube::DrawCubeWithTextureArray(std::vector<Texture *> textures, Shader * shader)
{
	// Make sure the passed in vector of texture has enough texture for exactly six faces of the cube
	assert(textures.size() == NUM_FACES);

	// Get the number of indices that define a single face
	int indexCountPerFace = this->mesh->GetCountOfMeshIndices() / NUM_FACES;
	// Iterate through all faces of the cube
	for (unsigned int i = 0; i < NUM_FACES; i++)
	{
		// Get a texture from the vector of textures
		Texture *texture = textures[i];
		// Bind the texture
		texture->BindTexture(0);
		// Set the texture to the sampler2D uniform in the shader program
		shader->SetUniformToTextureUnit("cubeTexture", 0);
		// Render only the desired face with the currently binded texture
		this->mesh->Draw(indexCountPerFace, indexCountPerFace * sizeof(unsigned int) * i);
		// Unbind the texture since it is no longer needed
		texture->UnbindTexture();
	}
}

std::vector<MeshVertex> Cube::SetAllFaceVertices(unsigned int faceSubdivisions)
{
	std::vector<MeshVertex> vertices;
	// Calculate the distance between vertices based on the faceSubdivisions
	float vertexStep = 1.0f / faceSubdivisions;

	// Create the top face
	CreateFaceVertices(
		&vertices,
		-0.5f, 0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the bottom face
	CreateFaceVertices(
		&vertices,
		-0.5f, -0.5f, 0.5f,
		0.0f, 0.0f, -vertexStep,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the front face
	CreateFaceVertices(
		&vertices,
		-0.5f, -0.5f, 0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the back face
	CreateFaceVertices(
		&vertices,
		-0.5f, -0.5f, -0.5f,
		0.0f, vertexStep, 0.0f,
		vertexStep, 0.0f, 0.0f,
		faceSubdivisions);

	// Create the left face
	CreateFaceVertices(
		&vertices,
		-0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	// Create the right face
	CreateFaceVertices(
		&vertices,
		0.5f, -0.5f, -0.5f,
		0.0, vertexStep, 0.0f,
		0.0f, 0.0f, vertexStep,
		faceSubdivisions);

	return vertices;
}

std::vector<unsigned int> Cube::SetAllFaceIndices(unsigned int faceSubdivisions)
{
	std::vector<unsigned int> indices;
	unsigned int currentIndex = 0;

	unsigned int indexOffset = faceSubdivisions + 1;
	// Iterate through the number of faces that comprices that cube
	for (unsigned int i = 0; i < NUM_FACES; i++)
	{
		// Generate the indices that for each face of the cube
		for (unsigned int j = 0; j < faceSubdivisions; j++)
		{
			for (unsigned int k = 0; k < faceSubdivisions; k++)
			{
				indices.push_back(currentIndex);
				indices.push_back(currentIndex + 1);
				indices.push_back(currentIndex + indexOffset + 1);

				indices.push_back(currentIndex);
				indices.push_back(currentIndex + indexOffset + 1);
				indices.push_back(currentIndex + indexOffset);
				(currentIndex)++;
			}
			(currentIndex)++;
		}
		currentIndex += faceSubdivisions + 1;
	}

	return indices;
}

void Cube::CreateFaceVertices(
	std::vector<MeshVertex>* vertices, 
	float x, float y, float z, 
	float xDirectionOuter, float yDirectionOuter, float zDirectionOuter, 
	float xDirectionInner, float yDirectionInner, float zDirectionInner, 
	unsigned int faceSubdivisions)
{
	MeshVertex vertex;

	float outerTextCoordPosition = 0.0f;
	float innerTextCoordPosition = 0.0f;
	float textCoordStep = 1.0f / (float)faceSubdivisions;

	// Calculate all vertices of the face based upon the initial position and the inner/outer direction vectors
	for (unsigned int i = 0; i <= faceSubdivisions; i++)
	{
		outerTextCoordPosition = textCoordStep * i;
		for (unsigned int j = 0; j <= faceSubdivisions; j++)
		{
			innerTextCoordPosition = textCoordStep * j;
			vertex.position = glm::vec3(x + (xDirectionInner * j), y + (yDirectionInner * j), z + (zDirectionInner * j));
			vertex.textureCoords = glm::vec2(outerTextCoordPosition, innerTextCoordPosition);
			vertices->push_back(vertex);
		}
		x += xDirectionOuter;
		y += yDirectionOuter;
		z += zDirectionOuter;
	}
}
