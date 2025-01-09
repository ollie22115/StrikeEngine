#pragma once
#include "KeyMap.h"

struct EventState{
	StateMap<uint64_t, 4> keysPressed;	//TODO!!! IMPLEMENT
	StateMap<uint64_t, 4> keysHeld;	//TODO!!! IMPLEMENT
	StateMap<uint64_t, 4> keysReleased;		//TODO!!! IMPLEMENT

	StateMap<uint8_t, 1> mouseButtonsPressed;	//TODO!!! NEED TO PLAN

	StateMap<uint8_t, 1> windowEvents;	//TODO!!! NEED TO PLAN
};