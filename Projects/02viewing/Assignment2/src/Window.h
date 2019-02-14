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

	/**
	* Return the current width of the window
	*/
	int GetWindowWidth();

	/**
	* Return the current height of the window
	*/
	int GetWindowHeight();

	/**
	* Return a pointer to the GLFWwindow object
	*/
	GLFWwindow * GetGLFWWindow();

	/**
	 * Process user input from the keyboard
	 * @param camerPosition
	 *		Position of the camera
	 * @param cameraFront
	 *		The direction the camera is facing
	 * @param cameraUp
	 *		The direction that is up relative to the camera
	 */
	void ProcessUserInput(glm::vec3 *camerPosition, glm::vec3 *cameraFront, glm::vec3 *cameraUp);

private:
	GLFWwindow *window;

	float timeBetweenFrames;

	float timeAtLastFrame;
};

#endif //WINDOW_H
