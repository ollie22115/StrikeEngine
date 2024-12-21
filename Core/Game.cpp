#include "Game.h"

KeyCode Game::getInput(){
	//at some point upgrade this method so it can
	// A) record multiple keys and
	// B) record the state of each of those keys 
	// 
	//TODO!!! TEST

	for (const KeyCode& key : keyListeners) {
		KeyState state = getKeyState(key);
		if (state != KeyState::IDLE) return key;
	}

	return KeyCode::KEY_NONE;
}
