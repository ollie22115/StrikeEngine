#pragma once

#include <memory>
#include "EventsAndInput/EventState.h"

#include "Scene/Scene.h"
#include "Window.h"
#include "Rendering/Renderer.h"

namespace Strike {

	class Game {
	public:
		Game(const std::string& title = "Game Window!");

		void loadScene(std::shared_ptr<Scene>& scene);
		void run(std::shared_ptr<Scene> firstScene = nullptr);

		~Game();

	private:
		bool running;

		std::shared_ptr<Window> window;

		uint64_t prevRecordedTime = 0;
		uint64_t elapsedTime = 0;

		std::shared_ptr<Scene> loadedScene;
		std::unique_ptr<Renderer> renderer;

		void update();
	};

	class DefaultScene : public Scene {
	public:
		void onStart() override;
		void onUpdate(const EventState& eventState, const uint64_t& deltaTime) override;
		void onFinish() override;
	};
}