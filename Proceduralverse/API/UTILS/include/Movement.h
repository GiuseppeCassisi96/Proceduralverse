#pragma once
#include "UTILS/include/Transform.h"
#include <GLFW/Include/glfw3.h>
#include "Constants.h"

class Movement
{
public:
	float currentTime = 0.0, lastTime = 0.0, deltaTime = 0.0;
	float movementSpeed = 90.0f;
	float yaw = 0.0f, pitch = 0.0f;
	float rotationSensitivity = 0.1f;
	float lastX = WIDTH / 2, lastY = HEIGHT / 2;
	bool firstMouse = true;
	glm::vec3 cameraDirection;
	glm::vec3 position;
	glm::vec3 upAxe, forwardAxe, rightAxe;
	const glm::vec3 centerOfScene{ glm::vec3(0.0f) };
	Movement(glm::vec3 initialPos, glm::mat4& viewMatrix);
	void Move(GLFWwindow* window, glm::mat4& viewMatrix);
	void Rotate(double xpos, double ypos);
};
