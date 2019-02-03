#define GLEW_STATIC
#include <cstdio>
#include <cstdlib>
#include "Window.h"

void setFrameBufferSize(GLFWwindow *window, int width, int height)
{
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}

Window::Window(int height, int width, const char * title, GLFWmonitor * montior, GLFWwindow * share)
{
	if (glfwInit() == NULL)
	{
		printf("GLFW could not be initialized!\n");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, title, montior, share);
	if (this->window == NULL)
	{
		printf("GLFW could not be initialized!\n");
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(this->window);

	glfwSetFramebufferSizeCallback(this->window, setFrameBufferSize);

	glewExperimental = GL_TRUE;
	GLenum glew = glewInit();
	if (GLEW_OK != glew)
	{
		printf("Could not initialize GLEW!!");
		exit(EXIT_FAILURE);
	}

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
