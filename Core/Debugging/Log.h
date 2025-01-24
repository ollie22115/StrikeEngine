#pragma once
#include "../EventsAndInput/EventState.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>

namespace Strike {

	class Log {
	public:
		static void logKeyState(const EventState& eventState);
		static void logWindowEventsState(const EventState& eventState);
		static void logError(const std::string& errorMsg);

		static void logVector4(glm::vec4 vector);
		static void logVector3(glm::vec3 vector);
		static void logVector2(glm::vec2 vector);

		static std::string logKey(const uint16_t& keyCode);

	private:
	};

}