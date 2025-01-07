#include "Log.h"

#include "Logger.h"

void Log::logKeyState(const EventState& eventState){
	//TODO!!! Test

	for (uint16_t i = 0; i < 256; i++) {
		Console::changeConsoleColour(COLOUR::GREEN);
		
		if (eventState.keysPressed.getKeyState(i)) 
			std::cout << logKey(i) << " Key Pressed!\n";
		else if(eventState.keysHeld.getKeyState(i))
			std::cout << logKey(i) << " Key Held!\n";
		else if (eventState.keysReleased.getKeyState(i)) {
			std::cout << logKey(i) << " Key Released!\n";
		}

		Console::changeConsoleColour(COLOUR::WHITE);
	}
}

void Log::logError(const std::string& errorMsg){
	Console::changeConsoleColour(COLOUR::RED);
	std::cout << "ERROR: " << errorMsg << "\n";
	Console::changeConsoleColour(COLOUR::WHITE);
}

std::string Log::logKey(const uint16_t& keyCode){
	//TODO!!!
	switch (keyCode) {
		case LOC_KEY_LEFT:
			return "Left Arrow";
		case LOC_KEY_RIGHT:
			return "Right Arrow";
		case LOC_KEY_UP:
			return "Up Arrow";
		case LOC_KEY_DOWN:
			return "Down Arrow";

		case LOC_KEY_SPACE:
			return "Space";

		case LOC_KEY_0:
			return "0";
		case LOC_KEY_1:
			return "1";
		case LOC_KEY_2:
			return "2";
		case LOC_KEY_3:
			return "3";
		case LOC_KEY_4:
			return "4";
		case LOC_KEY_5:
			return "5";
		case LOC_KEY_6:
			return "6";
		case LOC_KEY_7:
			return "7";
		case LOC_KEY_8:
			return "8";
		case LOC_KEY_9:
			return "9";

		case LOC_KEY_EXCLAMATION:
			return "!";
		case LOC_KEY_COMMA:
			return ",";

		case LOC_KEY_ESCAPE:
			return "ESC";
		case LOC_KEY_F1:
			return "F1";
		case LOC_KEY_F2:
			return "F2";
		case LOC_KEY_F3:
			return "F3";
		case LOC_KEY_F4:
			return "F4";
		case LOC_KEY_F5:
			return "F5";
		case LOC_KEY_F6:
			return "F6";
		case LOC_KEY_F7:
			return "F7";
		case LOC_KEY_F8:
			return "F8";
		case LOC_KEY_F9:
			return "F9";
		case LOC_KEY_F10:
			return "F10";
		case LOC_KEY_F11:
			return "F11";
		case LOC_KEY_F12:
			return "F12";

		case LOC_KEY_INSERT:
			return "Insert";
		case LOC_KEY_DELETE:
			return "Delete";
		case LOC_KEY_TAB:
			return "Tab";
		case LOC_KEY_ICOMMA:
			return "`";
		case LOC_KEY_SHIFT:
			return "Shift";
		case LOC_KEY_CAPS_LOCK:
			return "Caps Lock";
		case LOC_KEY_LEFT_CONTROL:
			return "Left Control";
		case LOC_KEY_RIGHT_CONTROL:
			return "Right Control";
		case LOC_KEY_WINDOWS:
			return "Windows";
		case LOC_KEY_LEFT_ALT:
			return "Left Alt";
		case LOC_KEY_RIGHT_ALT:
			return "Right Alt";
		case LOC_KEY_FN:
			return "FN";
		case LOC_KEY_DQUOTE:
			return "\"";
		case LOC_KEY_POUND:
			return "£";
		case LOC_KEY_DOLLAR:
			return "$";
		case LOC_KEY_PERCENTAGE:
			return "%";
		case LOC_KEY_AMPERSAND:
			return "&";
		case LOC_KEY_DASH:
			return "-";
		case LOC_KEY_UNDERLINE:
			return "_";
		case LOC_KEY_LBRACKET:
			return "(";
		case LOC_KEY_RBRAKCET:
			return ")";
		case LOC_KEY_ANGULAR_LBRACKET:
			return "<";
		case LOC_KEY_ANGULAR_RBRACKET:
			return ")";

		case LOC_KEY_A:
			return "A";
		case LOC_KEY_B:
			return "B";
		case LOC_KEY_C:
			return "C";
		case LOC_KEY_D:
			return "D";
		case LOC_KEY_E:
			return "E";
		case LOC_KEY_F:
			return "F";
		case LOC_KEY_G:
			return "G";
		case LOC_KEY_H:
			return "H";
		case LOC_KEY_I:
			return "I";
		case LOC_KEY_J:
			return "J";
		case LOC_KEY_K:
			return "K";
		case LOC_KEY_L:
			return "L";
		case LOC_KEY_M:
			return "M";
		case LOC_KEY_N:
			return "N";
		case LOC_KEY_O:
			return "O";
		case LOC_KEY_P:
			return "P";
		case LOC_KEY_Q:
			return "Q";
		case LOC_KEY_R:
			return "R";
		case LOC_KEY_S:
			return "S";
		case LOC_KEY_T:
			return "T";
		case LOC_KEY_U:
			return "U";
		case LOC_KEY_V:
			return "V";
		case LOC_KEY_W:
			return "W";
		case LOC_KEY_X:
			return "X";
		case LOC_KEY_Y:
			return "Y";
		case LOC_KEY_Z:
			return "Z";
	}

	return "";
}
