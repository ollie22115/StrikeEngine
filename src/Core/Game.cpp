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

		std::shared_ptr<Scene> scenePtr = std::make_shared<DefaultScene>();
		loadScene(scenePtr);
	}

	void Game::loadScene(std::shared_ptr<Scene>& scene) {
		if(loadedScene) 
			loadedScene->onFinish();

		loadedScene = scene;
		
		renderer->loadScene(loadedScene);

		loadedScene->onStart();
	}

	void Game::run(std::shared_ptr<Scene> firstScene) {

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

		TopDownCamera& camera = loadedScene->getCamera();
		renderer->draw(window, camera.getViewMatrix(), camera.getProjectionMatrix());
	}

	Game::~Game() {

	}

	void DefaultScene::onStart() {
		Log::log(LOG_PLATFORM_CORE, "Scene Started!");
	}

	void DefaultScene::onUpdate(const EventState& eventState, const uint64_t& deltaTime) {
	}

	void DefaultScene::onFinish() {
		Log::log(LOG_PLATFORM_CORE, "Scene Finished!");
	}

}