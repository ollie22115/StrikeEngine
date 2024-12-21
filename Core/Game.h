#pragma once

#include <vector>
#include "Time.h"
#include "Input.h"

class Game {
public:
	Game();

	bool onStart();
	bool onFinish();

	~Game();

private:
	enum State {
		PAUSED = 0,
		MAIN_MENU = 1,
		COMBAT = 2,
		RESULTS_SCREEN = 3
	};

	std::vector<KeyCode> keyListeners;		//the keys game program will "listen to"

	KeyCode getInput();
};