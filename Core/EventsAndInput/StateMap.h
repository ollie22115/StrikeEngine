#pragma once

#include <array>
#include "KeyButtonCode.h"

std::array<uint64_t, 64>& generateBitShiftPatterns();

const std::array<uint64_t, 64>& getBitPatterns();

template <typename T, uint16_t size>
struct StateMap {
	std::array<T, size> keyMaps;

	inline StateMap() { 
		for (int i = 0; i < size; i++) keyMaps[i] = 0;
	}

	inline void setStateTrue(const T& key) {
		uint16_t index = key / (sizeof(T) * 8);
		keyMaps[index] = keyMaps[index] | getBitPatterns()[key % 64];
	}

	inline void setStateFalse(const T& key) {
		uint64_t index = key / (sizeof(T) * 8);
		uint64_t bitUnsetPattern = 0xFFFFFFFFFFFFFFFF - getBitPatterns()[key % 64];
		keyMaps[index] = keyMaps[index] & bitUnsetPattern;
	}

	inline bool getStateOf(const T& state) {
		uint16_t index = state / (sizeof(T) * 8);
		return keyMaps[index] & getBitPatterns()[state % 64];
	}

	inline bool getStateOf(const T& key) const {
		uint16_t index = key / (sizeof(T) * 8);
		return keyMaps[index] & getBitPatterns()[key % 64];
	}
};