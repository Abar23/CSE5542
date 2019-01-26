#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"
#include "Shader.h"
#include "Plane.h"
#include "Cube.h"
#include "Sphere.h"
#include "Cylinder.h"
#include "Cone.h"
#include "Shape.h"
#include "HierachicalModel.h"
#include "ModelNode.h"

int main()
{
	Window *window = new Window(400, 400, "Porject 1 - Primitive Robot", NULL, NULL);

	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	primitiveShader->UseProgram();

	Shape *groundPlane = new Plane(8, 8, glm::vec3(0.0f), glm::vec3(1.0f));
	groundPlane->SetScale(&glm::vec3(8.0f, 0.0f, 4.0f));

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -1.25f, -7.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	primitiveShader->SetUniformMatrix4fv("view", &viewMatrix);

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		groundPlane->Draw(true);

		window->SwapBuffers();
		window->PollEvents();
		window->RefreshRate();
	}

	primitiveShader->TurnOffProgram();

	delete groundPlane;
	delete primitiveShader;
	delete window;
	return 0;
}