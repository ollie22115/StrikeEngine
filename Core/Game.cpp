#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <glm/glm.hpp>

void Game::run(){
	glm::vec2 vector;

	while (running) {
		update();
	}
}

/*
void Game::loadScene(Scene& scene){
	//TODO!!! CHECK OVER
	scene.onStart();
	//renderer.loadScene(&scene);
}
*/

void Game::handleInput() {
	//TODO!!! CHECK OVER

	//Handling key and mouse input - NEED TO TEST!!!
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
	//loadedScene->onUpdate(eventState);
	//renderer.drawScene();

	if (eventState.keysPressed.getKeyState(LOC_KEY_A))
		std::cout << "A\n";

	if (eventState.keysPressed.getKeyState(LOC_KEY_B) || eventState.keysHeld.getKeyState(LOC_KEY_B))
		std::cout << "B\n";

	if (eventState.keysReleased.getKeyState(LOC_KEY_C))
		std::cout << "C\n";
}
