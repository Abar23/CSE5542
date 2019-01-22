#include <GLM\glm.hpp>
#include <vector>
#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Plane.h"

int main()
{
	Window *window = new Window(400, 400, "Test", NULL, NULL);

	Shader *primitiveShader = new Shader("./Resources/primitives.vs", "./Resources/primitives.fs");

	Plane *plane = new Plane(4, 4, glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		primitiveShader->UseProgram();
		plane->Draw();
		primitiveShader->TurnOffProgram();

		window->SwapBuffers();
		window->PollEvents();
		window->RefreshRate();
	}
	delete plane;
	delete primitiveShader;
	delete window;
	return 0;
}