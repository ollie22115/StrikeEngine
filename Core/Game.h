#pragma once

#include <vector>
#include "Time.h"
#include "EventsAndInput/EventState.h"
#include "EventsAndInput/Input.h"
#include "Scene.h"

class Game {
public:
	Game();

	void run();
	void loadScene(const Scene& scene);

	~Game();

private:
	enum State {
		PAUSED = 0,
		LOADING = 1,
		ACTIVE = 2,
	};

	State gameState;
	EventState eventState;

	Scene* currentScene;



	void OnFinish();

	void handleInput();
	void update();
};