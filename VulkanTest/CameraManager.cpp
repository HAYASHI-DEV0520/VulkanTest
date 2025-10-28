#include "CameraManager.h"

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
		theta -= xoffset * sensitivity;
		phi += yoffset * sensitivity;

		if (phi > glm::radians(89.0f)) phi = glm::radians(89.0f);
		if (phi < glm::radians(-89.0f)) phi = glm::radians(-89.0f);
	}
}

void CameraManager::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	radius -= yoffset * 0.3f;
	if (radius > 9.0f) {
		radius = 9.0f;
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
			target += glm::normalize(glm::cross(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 0.0f, 1.0f)), target - getCameraPosition())) * time.getDuration() * movement;
			break;
		case GLFW_KEY_S:
			target -= glm::normalize(glm::cross(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 0.0f, 1.0f)), target - getCameraPosition())) * time.getDuration() * movement;
			break;
		case GLFW_KEY_A:
			target -= glm::normalize(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 0.0f, 1.0f))) * time.getDuration() * movement;
			break;
		case GLFW_KEY_D:
			target += glm::normalize(glm::cross(target - getCameraPosition(), glm::vec3(0.0f, 0.0f, 1.0f))) * time.getDuration() * movement;
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
	radius = 3;
	target = glm::vec3(0.0f);
	camera = glm::mat4(1.0f);
	lastX = lastY = 0;
}

glm::vec3 CameraManager::getCameraPosition()
{
	return glm::vec3(
		target.x + radius * sin(phi) * cos(theta),
		target.y + radius * sin(phi) * sin(theta),
		target.z + radius * cos(phi)
	);
}

glm::mat4 CameraManager::getViewMatrix()
{
	glm::vec3 cameraPos = getCameraPosition();
	return glm::lookAt(cameraPos, target, glm::vec3(0.0f, 0.0f, 1.0f));
}

