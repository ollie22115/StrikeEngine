#include "StateMap.h"

namespace Strike {

	std::array<uint64_t, 64>& generateBitShiftPatterns() {
		std::array<uint64_t, 64> bitPatternGenerator;
		uint64_t bitPattern = 1;
		for (int i = 0; i < 64; i++) {
			bitPatternGenerator[i] = bitPattern;
			bitPattern *= 2;
		}

		return bitPatternGenerator;
	}

	const std::array<uint64_t, 64> BIT_PATTERNS = generateBitShiftPatterns();

	const std::array<uint64_t, 64>& getBitPatterns() {
		return BIT_PATTERNS;
	}

}