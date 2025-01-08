#pragma once
#include "../EventsAndInput/EventState.h"
#include <string>
#include <iostream>

class Log {
public:
	static void logKeyState(const EventState& eventState);
	static void logWindowEventsState(const EventState& eventState);
	static void logError(const std::string& errorMsg);


private:
	static std::string logKey(const uint16_t& keyCode);
};