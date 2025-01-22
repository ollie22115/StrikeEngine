#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Debugging/Log.h"
#include "EventsAndInput/WindowEventCode.h"
#include "Utils/Time.h"

namespace Strike {

	Game::Game() : renderer(&window), loadedScene(nullptr), running(false) {}

	void Game::loadScene(Scene& scene) {
		loadedScene = &scene;
		renderer.loadScene(&scene);

		loadedScene->onStart();
	}

	void Game::run() {
		currentTime = currentTimeMS();
		prevRecordedTime = currentTime;

		running = true;

		while (running) {
			if (eventState.windowEvents.getStateOf(LOC_WINDOW_CLOSED)) break;

			update();
		}
	}

	void Game::handleInput() {
		//TODO!!! CHECK OVER

		//Handling key and mouse input - NEED TO TEST!!!
		for (uint16_t i = 0; i < LOC_TOTAL_KEYS; i++) {
			uint16_t input = Input::getInput(i);

			if (Input::getInput(i)) {

				if (eventState.keysPressed.getStateOf(i) || eventState.keysHeld.getStateOf(i)) {
					eventState.keysPressed.setStateFalse(i);
					eventState.keysHeld.setStateTrue(i);
					eventState.keysReleased.setStateFalse(i);

				}
				else {
					eventState.keysPressed.setStateTrue(i);
					eventState.keysHeld.setStateFalse(i);
					eventState.keysReleased.setStateFalse(i);

				}

			}
			else {

				if (eventState.keysPressed.getStateOf(i) || eventState.keysHeld.getStateOf(i)) {
					eventState.keysPressed.setStateFalse(i);
					eventState.keysHeld.setStateFalse(i);
					eventState.keysReleased.setStateTrue(i);

				}
				else {
					eventState.keysPressed.setStateFalse(i);
					eventState.keysHeld.setStateFalse(i);
					eventState.keysReleased.setStateFalse(i);

				}

			}
		}

#ifdef STRIKE_DEBUG
		Log::logKeyState(eventState);
#endif
	}

	void Game::handleWindowEvents() {
		if (glfwWindowShouldClose(window)) eventState.windowEvents.setStateTrue(LOC_WINDOW_CLOSED);
		else {
			eventState.windowEvents.setStateFalse(LOC_WINDOW_MAXIMISE);
			eventState.windowEvents.setStateFalse(LOC_WINDOW_MINIMISE);
		}
		//TODO!!!: expand this function once you have figured out how window events will work

#ifdef STRIKE_DEBUG
		Log::logWindowEventsState(eventState);
#endif
	}

	void Game::update() {
		currentTime = currentTimeMS();
		uint64_t timeStep = currentTime - prevRecordedTime;
		prevRecordedTime = currentTime;
		elapsedTime += timeStep;

		handleWindowEvents();
		handleInput();
		loadedScene->onUpdate(eventState, timeStep);
		renderer.drawScene(window);
		glfwPollEvents();
	}

}