#include "EventState.h"

namespace Strike {

	bool EventState::isKeyPressed(const uint64_t& keyCode) {
		return keysPressed.getStateOf(keyCode);
	}
	bool EventState::isKeyPressed(const uint64_t& keyCode) const {
		return keysPressed.getStateOf(keyCode);
	}

	bool EventState::isKeyHeld(const uint64_t& keyCode) {
		return keysHeld.getStateOf(keyCode);
	}
	bool EventState::isKeyHeld(const uint64_t& keyCode) const {
		return keysHeld.getStateOf(keyCode);
	}

	bool EventState::isKeyReleased(const uint64_t& keyCode) {
		return keysReleased.getStateOf(keyCode);
	}
	bool EventState::isKeyReleased(const uint64_t& keyCode) const {
		return keysReleased.getStateOf(keyCode);
	}

}