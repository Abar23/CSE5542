#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "GLM\glm.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"
#include "Shader.h"
#include "Cube.h"
#include "Texture.h"
#include "VirtualTrackBall.h"

#define INITIAL_WINDOW_WIDTH 800
#define INITIAL_WINDOW_HEIGHT 800

/*
 * GLFW callback for window resizing
 */
void SetFrameBufferSize(GLFWwindow * window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

int main()
{
	// Create window
	Window *window = new Window(INITIAL_WINDOW_HEIGHT, INITIAL_WINDOW_WIDTH, "Porject 2 - Stereoscopic Viewing");

	// Set callbacks for GLFW event handling
	glfwSetFramebufferSizeCallback(window->GetGLFWWindow(), SetFrameBufferSize);

	// Create shader program for rendering the primitives
	Shader *basicTextureShader = new Shader("../Resources/Shaders/basicTextureShader.vs", "../Resources/Shaders/basicTextureShader.fs");
	// Bind program for the entirety of the application
	basicTextureShader->BindProgram();

	// Load all textures
	Texture crateTexture("../Resources/Textures/Crate.jpg");
	
	std::vector<Texture *> textures = {
		new Texture("../Resources/Textures/Abstract Painting.jpg"),
		new Texture("../Resources/Textures/Tropical.jpg"),
		new Texture("../Resources/Textures/Grunge.jpg"),
		new Texture("../Resources/Textures/Nebulas.jpg"),
		new Texture("../Resources/Textures/Oil Painting.jpg"),
		new Texture("../Resources/Textures/Metalic Pattern.jpg")
	};

	// Create Cube objects that will utilized the various textures
	Cube SingleTexturedCube(4, glm::vec3(-1.0f, 0.0f, 0.0f));
	Cube MultiTexturedCube(1, glm::vec3(1.0f, 0.0f, 0.0f));

	// Initialize the view matrx for the camera
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	
	// Initialize properties of the camera
	glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 4.75f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// Initialize matrix to store rotations from the trackball
	glm::mat4 rotationMatrix = glm::mat4(1.0f);

	// Initialize the perspective projection matrix so that the scene depth
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	while (window->IsWindowClosed())
	{
		window->ClearBuffer();
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

		// Process user input from the keyboard
		window->ProcessUserInput(&cameraPosition, &cameraFront, &cameraUp);

		// Create view matrix based on the properties of the camera
		viewMatrix = glm::lookAt(cameraPosition, cameraFront + cameraPosition, cameraUp);

		// Set the leftEyeView to the view matrix uniform in the primitivesShader
		basicTextureShader->SetUniformMatrix4fv("view", &viewMatrix);

		// Create projection matrix
		projectionMatrix = glm::perspective(glm::radians(45.0f), window->GetAspectRatio(), 0.1f, 100.0f);
		// Set the projectionMatrix to the projection matrix uniform in the primitivesShader
		basicTextureShader->SetUniformMatrix4fv("projection", &projectionMatrix);

		// Slowly rotate the cube around the x, y, and z axes
		SingleTexturedCube.SetModelMatrix(&glm::rotate(SingleTexturedCube.GetModelMatrix(), 0.01f, glm::vec3(1.0f, 0.3f, 0.5f)));
		// Set the model matrix of the cube to the shader model matrix uniform
		basicTextureShader->SetUniformMatrix4fv("model", &SingleTexturedCube.GetModelMatrix());
		// Render the cube with a single texture on the geometry
		SingleTexturedCube.DrawCubeWithTexture(&crateTexture, basicTextureShader);

		// Slowly rotate the cube around the x, y, and z axes
		MultiTexturedCube.SetModelMatrix(&glm::rotate(MultiTexturedCube.GetModelMatrix(), 0.01f, glm::vec3(1.0f, 0.3f, 0.5f)));
		// Set the model matrix of the cube to the shader model matrix uniform
		basicTextureShader->SetUniformMatrix4fv("model", &MultiTexturedCube.GetModelMatrix());
		// Render the cube with multiple textures on the geometry
		MultiTexturedCube.DrawCubeWithTextureArray(textures, basicTextureShader);

		// Swap glfw's rendering buffers
		window->SwapBuffers();
		// Allow glfw to poll for events such as window size changes
		window->PollEvents();
		// Get the refresh rate of the window
		window->RefreshRate();
	}

	// Unbind the primitives shader since it is no longer needed
	basicTextureShader->UnbindProgram();

	// Delete all resources allocated for the application
	delete basicTextureShader;
	delete window;

	for (Texture *texture : textures)
	{
		delete texture;
	}

	return 0;
}