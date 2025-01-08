#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Debugging/Log.h"
#include "EventsAndInput/WindowEventCode.h"

Game::Game() : renderer(&window) {}

void Game::loadScene(Scene& scene) {
	loadedScene = &scene;
	renderer.loadScene(&scene);

	scene.onStart();
}

void Game::run(){
	while (running) {
		if (eventState.windowEvents.getEventState(LOC_WINDOW_CLOSED)) break;

		update();
	}
}

void Game::handleInput() {
	//TODO!!! CHECK OVER

	//Handling key and mouse input - NEED TO TEST!!!
	for (int i = 0; i < 256; i++) {
		uint16_t input = Input::getInput(i);

		if (Input::getInput(i)) {

			if (eventState.keysPressed.getEventState(i) || eventState.keysHeld.getEventState(i)) {
				eventState.keysPressed.unsetEvent(i);
				eventState.keysHeld.setEvent(i);
				eventState.keysReleased.unsetEvent(i);

			} else {
				eventState.keysPressed.setEvent(i);
				eventState.keysHeld.unsetEvent(i);
				eventState.keysReleased.unsetEvent(i);

			}

		} else {

			if (eventState.keysPressed.getEventState(i) || eventState.keysHeld.getEventState(i)) {
				eventState.keysPressed.unsetEvent(i);
				eventState.keysHeld.unsetEvent(i);
				eventState.keysReleased.setEvent(i);

			} else {
				eventState.keysPressed.unsetEvent(i);
				eventState.keysHeld.unsetEvent(i);
				eventState.keysReleased.unsetEvent(i);

			}

		}
	}

#ifdef STRIKE_DEBUG
	Log::logKeyState(eventState);
#endif
}

void Game::handleWindowEvents(){
	if (glfwWindowShouldClose(window)) eventState.windowEvents.setEvent(LOC_WINDOW_CLOSED);
	else {
		eventState.windowEvents.unsetEvent(LOC_WINDOW_MAXIMISE);
		eventState.windowEvents.unsetEvent(LOC_WINDOW_MINIMISE);
	}
	//TODO!!!: expand this function once you have figured out how window events will work

#ifdef STRIKE_DEBUG
	Log::logWindowEventsState(eventState);
#endif
}



void Game::update() {
	glfwPollEvents();
	handleWindowEvents();
	handleInput();
	//loadedScene->onUpdate(eventState);
	renderer.drawScene(window);
}
