#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>

class InputManager
{
public:
	using InputEvent = std::function<void()>;

	void pollEvents(GLFWwindow*);

	void registerKey(int);

	void registerEvent(int, InputEvent);

	bool isPressed(int);
private:
	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, InputEvent> keyEvents;
};

