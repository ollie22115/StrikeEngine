#pragma once
#include "../EventsAndInput/EventState.h"
#include <Logger.h>
#include <string>
#include <iostream>

class Log {
public:
	static void logKeyState(const EventState& eventState);

private:
	static std::string logKey(const uint16_t& keyCode);
};