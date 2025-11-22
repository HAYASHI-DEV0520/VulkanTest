#include "CameraManager.h"
#include <iostream>

glm::mat4 CameraManager::getCamera()
{
	return camera;
}

void CameraManager::setCamera(glm::mat4 camera)
{
	this->camera = camera;
}

void CameraManager::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - float(ypos);
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		theta += xoffset * sensitivity;
		phi += yoffset * sensitivity;

		if (phi > glm::radians(179.5f)) phi = glm::radians(179.5f);
		if (phi < glm::radians(0.5f)) phi = glm::radians(0.5f);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		target -= glm::normalize(glm::cross(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f)), target - getCameraPosition())) * yoffset * sensitivity * scale;
		target -= glm::normalize(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f))) * xoffset * sensitivity * scale;

	}

}

void CameraManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	radius -= yoffset * scale / 10.0f;
	float max = 10.0f * scale;
	if (radius > max) {
		radius = max;
	}
	if (radius < 0.1f) {
		radius = 0.1f;
	}
}

void CameraManager::moveByKey(InputManager* input, int KEY)
{
	switch (input->getKeyStatus(KEY)) {
	case InputManager::KeyStatus::HOLD:
		switch (KEY) {
		case GLFW_KEY_W:
			target += glm::normalize(glm::cross(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f)), target - getCameraPosition())) * time.getDuration() * scale;
			break;
		case GLFW_KEY_S:
			target -= glm::normalize(glm::cross(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f)), target - getCameraPosition())) * time.getDuration() * scale;
			break;
		case GLFW_KEY_A:
			target -= glm::normalize(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f))) * time.getDuration() * scale;
			break;
		case GLFW_KEY_D:
			target += glm::normalize(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 1.0f, 0.0f))) * time.getDuration() * scale;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE: // //
			target = glm::vec3(0.0f);
			radius = 3;
			lastX = lastY = 0;
		default:
			break;
		}
		break;
	default:
		break;
	}
	time.recordTime();
}

CameraManager::CameraManager()
{
	radius = 3 * scale;
	target = glm::vec3(0.0f);
	camera = glm::mat4(1.0f);
	lastX = lastY = 0;
}

glm::vec3 CameraManager::getCameraPosition()
{
	return glm::vec3(
		target.x + radius * sin(phi) * cos(theta),
		target.y + radius * cos(phi),
		target.z + radius * sin(phi) * sin(theta)
	);
}

glm::mat4 CameraManager::getViewMatrix()
{
	glm::vec3 cameraPos = getCameraPosition();
	return glm::lookAt(cameraPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

