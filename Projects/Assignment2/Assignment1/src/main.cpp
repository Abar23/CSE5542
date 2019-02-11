#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"
#include "Shader.h"
#include "Plane.h"
#include "Cube.h"
#include "Torus.h"
#include "RobotModel.h"
#include "VirtualTrackBall.h"

#define INITIAL_WINDOW_WIDTH 1600
#define INITIAL_WINDOW_HEIGHT 800

static VirtualTrackBall trackball(INITIAL_WINDOW_HEIGHT, INITIAL_WINDOW_WIDTH);

void SetFrameBufferSize(GLFWwindow * window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	trackball.SetNewWindowHeightWidth(height, width);
}

void SetMouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	trackball.MouseClickCallback(window, button, action, mods);
}

void SetCursorPosCallback(GLFWwindow * window, double mouseX, double mouseY)
{
	trackball.MouseCursorPositionCallback(window, mouseX, mouseY);
}

int main()
{
	// Create window
	Window *window = new Window(INITIAL_WINDOW_HEIGHT, INITIAL_WINDOW_WIDTH, "Porject 2 - Stereoscopic Viewing");
	glfwSetFramebufferSizeCallback(window->GetGLFWWindow(), SetFrameBufferSize);
	glfwSetMouseButtonCallback(window->GetGLFWWindow(), SetMouseButtonCallback);
	glfwSetCursorPosCallback(window->GetGLFWWindow(), SetCursorPosCallback);

	// Create shader program for rendering the primitives
	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	// Bind program for the entirety of the application
	primitiveShader->BindProgram();

	// Create the robot and plane objects that will be rendered in the scene
	RobotModel *robot = new RobotModel(primitiveShader);
	
	// Position all joints of the robot into place
	robot->Update();

	Shape *groundPlane = new Plane(16, 16, glm::vec3(0.0f), glm::vec3(1.0f));

	// Set the scale of the plane
	groundPlane->SetScale(&glm::vec3(500.0f, 0.0f, 500.0f));

	// Initialize the view matrx for the camera
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	// Translate and rotate camera so that scene can be viewed from a good perspective
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -5.0f, -30.0f));

	// Initialize the perspective projection matrix so that the scene depth
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glm::mat4 viewMatrix1 = glm::translate(viewMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
		primitiveShader->SetUniformMatrix4fv("view", &viewMatrix1);

		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		robot->RotateRobotGlobally(&trackball.GetRotationMatrixForModel(&viewMatrix));

		groundPlane->RotateModelMatrixGlobally(&trackball.GetRotationMatrixForModel(&viewMatrix));

		glViewport(0, 0, window->GetWindowWidth() / 2, window->GetWindowHeight());
		// Update the projectionMatrix each time since the window's aspect ratio can change
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Set the model matrix of the plane to the model matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		// Draw the plane
		groundPlane->Draw(false);
		// Draw the robot to the screen
		robot->Draw(false);

		glm::mat4 viewMatrix2 = glm::translate(viewMatrix, glm::vec3(0.5f, 0.0f, 0.0f));
		primitiveShader->SetUniformMatrix4fv("view", &viewMatrix2);

		glViewport(window->GetWindowWidth() / 2, 0, window->GetWindowWidth() / 2, window->GetWindowHeight());
		// Update the projectionMatrix each time since the window's aspect ratio can change
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Set the model matrix of the plane to the model matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		// Draw the plane
		groundPlane->Draw(false);
		// Draw the robot to the screen
		robot->Draw(false);

		trackball.UpdateTrackBallAngle();
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