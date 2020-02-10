#ifndef VIRTUALTRACKBALL_H
#define VIRTUALTRACKBALL_H

#include "GLM\glm.hpp"
#include "GLFW\glfw3.h"

class VirtualTrackBall
{
public:
	/**
	 * Create trackball control that is used to manipulate the camera view
	 * @param height
	 *		Height of the window
	 * @param width
	 *		Width of the window
	 */
	VirtualTrackBall(int height, int width);

	~VirtualTrackBall();

	/**
	 * Update the stored width and height to the resized window's width and 
	 * height of the
	 * @param newHeight
	 *		Height of the window
	 * @param newWidth
	 *		Width of the window
	 */
	void SetNewWindowHeightWidth(int newHieght, int newWidth);

	/**
	 * Mouse callback for GLFW that allows for mouse event handling
	 * @param window
	 *		Current GLFWwindow
	 * @param button
	 *		Mouse button that was pressed
	 * @param action
	 *		Indicates the action that the user made with the mouse
	 * @param mods
	 *		The GLFWwindow bit field that describes which modifier keys were held down
	 */
	void MouseClickCallback(GLFWwindow *window, int button, int action, int mods);

	/**
	 * Mouse cursor callback for GLFW that allows for mouse event handling
	 * @param window
	 *		Current GLFWwindow
	 * @param mouseX
	 *		X position of the mouse cursor
	 * @param mouseY
	 *		Y position of the mouse cursor
	 */
	void MouseCursorPositionCallback(GLFWwindow *window, double mouseX, double mouseY);

	/**
	 * Return rotational matrix based upon the trackball's movement
	 */
	glm::mat4 GetRotationMatrixForView();
	
	/**
	 * Update the current angle of rotation for the trackball
	 */
	void UpdateTrackBallAngle();

private:
	int windowHeight;
	int windowWidth;
	float previousAngle;
	float angleBetweenPositions;
	glm::vec3 previousPosition;
	glm::vec3 currentPosition;
	glm::vec3 axisOfRotation;
	bool isRotating;
	bool hasInitialPosition;

	/**
	 * Converts mouse positions from GLFW to screen space so that it maps to the 
	 * trackball
	 * @param window
	 *		Current GLFWwindow
	 * @param mouseX
	 *		X position of the mouse cursor
	 * @param mouseY
	 *		Y position of the mouse cursor
	 */
	glm::vec3 ConvertMousePositionToScreenSpace(double mouseX, double mouseY);
};

#endif // VIRTUALTRACKBALL_H