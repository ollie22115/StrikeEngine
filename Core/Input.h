#pragma once

enum class KeyCode {
	KEY_NONE = 0,

	//directional keys
	KEY_UP = 1,
	KEY_DOWN = 2,
	KEY_LEFT = 3,
	KEY_RIGHT = 4,

	//spacebar
	KEY_SPACE = 5
};

enum class KeyState {
	IDLE,
	PRESSED,
	HOLD,
	RELEASED
};

bool isDirectionalKey(const KeyCode& keyCode) {
	switch (keyCode) {
		case KeyCode::KEY_UP:
			return true;
		case KeyCode::KEY_DOWN:
			return true;
		case KeyCode::KEY_LEFT:
			return true;
		case KeyCode::KEY_RIGHT:
			return true;
	}

	return false;
}

KeyState getKeyState(const KeyCode& keyCode) {
	//TODO!!!
	return KeyState::IDLE;
}

