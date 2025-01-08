#pragma once

#include <vector>
#include "EventsAndInput/EventState.h"
#include "EventsAndInput/Input.h"
#include <iostream>
#include "Scene.h"
#include "Rendering/Renderer.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>

class Game {
public:
	Game();

	void loadScene(Scene& scene);
	void run();

private:
	enum State {
		PAUSED = 0,
		LOADING = 1,
		ACTIVE = 2,
	};

	bool running;

	GLFWwindow* window;

	Scene* loadedScene;
	SceneRenderer renderer;

	State gameState;
	EventState eventState;

	void handleInput();
	void handleWindowEvents();
	void update();
};