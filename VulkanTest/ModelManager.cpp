#include "ModelManager.h"
#include "InputManager.h"
#include <chrono>
#include <GLFW/glfw3.h>

glm::mat4 ModelManager::getModel()
{
	return model;
}

void ModelManager::setModel(glm::mat4 model)
{
	this->model = model;
}

void ModelManager::rotate(glm::vec3 axis, float angle)
{
	model = glm::rotate(model, angle, axis);
}

void ModelManager::rotateAuto(InputManager *inputManager)
{
	switch (inputManager->getKeyStatus(GLFW_KEY_SPACE)) {
	case InputManager::KeyStatus::PRESSED:
		model = glm::rotate(model, glm::radians(5.0f), axis);
		time.recordTime();
		break;
	case InputManager::KeyStatus::HOLD:
		if (time.getDuration() < 0) {
			break;
		}
		model = glm::rotate(model, time.getDuration() * angle, axis);
		time.recordTime();
		break;
	default:
		break;
	}
}

ModelManager::ModelManager() {
	model = glm::mat4(1.0f);
	duration = 1.0f;
	angle = glm::radians(90.0f);
	axis = glm::vec3(0.0f, 1.0f, 0.0f);
}