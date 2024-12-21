#pragma once

#include <array>
#include "KeyButtonCode.h"

struct KeyMap {
	std::array<uint64_t, 4> keyMaps;

	inline KeyMap() { 
		for (int i = 0; i < 4; i++) keyMaps[i] = 0;
	}

	inline void setKey(const uint64_t& key) {
		uint16_t index = (key / 64) - 1;
		uint64_t bitSetPattern = 1;
		for (int i = 0; i < key % 64;) bitSetPattern *= 2;
		keyMaps[index] = keyMaps[index] | bitSetPattern;
	}
	inline void unsetKey(const uint64_t& key) {
		uint16_t index = (key / 64) - 1;
		uint64_t bitUnsetPattern = 1;
		for (int i = 0; i < key - (index + 1) * 64; i++) bitUnsetPattern *= 2;
		bitUnsetPattern = 0xFFFFFFFFFFFFFFFF - bitUnsetPattern;
		keyMaps[index] = keyMaps[index] & bitUnsetPattern;
	}

	inline bool getKeyState(const uint64_t& key) {
		uint16_t index = (key / 64) - 1;
		uint64_t bitCheckPattern = 1;
		for (int i = 0; i < key % 64;) bitCheckPattern *= 2;
		return keyMaps[index] & bitCheckPattern;
	}

	inline bool getKeyState(const uint64_t& key) const {
		uint16_t index = (key / 64) - 1;
		uint64_t bitCheckPattern = 1;
		for (int i = 0; i < key % 64;) bitCheckPattern *= 2;
		return keyMaps[index] & bitCheckPattern;
	}
};