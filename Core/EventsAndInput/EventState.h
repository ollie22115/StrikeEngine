#pragma once
#include "StateMap.h"

struct EventState{
	StateMap<uint64_t, 4> keysPressed;
	StateMap<uint64_t, 4> keysHeld;
	StateMap<uint64_t, 4> keysReleased;

	StateMap<uint8_t, 1> mouseButtonsPressed;	//TODO!!! NEED TO PLAN

	StateMap<uint8_t, 1> windowEvents;	//TODO!!! NEED TO PLAN

	bool isKeyPressed(const uint64_t& keyCode);
	bool isKeyPressed(const uint64_t& keyCode) const;

	bool isKeyHeld(const uint64_t& keyCode);
	bool isKeyHeld(const uint64_t& keyCode) const;

	bool isKeyReleased(const uint64_t& keyCode);
	bool isKeyReleased(const uint64_t& keyCode) const;
};