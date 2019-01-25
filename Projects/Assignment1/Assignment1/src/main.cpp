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

int main()
{
	Window *window = new Window(400, 400, "Porject 1 - Primitive Robot", NULL, NULL);

	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	primitiveShader->UseProgram();

	Plane *plane = new Plane(4, 4, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Cube *cube = new Cube(4, glm::vec3(0.0f), glm::vec3(1.0f));
	Sphere *sphere = new Sphere(12, 12, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Cylinder *cylinder = new Cylinder(12, 36, glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	Cone *cone = new Cone(6, 16, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -1.25f, -5.5f));
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	primitiveShader->SetUniformMatrix4fv("view", &viewMatrix);

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);
		
		primitiveShader->SetUniformMatrix4fv("model", &cube->GetModelMatrix());
		cube->DrawWireFrame();

		primitiveShader->SetUniformMatrix4fv("model", &plane->GetModelMatrix());
		plane->DrawWireFrame();

		primitiveShader->SetUniformMatrix4fv("model", &sphere->GetModelMatrix());
		sphere->DrawWireFrame();

		primitiveShader->SetUniformMatrix4fv("model", &cylinder->GetModelMatrix());
		cylinder->DrawWireFrame();

		primitiveShader->SetUniformMatrix4fv("model", &cone->GetModelMatrix());
		cone->DrawWireFrame();

		window->SwapBuffers();
		window->PollEvents();
		window->RefreshRate();
	}

	primitiveShader->TurnOffProgram();

	delete cone;
	delete cylinder;
	delete sphere;
	delete cube;
	delete plane;
	delete primitiveShader;
	delete window;
	return 0;
}