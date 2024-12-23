#pragma once
#include <cstdint>

#include "KeyButtonCode.h"

class Input {
public:
	static uint16_t getInput(uint16_t input);

private:
	static uint16_t keyCodeLOCtoWindows(uint16_t windowsCode);
};