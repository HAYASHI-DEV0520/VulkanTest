#include "InputManager.h"
#include <stdexcept>

void InputManager::pollEvents(GLFWwindow* window) {
	for (auto& [key, state] : keyStates) {
		switch (state) {
		case true:
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				keyStatus[key] = KeyStatus::HOLD;
			}
			else {
				keyStatus[key] = KeyStatus::RELEASED;
			}
			break;
		case false:
			if (glfwGetKey(window, key) == GLFW_PRESS) {
				keyStatus[key] = KeyStatus::PRESSED;
			}
			else {
				keyStatus[key] = KeyStatus::UNPRESS;
			}
			break;
		default:
			throw std::runtime_error("unknown key status!");
		}
		state = glfwGetKey(window, key) == GLFW_PRESS;
		if (keyStates[key]) {
			keyEvents[key](this);
		}
	}
	
}

void InputManager::registerKey(int key) {
	keyStates[key] = false;
	keyEvents[key] = nullptr;
	keyStatus[key] = KeyStatus::UNPRESS;
}

void InputManager::registerEvent(int key, InputEvent event)
{
	keyEvents[key] = event;
}

bool InputManager::isPressed(int key) {
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}

InputManager::KeyStatus InputManager::getKeyStatus(int key)
{
	return keyStatus[key];
}
