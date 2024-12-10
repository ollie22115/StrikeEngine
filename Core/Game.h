#pragma once

class Game {
public:
	Game();

	bool onStart();
	bool onFinish();

private:
	enum State {
		PAUSED = 0,
		MAIN_MENU = 1,
		COMBAT = 2,
		RESULTS_SCREEN = 3
	};

	
};