#pragma once
#include <chrono>

namespace Strike {

	//returns the current time in milli seconds
	int64_t currentTimeMS();

	class TimeWindow {
		int32_t elapsedTime;

	public:
		TimeWindow(const int32_t& elapsedTime) : elapsedTime(elapsedTime) {}

		inline void onUpdate(const int32_t& timeStep) { elapsedTime -= timeStep; }

		inline bool isActive() { return elapsedTime > 0; }
		inline bool isFinished() { return !isActive(); }

		inline int32_t getElapsedTime() { return elapsedTime; }
	};

}