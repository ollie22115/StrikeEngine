#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EventsAndInput/EventState.h"
#include "Object.h"

namespace Strike {

	using OnStartCallback = std::function<void()>;
	using OnUpdateCallback = std::function<void(const EventState&, const uint64_t&)>;
	using OnFinishCallback = std::function<void()>;

	//describes a scene to be rendered
	class Scene {
		//TODO!!!
	public:
		Scene() = default;
		Scene(const OnStartCallback& onStartCallback, const OnUpdateCallback& onUpdateCallback, const OnFinishCallback& onFinishCallback);

		inline std::vector<std::shared_ptr<Object>>& getObjects() { return objects; }
		inline std::shared_ptr<EnttObject>& getCamera() { return cameraObj; }//Temporary until I figure out what to do with camera

		inline void setOnStartCallback(const OnStartCallback& onStartCallback) {
			this->onStartCallback = onStartCallback;
		}

		inline void setOnUpdateCallback(const OnUpdateCallback& onUpdateCallback) {
			this->onUpdateCallback = onUpdateCallback;
		}

		inline void setOnFinishCallback(const OnFinishCallback& onFinishCallback) {
			this->onFinishCallback = onFinishCallback;
		}

		void onStart(); //method that is called when scene is first loaded
		void onUpdate(const EventState& eventState, const uint64_t& deltaTime); //called every frame
		void onFinish(); //method that is called just before scene is unloaded

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		bool boxCast(const float& x0, const float& y0, const float& x1, const float& y1);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		~Scene() = default;

	protected:
		static void defaultOnStartCallback();
		static void defaultOnUpdateCallback(const EventState& eventState, const uint64_t& deltaTime);
		static void defaultOnFinishCallback();

		OnStartCallback onStartCallback = defaultOnStartCallback;
		OnUpdateCallback onUpdateCallback = defaultOnUpdateCallback;
		OnFinishCallback onFinishCallback = defaultOnFinishCallback;
		std::vector<std::shared_ptr<Object>> objects;
		
		entt::registry registry;
		std::shared_ptr<EnttObject> cameraObj = std::make_shared<EnttObject>(registry, true, false);
	};

}