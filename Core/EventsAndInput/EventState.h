#pragma once
#include "KeyMap.h"

struct EventState{
	EventMap<uint64_t, 4> keysPressed;	//TODO!!! IMPLEMENT
	EventMap<uint64_t, 4> keysHeld;	//TODO!!! IMPLEMENT
	EventMap<uint64_t, 4> keysReleased;		//TODO!!! IMPLEMENT

	EventMap<uint8_t, 1> mouseButtonsPressed;	//TODO!!! NEED TO PLAN

	EventMap<uint8_t, 1> windowEvents;	//TODO!!! NEED TO PLAN
};