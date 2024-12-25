#pragma once

#include <array>
#include "KeyButtonCode.h"

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

template <typename T, uint16_t size>
struct KeyMap {
	//TODO!!! Replace uint64_t with the template T in some areas of the code

	std::array<T, size> keyMaps;

	inline KeyMap() { 
		for (int i = 0; i < size; i++) keyMaps[i] = 0;
	}

	inline void setKey(const uint64_t& key) {
		uint16_t index = key / (sizeof(T) * 8);
		uint64_t bitSetPattern = 1;
		keyMaps[index] = keyMaps[index] | BIT_PATTERNS[key % 64];
	}

	inline void unsetKey(const uint64_t& key) {
		uint64_t index = key / (sizeof(T) * 8);
		uint64_t bitUnsetPattern = 0xFFFFFFFFFFFFFFFF - BIT_PATTERNS[key % 64];
		keyMaps[index] = keyMaps[index] & bitUnsetPattern;
	}

	inline bool getKeyState(const uint64_t& key) {
		uint16_t index = key / (sizeof(T) * 8);
		uint64_t bitCheckPattern = BIT_PATTERNS[key % 64];
		return keyMaps[index] & bitCheckPattern;
	}

	inline bool getKeyState(const uint64_t& key) const {
		uint16_t index = key / (sizeof(T) * 8);
		uint64_t bitCheckPattern = 1;
		for (int i = 0; i < key % 64; i++) bitCheckPattern *= 2;
		return keyMaps[index] & bitCheckPattern;
	}
};