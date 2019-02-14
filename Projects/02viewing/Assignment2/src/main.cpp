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

/*
 * GLFW callback for window resizing
 */
void SetFrameBufferSize(GLFWwindow * window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	trackball.SetNewWindowHeightWidth(height, width);
}

/*
 * GLFW callback for mouse button input
 */
void SetMouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
{
	trackball.MouseClickCallback(window, button, action, mods);
}

/*
 * GLFW callback for mouse cursor movement
 */
void SetCursorPosCallback(GLFWwindow * window, double mouseX, double mouseY)
{
	trackball.MouseCursorPositionCallback(window, mouseX, mouseY);
}

int main()
{
	// Create window
	Window *window = new Window(INITIAL_WINDOW_HEIGHT, INITIAL_WINDOW_WIDTH, "Porject 2 - Stereoscopic Viewing");

	// Set callbacks for GLFW event handling
	glfwSetFramebufferSizeCallback(window->GetGLFWWindow(), SetFrameBufferSize);
	glfwSetMouseButtonCallback(window->GetGLFWWindow(), SetMouseButtonCallback);
	glfwSetCursorPosCallback(window->GetGLFWWindow(), SetCursorPosCallback);

	// Create shader program for rendering the primitives
	Shader *primitiveShader = new Shader("../Resources/primitives.vs", "../Resources/primitives.fs");
	// Bind program for the entirety of the application
	primitiveShader->BindProgram();

	// Create the robot and plane objects that will be rendered in the scene
	RobotModel *robot = new RobotModel(primitiveShader);
	Shape *groundPlane = new Plane(16, 16, glm::vec3(0.0f), glm::vec3(1.0f));
	
	// Position all joints of the robot into place
	robot->Update();

	// Initialize the view matrx for the camera
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	
	// Initialize properties of the camera
	glm::vec3 cameraPosition = glm::vec3(0.0f, 5.0f, 30.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Initialize matrix to store rotations from the trackball
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	// Initialize the perspective projection matrix so that the scene depth
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	float intraOcularDistance = 0.5f;

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		// Process user input from the keyboard
		window->ProcessUserInput(&cameraPosition, &cameraFront, &cameraUp);

		// Create view matrix based on the properties of the camera
		viewMatrix = glm::lookAt(cameraPosition, cameraFront + cameraPosition, cameraUp);

		// Accumulate rotations from the trackball
		rotationMatrix *= trackball.GetRotationMatrixForView();

		// Apply trackball rotation to the view matrix
		viewMatrix = rotationMatrix * viewMatrix;

		// Calculate the aspect ratio for the stereoscopic views
		float stereoscopicAspectRation = ((float)window->GetWindowWidth() / 2) / (float)window->GetWindowHeight();

		// Create left eye view by translating the left eye along the positive x-axis
		glm::mat4 leftEyeView = glm::translate(viewMatrix, glm::vec3(intraOcularDistance, 0.0f, 0.0f));
		// Set the leftEyeView to the view matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("view", &leftEyeView);

		// Create projection matrix
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Modify viewport to match the new stereoscopic view parameters
		glViewport(0, 0, window->GetWindowWidth() / 2, window->GetWindowHeight());
		// Update the projectionMatrix each time since the window's aspect ratio can change
		projectionMatrix = glm::perspective(glm::radians(45.0f), stereoscopicAspectRation, 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Anchor the ground plane to the camera by having the plane follow the camera
		groundPlane->SetPositionXAndZPosition(cameraPosition);

		// Set the scale of the plane
		groundPlane->SetScale(&glm::vec3(500.0f, 0.0f, 500.0f));
		// Set the model matrix of the plane to the model matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		// Draw the plane
		groundPlane->Draw(false);
		// Draw the robot to the screen
		robot->Draw(false);

		// Create left eye view by translating the left eye along the negative x-axis
		glm::mat4 rightEyeView = glm::translate(viewMatrix, glm::vec3(-intraOcularDistance, 0.0f, 0.0f));
		// Set the rightEyeView to the view matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("view", &rightEyeView);

		// Modify viewport to match the new stereoscopic view parameters
		glViewport(window->GetWindowWidth() / 2, 0, window->GetWindowWidth() / 2, window->GetWindowHeight());
		// Update the projectionMatrix each time since the window's aspect ratio can change
		projectionMatrix = glm::perspective(glm::radians(45.0f), stereoscopicAspectRation, 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Set the model matrix of the plane to the model matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("model", &groundPlane->GetModelMatrix());
		// Draw the plane
		groundPlane->Draw(false);
		// Draw the robot to the screen
		robot->Draw(false);

		// Update the angle of the trackball
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