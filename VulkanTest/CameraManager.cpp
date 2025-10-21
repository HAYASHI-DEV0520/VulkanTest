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
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		theta -= xoffset * sensitivity;
		phi -= yoffset * sensitivity;

		if (phi > glm::radians(89.0f)) phi = glm::radians(89.0f);
		if (phi < glm::radians(-89.0f)) phi = glm::radians(-89.0f);
	}
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
		target.x + radius * cos(phi) * sin(theta),
		target.y + radius * sin(phi),
		target.z + radius * cos(phi) * cos(theta)
	);
}

glm::mat4 CameraManager::getViewMatrix()
{
	glm::vec3 cameraPos = getCameraPosition();
	return glm::lookAt(cameraPos, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

