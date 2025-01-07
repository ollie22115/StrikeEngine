#pragma once

#include <iostream>
#include <string>

enum class COLOUR {
	WHITE,
	GRAY,
	RED,
	GREEN,
	BLUE,
	YELLOW
};

struct Console {
	static void logText(const char* text, const COLOUR& colour = COLOUR::WHITE, const bool& newLine = true);
	static void logText(const std::string& text, const COLOUR& colour = COLOUR::WHITE);

	static void changeConsoleColour(const COLOUR& colour);

	static void resetColour();

	static void clearConsole();
};