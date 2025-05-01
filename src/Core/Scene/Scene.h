#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EventsAndInput/EventState.h"
#include "Object.h"

namespace Strike {

	//describes a scene to be rendered
	class Scene {
		//TODO!!!
	public:
		inline Scene() = default;

		inline std::vector<std::shared_ptr<Object>>& getObjects() { return objects; }

		virtual void onStart() = 0;	//method that is called when a scene is being loaded
		virtual void onUpdate(const EventState& eventState, const uint64_t& deltaTime) = 0;		//method that is called every frame upon every update call
		virtual void onFinish() = 0;	//method that is called when a scene is being unloaded

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		~Scene() = default;

	protected:
		std::vector<std::shared_ptr<Object>> objects;
		std::shared_ptr<Object> cameraObj;
	};

}