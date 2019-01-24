#include <GLM\glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <GLM\gtx\transform.hpp>
#include <vector>
#include "Window.h"
#include "Shader.h"
#include "Plane.h"
#include "Cube.h"

int main()
{
	Window *window = new Window(400, 400, "Test", NULL, NULL);

	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");

	primitiveShader->UseProgram();
	Plane *plane = new Plane(4, 4, glm::vec3(-2.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	Cube *cube = new Cube(4, glm::vec3(0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	primitiveShader->TurnOffProgram();

	plane->SetScale(glm::vec3(4.0f, 4.0f, 4.0f));
	cube->SetScale(glm::vec3(2.0f, 2.0f, 2.0f));

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -5.0f));
	
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	primitiveShader->UseProgram();
	glUniformMatrix4fv(glGetUniformLocation(primitiveShader->GetProgramID(), "view"), 1, GL_FALSE, &viewMatrix[0][0]);
	primitiveShader->TurnOffProgram();

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		
		primitiveShader->UseProgram();
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(primitiveShader->GetProgramID(), "projection"), 1, GL_FALSE, &projectionMatrix[0][0]);

		glUniformMatrix4fv(glGetUniformLocation(primitiveShader->GetProgramID(), "model"), 1, GL_FALSE, &cube->GetModelMatrix()[0][0]);
		cube->Draw();
		glUniformMatrix4fv(glGetUniformLocation(primitiveShader->GetProgramID(), "model"), 1, GL_FALSE, &plane->GetModelMatrix()[0][0]);
		plane->Draw();
		primitiveShader->TurnOffProgram();

		window->SwapBuffers();
		window->PollEvents();
		window->RefreshRate();
	}

	delete cube;
	delete plane;
	delete primitiveShader;
	delete window;
	return 0;
}