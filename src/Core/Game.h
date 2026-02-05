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

		template<typename T, typename... Args>
		inline ResourcePointer<T> loadRendererResource(const std::string& filePath, Args&&... args) {
			return Renderer::loadResource<T>(filePath, std::forward<Args>(args)...);
		}

		template <typename T, typename... Args>
		static ResourcePointer<T> emplaceRendererResource(const std::string& filePath, Args&&... args){
			return Renderer::emplaceResource<T>(filePath, std::forward<Args>(args)...);
		}

		~Game();

#ifdef STRIKE_DEBUG
		inline uint64_t getElapsedTime() { return elapsedTime; }
		inline uint64_t getElapsedFrames() { return elapsedFrames; }
#endif

	private:
		bool running;

		std::shared_ptr<Window> window;

		uint64_t prevRecordedTime = 0;

		std::shared_ptr<Scene> loadedScene = std::make_shared<Scene>();
		std::unique_ptr<Renderer> renderer;

		void update();

		//DEBUGGING
#ifdef STRIKE_DEBUG
		uint64_t elapsedTime = 0;
		uint64_t elapsedFrames = 0;
#endif
	};
}