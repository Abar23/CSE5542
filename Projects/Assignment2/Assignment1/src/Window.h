#ifndef WINDOW_H
#define WINDOW_H

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "GLM\glm.hpp"

using namespace std;

class Window
{
public:
	/**
	 * Creates a window with an attached OpenGL context
	 * @param height
	 *		Height of the window
	 * @param width
	 *		Width of the window
	 * @param title
	 *		Title that will appear at the top of the window
	 */
	Window(int height, int width, const char *title);

	~Window();

	/**
	 * Returns true when the window is open, false otherwise
	 */
	bool IsWindowClosed();

	/**
	 * Swap the draw buffers
	 */
	void SwapBuffers();

	/**
	* Clears the color buffer and depth bufer
	*/
	void ClearBuffer();

	/**
	* Allow glfw to check for any triggered events
	*/
	void PollEvents();

	/**
	* Returns the current apsect ratio of the window
	*/
	float GetAspectRatio();

	/**
	* Determine the refresh rate of the window. Used to normalize run-time between machines
	*/
	void RefreshRate();

	int GetWindowWidth();

	int GetWindowHeight();

	GLFWwindow * GetGLFWWindow();

private:
	GLFWwindow *window;

	float timeBetweenFrames;

	float timeAtLastFrame;
};

#endif //WINDOW_H
