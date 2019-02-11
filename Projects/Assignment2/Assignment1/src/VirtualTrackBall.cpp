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
	if (this->isRotating)
	{
		if (!this->hasInitialPosition)
		{
			this->previousPosition = ConvertMousePositionToScreenSpace(mouseX, mouseY);
			this->hasInitialPosition = true;
		}
		else
		{
			this->currentPosition = ConvertMousePositionToScreenSpace(mouseX, mouseY);
			this->angleBetweenPositions = acos(std::min(1.0f, glm::dot(this->previousPosition, this->currentPosition) / (glm::length(this->previousPosition) * glm::length(this->currentPosition))));
			this->axisOfRotation = glm::cross(this->previousPosition, this->currentPosition);
		}
	}
}

glm::mat4 VirtualTrackBall::GetRotationMatrixForView()
{
	float angle = this->angleBetweenPositions - this->previousAngle;
	if (angle < 0.0f)
	{
		this->hasInitialPosition = false;
		angle = 0.0f;
		this->previousAngle = 0.0f;
		this->angleBetweenPositions = 0.0f;
	}
	return glm::rotate(angle, this->axisOfRotation);
}

glm::mat4 VirtualTrackBall::GetRotationMatrixForModel(glm::mat4 *viewMatrix)
{
	float angle = this->angleBetweenPositions - this->previousAngle;
	if (angle < 0.0f)
	{
		this->hasInitialPosition = false;
		angle = 0.0f;
		this->previousAngle = 0.0f;
		this->angleBetweenPositions = 0.0f;
	}
	glm::vec3 rotationAxis = glm::inverse(glm::mat3(*viewMatrix)) * this->axisOfRotation;
	return glm::rotate(angle, rotationAxis);
}

void VirtualTrackBall::UpdateTrackBallAngle()
{
	this->previousAngle = this->angleBetweenPositions;
}

glm::vec3 VirtualTrackBall::ConvertMousePositionToScreenSpace(double mouseX, double mouseY)
{
	glm::vec3 screenCoordinates = glm::vec3(0.0f);
	screenCoordinates.x = ((2 * mouseX) - this->windowWidth) / this->windowWidth;
	screenCoordinates.y = -((2 * mouseY) - this->windowHeight) / this->windowHeight;

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
