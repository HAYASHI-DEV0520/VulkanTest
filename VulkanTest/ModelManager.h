#pragma once
#define GLM_FORCE_RADIANS
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "InputManager.h"

class ModelManager
{
	
public:
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
	void rotate(glm::vec3 axis, float angle);
	void rotateAuto(InputManager*);
	ModelManager();
private:
	glm::mat4 model;
	float duration;
	float angle;
	glm::vec3 axis;
};

