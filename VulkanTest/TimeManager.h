#pragma once
#include <chrono>

class TimeManager
{
public:
	TimeManager();
	using TimePoint = std::chrono::steady_clock::time_point;
	TimePoint getTime();
	TimePoint recordTime();
	float getDuration();
private:
	TimePoint previousTime;
	bool HasP;
};

