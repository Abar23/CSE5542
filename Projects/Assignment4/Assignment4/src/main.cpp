#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"
#include "Shader.h"
#include "Cube.h"
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

		// Create projection matrix
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		primitiveShader->SetUniformMatrix4fv("projection", &projectionMatrix);



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
	delete primitiveShader;
	delete window;

	return 0;
}