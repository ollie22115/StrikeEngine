#include "StrikePCH.h"
#include "Log.h"

#include "EventsAndInput/KeyButtonCode.h"
#include "EventsAndInput/MouseButtonCode.h"
#include <sstream>

namespace Strike {
	
	static std::bitset<16> blockers;

	void Log::blockLogMessages(const uint32_t& category) {
		blockers.set(category);
	}

	void Log::unBlockLogMessages(const uint32_t& category) {
		blockers.reset(category);
	}

	void Log::logKeyState(const EventState& eventState) {
		if (blockers[LOG_TYPE_INPUT_EVENT])
			return;

		std::cout << LogColour::green();

		for (uint16_t i = 0; i < STRIKE_TOTAL_KEYS; i++) {

			if (eventState.isKeyPressed(i) && !blockers[LOG_TYPE_KEY_PRESSED_EVENT]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logKey(i) << " Key Pressed!\n";
			}
			if (eventState.isKeyHeld(i) && !blockers[LOG_TYPE_KEY_HELD_EVENT]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logKey(i) << " Key Held!\n";
			}
			if (eventState.isKeyReleased(i) && !blockers[LOG_TYPE_KEY_RELEASED_EVENT]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logKey(i) << " Key Released!\n";
			}

		}


		std::cout << LogColour::white();
	}

	void Log::logMouseButtonState(const EventState& eventState) {
		if (blockers[LOG_TYPE_INPUT_EVENT])
			return;

		std::cout << LogColour::green();

		for (uint16_t i = 0; i < STRIKE_TOTAL_MOUSE_BUTTONS; i++) {

			if (eventState.isMouseButtonPressed(i) && !blockers[LOG_TYPE_MOUSE_BUTTON_PRESSED]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logMouseButton(i) << " Button Pressed, " << "x: " << eventState.mouseState.xPos << " y, " << eventState.mouseState.yPos << "\n";
			}
			if (eventState.isMouseButtonHeld(i) && !blockers[LOG_TYPE_MOUSE_BUTTON_HELD]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logMouseButton(i) << " Button Held, " << "x: " << eventState.mouseState.xPos << " y, " << eventState.mouseState.yPos << "\n";
			}
			if (eventState.isMouseButtonReleased(i) && !blockers[LOG_TYPE_MOUSE_BUTTON_RELEASED]) {
				logPlatform(LOG_PLATFORM_CORE);
				std::cout << logMouseButton(i) << " Button Released, " << "x: " << eventState.mouseState.xPos << " y, " << eventState.mouseState.yPos << "\n";
			}

		}

		std::cout << LogColour::white();
	}

	void Log::logError(const uint32_t& platform, const std::string& errorMsg) {
		std::cout << LogColour::red();

		logPlatform(platform);

		std::cout << errorMsg << LogColour::white() << "\n";
	}

	void Log::logError(const uint32_t& platform, const std::initializer_list<std::string>& errorMsg) {	
		std::cout << LogColour::red();

		logPlatform(platform);

		for (auto& msg : errorMsg)
			std::cout << msg;

		std::cout << LogColour::white() << "\n";
	}

	void Log::logWarning(const uint32_t& platform, const std::string& warningMsg) {
		std::cout << LogColour::yellow();

		logPlatform(platform);

		std::cout << warningMsg << LogColour::white() << "\n";
	}

	void Log::logWarning(const uint32_t& platform, const std::initializer_list<std::string>& warningMsg) {
		std::cout << LogColour::yellow();

		logPlatform(platform);

		for (auto& msg : warningMsg)
			std::cout << msg;

		std::cout << LogColour::white() << "\n";
	}

	void Log::log(const uint32_t& platform, const std::string& msg) {
		std::cout << LogColour::white();

		logPlatform(platform);

		std::cout << msg << LogColour::white() << "\n";
	}

	void Log::log(const uint32_t& platform, const std::initializer_list<std::string>& msg) {
		std::cout << LogColour::white();

		logPlatform(platform);

		for (auto& msg : msg)
			std::cout << msg;

		std::cout << LogColour::white() << "\n";
	}

	void Log::logMessage(const std::string& msg) {
		std::cout << msg;
	}

	void Log::logMessage(const std::initializer_list<std::string>& msg) {
		for (auto& msg : msg)
			std::cout << msg;
	}

	std::string Log::logKey(const uint16_t& keyCode) {
		switch (keyCode) {
		case STRIKE_KEY_LEFT:
			return "[Left Arrow]";
		case STRIKE_KEY_RIGHT:
			return "[Right Arrow]";
		case STRIKE_KEY_UP:
			return "[Up Arrow]";
		case STRIKE_KEY_DOWN:
			return "[Down Arrow]";

		case STRIKE_KEY_SPACE:
			return "[Space]";

		case STRIKE_KEY_0:
			return "0";
		case STRIKE_KEY_1:
			return "1";
		case STRIKE_KEY_2:
			return "2";
		case STRIKE_KEY_3:
			return "3";
		case STRIKE_KEY_4:
			return "4";
		case STRIKE_KEY_5:
			return "5";
		case STRIKE_KEY_6:
			return "6";
		case STRIKE_KEY_7:
			return "7";
		case STRIKE_KEY_8:
			return "8";
		case STRIKE_KEY_9:
			return "9";

		case STRIKE_KEY_EXCLAMATION:
			return "!";
		case STRIKE_KEY_COMMA:
			return ",";

		case STRIKE_KEY_ESCAPE:
			return "[ESC]";
		case STRIKE_KEY_F1:
			return "[F1]";
		case STRIKE_KEY_F2:
			return "[F2]";
		case STRIKE_KEY_F3:
			return "[F3]";
		case STRIKE_KEY_F4:
			return "[F4]";
		case STRIKE_KEY_F5:
			return "[F5]";
		case STRIKE_KEY_F6:
			return "[F6]";
		case STRIKE_KEY_F7:
			return "[F7]";
		case STRIKE_KEY_F8:
			return "[F8]";
		case STRIKE_KEY_F9:
			return "[F9]";
		case STRIKE_KEY_F10:
			return "[F10]";
		case STRIKE_KEY_F11:
			return "[F11]";
		case STRIKE_KEY_F12:
			return "[F12]";

		case STRIKE_KEY_INSERT:
			return "[Insert]";
		case STRIKE_KEY_DELETE:
			return "[Delete]";
		case STRIKE_KEY_TAB:
			return "[Tab]";
		case STRIKE_KEY_ICOMMA:
			return "`";
		case STRIKE_KEY_LEFT_SHIFT:
			return "[Left Shift]";
		case STRIKE_KEY_RIGHT_SHIFT:
			return "[Right Shift]";
		case STRIKE_KEY_CAPS_LOCK:
			return "[Caps Lock]";
		case STRIKE_KEY_LEFT_CONTROL:
			return "[Left Control]";
		case STRIKE_KEY_RIGHT_CONTROL:
			return "[Right Control]";
		case STRIKE_KEY_LEFT_WINDOWS:
			return "Left Windows";
		case STRIKE_KEY_RIGHT_WINDOWS:
			return "Right Windows";
		case STRIKE_KEY_LEFT_ALT:
			return "[Left Alt]";
		case STRIKE_KEY_RIGHT_ALT:
			return "[Right Alt]";
		case STRIKE_KEY_FN:
			return "[FN]";
		case STRIKE_KEY_DQUOTE:
			return "\"";
		case STRIKE_KEY_POUND:
			return "£";
		case STRIKE_KEY_DOLLAR:
			return "$";
		case STRIKE_KEY_PERCENTAGE:
			return "%";
		case STRIKE_KEY_AMPERSAND:
			return "&";
		case STRIKE_KEY_DASH:
			return "-";
		case STRIKE_KEY_UNDERLINE:
			return "_";
		case STRIKE_KEY_LBRACKET:
			return "(";
		case STRIKE_KEY_RBRAKCET:
			return ")";
		case STRIKE_KEY_ANGULAR_LBRACKET:
			return "<";
		case STRIKE_KEY_ANGULAR_RBRACKET:
			return ">";
		case STRIKE_KEY_BACKSPACE:
			return "[BackSpace]";
		case STRIKE_KEY_SEMICOLON:
			return ";";
		case STRIKE_KEY_SLASH:
			return "/";
		case STRIKE_KEY_FULLSTOP:
			return ".";
		case STRIKE_KEY_APOSTROPHE:
			return "'";
		case STRIKE_KEY_ENTER:
			return "[Enter]";

		case STRIKE_KEY_A:
			return "A";
		case STRIKE_KEY_B:
			return "B";
		case STRIKE_KEY_C:
			return "C";
		case STRIKE_KEY_D:
			return "D";
		case STRIKE_KEY_E:
			return "E";
		case STRIKE_KEY_F:
			return "F";
		case STRIKE_KEY_G:
			return "G";
		case STRIKE_KEY_H:
			return "H";
		case STRIKE_KEY_I:
			return "I";
		case STRIKE_KEY_J:
			return "J";
		case STRIKE_KEY_K:
			return "K";
		case STRIKE_KEY_L:
			return "L";
		case STRIKE_KEY_M:
			return "M";
		case STRIKE_KEY_N:
			return "N";
		case STRIKE_KEY_O:
			return "O";
		case STRIKE_KEY_P:
			return "P";
		case STRIKE_KEY_Q:
			return "Q";
		case STRIKE_KEY_R:
			return "R";
		case STRIKE_KEY_S:
			return "S";
		case STRIKE_KEY_T:
			return "T";
		case STRIKE_KEY_U:
			return "U";
		case STRIKE_KEY_V:
			return "V";
		case STRIKE_KEY_W:
			return "W";
		case STRIKE_KEY_X:
			return "X";
		case STRIKE_KEY_Y:
			return "Y";
		case STRIKE_KEY_Z:
			return "Z";
		}

		return "";
	}

	std::string Log::logMouseButton(const uint16_t& mouseButton) {
		
		switch (mouseButton) {
			case STRIKE_MOUSE_BUTTON_LEFT: return "[Left Mouse Button]";
			case STRIKE_MOUSE_BUTTON_RIGHT: return "[Right Mouse Button]";
			case STRIKE_MOUSE_BUTTON_MIDDLE: return "[Middle Mouse Button]";
		}
		
		return "";
	}

	void Log::logPlatform(const uint32_t& platform) {
		switch (platform) {
		case LOG_PLATFORM_CORE: std::cout << "Core: ";
			break;

		case LOG_PLATFORM_WINDOWS: std::cout << "Windows: ";
			break;

		case LOG_PLATFORM_OPENGL: std::cout << "OpenGL: ";
			break;

		case LOG_PLATFORM_GLFW: std::cout << "GLFW: ";
			break;
		}
	}
}