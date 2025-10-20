#include "InputManager.h"


void InputManager::pollEvents(GLFWwindow* window) {
	for (auto& [key, state] : keyStates) {
		state = glfwGetKey(window, key) == GLFW_PRESS;
		if (keyStates[key]) {
			keyEvents[key]();
		}
	}
	
}

void InputManager::registerKey(int key) {
	keyStates[key] = false;
	keyEvents[key] = nullptr;
}

void InputManager::registerEvent(int key, InputEvent event)
{
	keyEvents[key] = event;
}

bool InputManager::isPressed(int key) {
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}