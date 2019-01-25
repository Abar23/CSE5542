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

int main()
{
	Window *window = new Window(400, 400, "Porject 1 - Primitive Robot", NULL, NULL);

	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	primitiveShader->UseProgram();

	Shape *plane = new Plane(8, 8, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Shape *cube = new Cube(12, glm::vec3(0.0f), glm::vec3(1.0f));
	Shape *sphere = new Sphere(36, 18, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Shape *cylinder = new Cylinder(12, 36, glm::vec3(-2.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f));
	Shape *cone = new Cone(12, 32, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));

	std::vector<Shape *> shapesToRender = {plane, cube, sphere, cylinder, cone};

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
		
		for (Shape *shape : shapesToRender)
		{
			primitiveShader->SetUniformMatrix4fv("model", &shape->GetModelMatrix());
			shape->DrawWireFrame();
		}

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