#include "Logger.h"

namespace Strike {

	void Console::logText(const char* text, const COLOUR& colour, const bool& newLine) {
		changeConsoleColour(colour);
		std::cout << text;
		if (newLine) std::cout << "\n";
	}

	void Console::logText(const std::string& text, const COLOUR& colour) {
		changeConsoleColour(colour);
		std::cout << text;
	}

	void Console::changeConsoleColour(const COLOUR& colour) {
		switch (colour) {
		case COLOUR::WHITE:
			std::cout << "\033[37m";
			break;

		case COLOUR::GRAY:
			std::cout << "\033[90m";
			break;

		case COLOUR::RED:
			std::cout << "\033[31m";
			break;

		case COLOUR::GREEN:
			std::cout << "\033[32m";
			break;

		case COLOUR::BLUE:
			std::cout << "\033[34m";
			break;

		case COLOUR::YELLOW:
			std::cout << "\033[33m";
			break;
		}
	}

	void Console::resetColour() {
		changeConsoleColour(COLOUR::WHITE);
	}

	void Console::clearConsole() {
		system("cls");
	}

}