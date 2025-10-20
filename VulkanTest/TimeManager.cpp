#include "TimeManager.h"

TimeManager::TimeManager()
{
	HasP = false;
}

TimeManager::TimePoint TimeManager::getTime() {
	return std::chrono::high_resolution_clock::now();
}

TimeManager::TimePoint TimeManager::recordTime()
{
	HasP = true;
	previousTime = std::chrono::high_resolution_clock::now();
	return std::chrono::high_resolution_clock::now();
}

float TimeManager::getDuration()
{
	if (!HasP) {
		return -1.0f;
	}
	return std::chrono::duration<float, std::chrono::seconds::period>(std::chrono::high_resolution_clock::now() - previousTime).count();
}
