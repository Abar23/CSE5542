#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include "GLM\gtx\transform.hpp"
#include "VirtualTrackBall.h"

VirtualTrackBall::VirtualTrackBall(int height, int width)
{
	this->windowHeight = height;
	this->windowWidth = width;
	this->isRotating = false;
	this->hasInitialPosition = false;
	this->axisOfRotation = glm::vec3(0.0f, 1.0f, 0.0f);
	this->angleBetweenPositions = 0.0f;
	this->previousAngle = 0.0;
}

VirtualTrackBall::~VirtualTrackBall()
{
}

void VirtualTrackBall::SetNewWindowHeightWidth(int newHieght, int newWidth)
{
	this->windowHeight = newHieght;
	this->windowWidth = newWidth;
}

void VirtualTrackBall::MouseClickCallback(GLFWwindow * window, int button, int action, int mods)
{
	// Only listen to left mouse button clicks
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		this->isRotating = true;
	}
	else
	{
		this->isRotating = false;
		this->hasInitialPosition = false;
		this->angleBetweenPositions = 0.0f;
		this->previousAngle = 0.0f;
	}
}

void VirtualTrackBall::MouseCursorPositionCallback(GLFWwindow * window, double mouseX, double mouseY)
{
	// The left mouse button is clicked
	if (this->isRotating)
	{
		// Calculate the initial position for the trackball base upon the mouse position
		if (!this->hasInitialPosition)
		{
			this->previousPosition = ConvertMousePositionToScreenSpace(mouseX, mouseY);
			this->hasInitialPosition = true;
		}
		// Calculate and update the sequential positions based upon the mouse position
		else
		{
			this->currentPosition = ConvertMousePositionToScreenSpace(mouseX, mouseY);
			this->angleBetweenPositions = acos(std::min(1.0f, glm::dot(this->previousPosition, this->currentPosition) / (glm::length(this->previousPosition) * glm::length(this->currentPosition))));
			// Generate axis of rotation
			this->axisOfRotation = glm::cross(this->previousPosition, this->currentPosition);
		}
	}
}

glm::mat4 VirtualTrackBall::GetRotationMatrixForView()
{
	// Get angle to rotate by
	float angle = this->angleBetweenPositions - this->previousAngle;
	// If there is not an angle to rotate about, generate new positions for the trackball
	if (angle < 0.0f)
	{
		this->hasInitialPosition = false;
		angle = 0.0f;
		this->previousAngle = 0.0f;
		this->angleBetweenPositions = 0.0f;
	}
	// Generate rotation matrix based upon the calculated rotation angle and axis of rotation
	return glm::rotate(angle, this->axisOfRotation);
}

void VirtualTrackBall::UpdateTrackBallAngle()
{
	// Set previous angle to the next angle
	this->previousAngle = this->angleBetweenPositions;
}

glm::vec3 VirtualTrackBall::ConvertMousePositionToScreenSpace(double mouseX, double mouseY)
{
	// Initialize vector to store the converted x, y, and z positions
	glm::vec3 screenCoordinates = glm::vec3(0.0f);
	// Convert mouse X to screen space x
	screenCoordinates.x = ((2 * mouseX) - this->windowWidth) / this->windowWidth;
	// Convert moust Y to screen space Y
	screenCoordinates.y = -((2 * mouseY) - this->windowHeight) / this->windowHeight;

	// Get radius/hypotenuse based upon the x and y position
	float hypotenuseFromScreenXY = screenCoordinates.x * screenCoordinates.x + screenCoordinates.y * screenCoordinates.y;
	if (hypotenuseFromScreenXY <= 1.0f)
	{
		screenCoordinates.z = sqrt(1.0f - hypotenuseFromScreenXY);
	}
	else
	{
		screenCoordinates = glm::normalize(screenCoordinates);
	}

	return screenCoordinates;
}
