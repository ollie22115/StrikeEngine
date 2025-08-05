#pragma once

#include "Component/Component.h"
#include "Component/RenderableComponent.h"
#include "Component/Transform.h"
#include "Component/CoreObjectData.h"
#include <string>
#include <memory>
#include <entt.hpp>

#include "Utils/TransformMaths.h"

#ifdef STRIKE_DEBUG
#include "Debugging/StrikeDebug.h"
#endif

#define ALL_COMPONENTS Transform,

namespace Strike {

	struct Object {

		Object(/*const Scene* scene, */entt::registry& registry);
		Object(/*const Scene* scene, */entt::registry& registry, const Transform& transform);
		Object(/*const Scene* scene, */entt::registry& registry, const bool& isVisible, const bool& isStatic);
		Object(/*const Scene* scene, */entt::registry& registry, const Transform& transform, const bool& isVisible, const bool& isStatic);

		Object(/*const Scene* scene, */entt::entity objectHandle, entt::registry& registry);

		inline bool isStatic() {
			return getComponent<CoreObjectData>().isStatic;
		}

		inline bool isVisible() {
			return getComponent<CoreObjectData>().isVisible;
		}

		template <typename T>
		inline T& getComponent(){
			return registry->get<T>(objectHandle);
		}

		template<typename T, typename... Args>
		inline T& addComponent(Args&&... args) {
			STRIKE_ASSERT(!hasComponent<T>(), LOG_PLATFORM_CORE, "Object cannot have two of the same component type!");

			return registry->emplace<T>(objectHandle, std::forward<Args>(args)...);
		}

		template <typename T>
		bool hasComponent() {
			return registry->all_of<T>(objectHandle);
		}

		Renderable getRenderable();

		bool isRenderable();

	private:
		//Scene* scene;
		entt::registry* registry;
		entt::entity objectHandle;
	};
}
