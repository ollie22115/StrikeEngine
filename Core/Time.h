#pragma once
#include <chrono>

//returns the current time
int64_t currentTime() {
	auto time = std::chrono::system_clock::now();
	auto duration = time.time_since_epoch();

	return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

class TimeWindow {
	int32_t elapsedTime;

public:
	inline TimeWindow(int32_t& elapsedTime) : elapsedTime(elapsedTime) {};

	inline void onUpdate(const int32_t& timeStep) { elapsedTime -= timeStep; }

	inline bool isActive() { return elapsedTime > 0; }
	inline bool isFinished() { !isActive(); }

	inline int32_t elapsedTime() { return elapsedTime; }
};