#pragma once
#include "KeyMap.h"

struct EventState{
	KeyMap<uint64_t, 4> keysPressed;
	KeyMap<uint64_t, 4> keysHeld;
	KeyMap<uint64_t, 4> keysReleased;

	KeyMap<uint8_t, 1> mouseButtonsPressed;	//TODO!!! UNIMPLEMENTED

	KeyMap<uint8_t, 1> windowEvents;	//TODO!!! UNIMPLEMENTED
};