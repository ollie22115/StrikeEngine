#pragma once

#include <vector>
#include "EventsAndInput/EventState.h"
#include "EventsAndInput/Input.h"
#include <iostream>
//#include "Scene.h"
//#include "Rendering/Renderer.h"

class Game {
public:
	Game() = default;

	void run();

private:
	enum State {
		PAUSED = 0,
		LOADING = 1,
		ACTIVE = 2,
	};

	bool running;

	State gameState;
	EventState eventState;

	void handleInput();
	void update();
};