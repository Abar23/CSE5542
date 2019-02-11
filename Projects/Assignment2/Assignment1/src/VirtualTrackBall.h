#ifndef VIRTUALTRACKBALL_H
#define VIRTUALTRACKBALL_H

#include "GLM\glm.hpp"
#include "GLFW\glfw3.h"

class VirtualTrackBall
{
public:
	VirtualTrackBall(int height, int width);
	~VirtualTrackBall();

	void SetNewWindowHeightWidth(int newHieght, int newWidth);

	void MouseClickCallback(GLFWwindow *window, int button, int action, int mods);

	void MouseCursorPositionCallback(GLFWwindow *window, double mouseX, double mouseY);

	glm::mat4 GetRotationMatrixForView();

	glm::mat4 GetRotationMatrixForModel(glm::mat4 *viewMatrix);

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

	glm::vec3 ConvertMousePositionToScreenSpace(double mouseX, double mouseY);
};

#endif // VIRTUALTRACKBALL_H