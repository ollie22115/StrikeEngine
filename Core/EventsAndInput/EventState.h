#pragma once
#include "KeyMap.h"

struct EventState{
	KeyMap<uint64_t, 4> keysPressed;	//TODO!!! IMPLEMENT
	KeyMap<uint64_t, 4> keysHeld;	//TODO!!! IMPLEMENT
	KeyMap<uint64_t, 4> keysReleased;		//TODO!!! IMPLEMENT

	KeyMap<uint8_t, 1> mouseButtonsPressed;	//TODO!!! NEED TO PLAN

	KeyMap<uint8_t, 1> windowEvents;	//TODO!!! NEED TO PLAN
};