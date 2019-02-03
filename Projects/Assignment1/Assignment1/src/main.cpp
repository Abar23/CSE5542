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
	// Create window
	Window *window = new Window(400, 400, "Porject 1 - Primitive Robot", NULL, NULL);

	// Create shader program for rendering the primitives
	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	// Bind program for the entirety of the application
	primitiveShader->BindProgram();

	// Create the robot and plane objects that will be rendered in the scene
	RobotModel *robot = new RobotModel(primitiveShader);
	Shape *groundPlane = new Plane(16, 16, glm::vec3(0.0f), glm::vec3(1.0f));

	// Set the scale of the plane
	groundPlane->SetScale(&glm::vec3(12.0f, 0.0f, 12.0f));

	// Initialize the view matrx for the camera
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	// Translate and rotate camera so that scene can be viewed from a good perspective
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -3.0f, -21.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	// Set the viewMatrix as the view unifiorm matrix in the primitiveShader
	primitiveShader->SetUniformMatrix4fv("view", &viewMatrix);

	// Initialize the perspective projection matrix so that the scene depth
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Update the projectionMatrix each time since the window's aspect ratio can change
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Set the model matrix of the plane to the model matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		// Draw the plane
		groundPlane->Draw(true);

		// Position all joints of the robot into place
		robot->Update();

		// Draw the robot to the screen
		robot->Draw(true);

		// Swap glfw's rendering buffers
		window->SwapBuffers();
		// Allow glfw to poll for events such as window size changes
		window->PollEvents();
		// Get the refresh rate of the window
		window->RefreshRate();
	}

	// Unbind the primitives shader since it is no longer needed
	primitiveShader->UnbindProgram();

	// Delete all resources allocated for the application
	delete groundPlane;
	delete robot;
	delete primitiveShader;
	delete window;
	
	return 0;
}