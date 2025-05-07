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

		virtual void onStart() = 0;	//method that is called when scene is first loaded
		virtual void onUpdate(const EventState& eventState, const uint64_t& deltaTime) = 0;		//method that is called every frame upon every update call
		virtual void onFinish() = 0;	//method that is called just before scene is unloaded

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		bool boxCast(const float& x0, const float& y0, const float& x1, const float& y1);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		~Scene() = default;

	protected:
		std::vector<std::shared_ptr<Object>> objects;
		std::shared_ptr<Object> cameraObj;
	};

}