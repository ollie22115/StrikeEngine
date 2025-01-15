#pragma once
#include <chrono>

//returns the current time in milli seconds
int64_t currentTimeMS();

class TimeWindow {
	int32_t elapsedTime;

public:
	inline TimeWindow(int32_t& elapsedTime) : elapsedTime(elapsedTime) {}

	inline void onUpdate(const int32_t& timeStep) { elapsedTime -= timeStep; }

	inline bool isActive() { return elapsedTime > 0; }
	inline bool isFinished() { !isActive(); }

	inline int32_t getElapsedTime() { return elapsedTime; }
};