#pragma once

#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "EventsAndInput/EventState.h"
#include "Object.h"

namespace Strike {

	class Renderer;

	//describes a scene to be rendered
	class Scene {
		//TODO!!!
	public:
		Scene() = default;

		inline std::vector<std::shared_ptr<Object>>& getObjects() { return objects; }
		inline std::shared_ptr<Object>& getCamera() { return cameraObj; }//Temporary until I figure out what to do with cameraz

		std::shared_ptr<Object> createObject(const bool& isStatic = false);

		void load(std::unique_ptr<Renderer>& renderer);

		virtual void onStart(); //method that is called when scene is first loaded
		virtual void onUpdate(const EventState& eventState, const uint64_t& deltaTime); //called every frame
		virtual void onFinish(); //method that is called just before scene is unloaded

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

		bool boxCast(const float& x0, const float& y0, const float& x1, const float& y1);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY);
		bool rayCast(const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		~Scene() = default;

	protected:
		std::vector<std::shared_ptr<Object>> objects;
		
		entt::registry registry;
		std::shared_ptr<Object> cameraObj = std::make_shared<Object>(registry, true, false);
	};

}