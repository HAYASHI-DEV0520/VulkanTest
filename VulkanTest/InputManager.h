#pragma once

#include <GLFW/glfw3.h>
#include <unordered_map>
#include <functional>

class InputManager
{
public:
	using InputEvent = std::function<void(InputManager*)>;

	void pollEvents(GLFWwindow*);

	void registerKey(int);

	void registerEvent(int, InputEvent);

	bool isPressed(int);

	enum class KeyStatus {
		PRESSED, HOLD, RELEASED, UNPRESS
	};

	KeyStatus getKeyStatus(int);
private:
	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, InputEvent> keyEvents;
	std::unordered_map<int, KeyStatus> keyStatus;
};

