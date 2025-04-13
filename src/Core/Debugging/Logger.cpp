#include "StrikePCH.h"
#include "Logger.h"

namespace Strike {

	std::string LogColour::getColourCode(uint32_t colourCode) {

		switch (colourCode) {
		case 1:
			return "\033[37m";

		case 2:
			return "\033[90m";

		case 3:
			return "\033[31m";

		case 4:
			return "\033[32m";


		case 5:
			return "\033[34m";

		case 6:
			return "\033[33m";
		}

		return "";

	}
}