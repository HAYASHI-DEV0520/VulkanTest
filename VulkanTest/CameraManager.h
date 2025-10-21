#pragma once
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "InputManager.h"
#include "TimeManager.h"


class CameraManager
{
public:
	glm::mat4 getCamera();
	void setCamera(glm::mat4 camera);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void moveByKey(InputManager* input, int KEY);
	CameraManager();
	glm::vec3 getCameraPosition();
	glm::mat4 getViewMatrix();
private:
	glm::mat4 camera;
	double lastX, lastY;
	bool firstMouse = true;

	float sensitivity = 0.005f;

	glm::vec3 target;
	float radius = 5.0f;
	float theta = glm::radians(0.0f);
	float phi = glm::radians(30.0f);

	float movement = 0.9f;

	TimeManager time;
	
};

