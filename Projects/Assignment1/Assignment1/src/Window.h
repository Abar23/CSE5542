#ifndef WINDOW_H
#define WINDOW_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"

using namespace std;

class Window
{
public:
	Window(int height, int width, const char *title, GLFWmonitor *montior, GLFWwindow *share);

	~Window();

	bool IsWindowClosed();

	void SwapBuffers();

	void ClearBuffer();

	void PollEvents();

	float GetAspectRatio();

	void RefreshRate();

private:
	GLFWwindow *window;

	float timeBetweenFrames;

	float timeAtLastFrame;
};

#endif //WINDOW_H
