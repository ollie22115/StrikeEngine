#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Debugging/Log.h"

Game::Game() : renderer(&window) {}

void Game::loadScene(Scene& scene) {
	loadedScene = &scene;
	renderer.loadScene(&scene);

	scene.onStart();
}

void Game::run(){
	glm::vec2 vector;

	while (running) {
		if (glfwWindowShouldClose(window)) break;
		update();
	}
}

void Game::handleInput() {
	//TODO!!! CHECK OVER

	//Handling key and mouse input - NEED TO TEST!!!
	for (int i = 0; i < 256; i++) {
		uint16_t input = Input::getInput(i);

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

#ifdef STRIKE_DEBUG
	Log::logKeyState(eventState);
#endif
}

void Game::update() {
	glfwPollEvents();	//Here for the time being may want to move it elsewhere
	handleInput();
	//loadedScene->onUpdate(eventState);
	renderer.drawScene(window);
}
