#include "StrikePCH.h"
#include "Game.h"

#include "Debugging/Log.h"
#include "Debugging/ProfileTimer.h"
#include "EventsAndInput/WindowEventCode.h"
#include "Utils/Time.h"

namespace Strike {

	Game::Game(const std::string& title) : loadedScene(nullptr), running(false) {

		window = std::shared_ptr<Window>(Window::init(1280, 800, title.c_str()));

		renderer = Renderer::createRenderer();
		renderer->init(window);

		std::shared_ptr<Scene> scene = std::make_shared<Scene>();
		loadScene(scene);
	}

	void Game::loadScene(std::shared_ptr<Scene>& scene) {
		STRIKE_ASSERT(scene, LOG_PLATFORM_CORE, "Scene to load is nullptr!");
		
		if(loadedScene)
			loadedScene->onFinish();

		loadedScene = scene;
		
		scene->load(renderer);
		loadedScene->onStart();
	}

	void Game::run(std::shared_ptr<Scene> firstScene) {

#ifdef STRIKE_DEBUG
		elapsedFrames = 0;
		elapsedTime = 0;
#endif

		if (firstScene)
			loadScene(firstScene);

		running = true;

		prevRecordedTime = currentTimeMS();	//to start off delta time calculations

		while (!window->getEventState().windowClosed) 
			update();
		
	}

	void Game::update() {
		uint64_t deltaTime = currentTimeMS() - prevRecordedTime;
		prevRecordedTime = currentTimeMS();

		window->onUpdate();

#ifdef STRIKE_DEBUG
		elapsedTime += deltaTime;
		elapsedFrames++;
		Log::logKeyState(window->getEventState());
		Log::logMouseButtonState(window->getEventState());
#endif

		loadedScene->onUpdate(window->getEventState(), deltaTime);
		renderer->update();

		renderer->draw(window, loadedScene->getViewMatrix(), loadedScene->getProjectionMatrix());
	}

	Game::~Game() {

	}

}