#include "Game.h"
#include <Windows.h>

void Game::handleInput() {
	//TODO!!!

	//Handling key input - NEED TO TEST!!!
	for (int i = 0; i < 256; i++) {
		if (Input::getInput(i)) {

			if (eventState.keysPressed.getKeyState(i) || eventState.keysHeld.getKeyState(i)) {
				eventState.keysPressed.unsetKey(i);
				eventState.keysHeld.setKey(i);
				eventState.keysReleased.unsetKey(i);

			} else {
				eventState.keysPressed.setKey(i);
				eventState.keysHeld.unsetKey(i);
				eventState.keysReleased.unsetKey(i);

			}

		} else {

			if (eventState.keysPressed.getKeyState(i) || eventState.keysHeld.getKeyState(i)) {
				eventState.keysPressed.unsetKey(i);
				eventState.keysHeld.unsetKey(i);
				eventState.keysReleased.setKey(i);

			} else {
				eventState.keysPressed.unsetKey(i);
				eventState.keysHeld.unsetKey(i);
				eventState.keysReleased.unsetKey(i);

			}

		}
	}
}

void Game::update() {
	handleInput();
	//updateScene();
	//drawScene();
}
