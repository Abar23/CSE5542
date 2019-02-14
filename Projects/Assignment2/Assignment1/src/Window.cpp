#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#include <cstdio>
#include <cstdlib>
#include "GLM\glm.hpp"
#include "GLM\gtx\rotate_vector.hpp"
#include "GLM\gtx\transform.hpp"
#include "Window.h"

Window::Window(int height, int width, const char * title)
{
	// Initialize glfw
	if (glfwInit() == NULL)
	{
		printf("GLFW could not be initialized!\n");
		exit(EXIT_FAILURE);
	}

	// Set OpenGL context to version to 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (this->window == NULL)
	{
		printf("GLFW could not be initialized!\n");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);

	// Enable experimental drivers
	glewExperimental = GL_TRUE;
	//Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		printf("Could not initialize GLEW!!");
		exit(EXIT_FAILURE);
	}

	// Enable z buffer depth testing
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

bool Window::IsWindowClosed()
{
	return !glfwWindowShouldClose(this->window);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(this->window);
}

void Window::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::PollEvents()
{
	glfwPollEvents();
}

float Window::GetAspectRatio()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);

	return (float)width / (float)height;
}

// This corrects how fast openGL runs between hardware so that movement with the camera becomes uniform for all users
void Window::RefreshRate()
{
	float timeAtCurrentFrame = glfwGetTime();
	this->timeBetweenFrames = timeAtCurrentFrame - this->timeAtLastFrame;
	this->timeAtLastFrame = timeAtCurrentFrame;
}

int Window::GetWindowWidth()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);

	return width;
}

int Window::GetWindowHeight()
{
	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);

	return height;
}

GLFWwindow * Window::GetGLFWWindow()
{
	return this->window;
}

void Window::ProcessUserInput(glm::vec3 * camerPosition, glm::vec3 * cameraFront, glm::vec3 * cameraUp)
{
	float cameraSpeed = 5.0f * this->timeBetweenFrames; // Makes camera movement uniform between differing hardware across user machines

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		*camerPosition += cameraSpeed * *cameraFront;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		*camerPosition -= cameraSpeed * *cameraFront;
	}

	cameraSpeed = 25.0f * this->timeBetweenFrames;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		*cameraFront = glm::rotate(*cameraFront, glm::radians(cameraSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		*cameraFront = glm::rotate(*cameraFront, -glm::radians(cameraSpeed), glm::vec3(0.0f, 1.0f, 0.0f));
	}
}
