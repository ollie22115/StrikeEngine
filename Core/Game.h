#pragma once

#include <vector>
#include "Time.h"
#include "EventsAndInput/EventState.h"
#include "EventsAndInput/Input.h"

class Game {
public:
	Game();

	bool onStart();
	bool onFinish();

	~Game();

private:
	enum State {
		PAUSED = 0,
		ACTIVE = 1
	};

	void handleInput();
	void update();

	State gameState;
	EventState eventState;
};