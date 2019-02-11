#define GLEW_STATIC
#include <cstdio>
#include <cstdlib>
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
