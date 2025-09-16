#pragma once
#include <initializer_list>
#include "Logger.h"
#include "../EventsAndInput/EventState.h"

//platforms
#define LOG_PLATFORM_CORE							1	//Log that has been triggered from any code within the core engine library
#define LOG_PLATFORM_WINDOWS						2	//Log that has been triggered from any windows specific code
#define LOG_PLATFORM_OPENGL							3	//Log that has been triggered from any OpenGL specific code
#define LOG_PLATFORM_GLFW							4	//Log that has been triggered from any GLFW specific code

//type
#define LOG_TYPE_INPUT_EVENT						5
#define LOG_TYPE_KEY_PRESSED_EVENT					6
#define LOG_TYPE_KEY_HELD_EVENT						7
#define LOG_TYPE_KEY_RELEASED_EVENT					8		
#define LOG_TYPE_MOUSE_BUTTON_PRESSED				9		
#define LOG_TYPE_MOUSE_BUTTON_HELD					10		
#define LOG_TYPE_MOUSE_BUTTON_RELEASED				11
#define LOG_TYPE_RENDERER_EVENT						12

namespace Strike {

	class Log {
	public:
		static void blockLogMessages(const uint32_t& category);
		static void unBlockLogMessages(const uint32_t& category);

		static void logError(const uint32_t& platform, const std::string& errorMsg);
		static void logError(const uint32_t& platform, const std::initializer_list<std::string>& errorMsg);

		static void logWarning(const uint32_t& platform, const std::string& warningMsg);
		static void logWarning(const uint32_t& platform, const std::initializer_list<std::string>& warningMsg);

		static void log(const uint32_t& platform, const std::string& msg);
		static void log(const uint32_t& platform, const std::initializer_list<std::string>& msg);

		static void logMessage(const std::string& msg);
		static void logMessage(const std::initializer_list<std::string>& msg);

		static void logKeyState(const EventState& eventState);
		static void logMouseButtonState(const EventState& eventState);
		static void logWindowEventsState(const EventState& eventState);	//TODO!!!

		static std::string logKey(const uint16_t& keyCode);
		static std::string logMouseButton(const uint16_t& mouseButton);

	private:
		static void logPlatform(const uint32_t& platform);

	};

}