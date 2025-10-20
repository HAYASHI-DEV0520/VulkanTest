#include "ModelManager.h"

#include <chrono>

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

void ModelManager::rotateAuto(void)
{
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	model = glm::rotate(glm::mat4(1.0f), time * angle, axis);
}

ModelManager::ModelManager() {
	model = glm::mat4(1.0f);
	duration = 1.0f;
	angle = glm::radians(90.0f);
	axis = glm::vec3(0.0f, 1.0f, 0.0f);
}