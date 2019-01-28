#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"
#include "Shader.h"
#include "Plane.h"
#include "Torus.h"
#include "RobotModel.h"

int main()
{
	Window *window = new Window(400, 400, "Porject 1 - Primitive Robot", NULL, NULL);

	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	primitiveShader->UseProgram();

	RobotModel *robot = new RobotModel(primitiveShader);
	Shape *groundPlane = new Plane(16, 16, glm::vec3(0.0f), glm::vec3(1.0f));

	groundPlane->SetScale(&glm::vec3(12.0f, 0.0f, 12.0f));

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -3.0f, -21.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	primitiveShader->SetUniformMatrix4fv("view", &viewMatrix);
	robot->Update();
	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		groundPlane->Draw(true);

		robot->Draw(true);

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