#include "StrikePCH.h"
#include "Object.h"

#include "Utils/Math.h"
#include "Debugging/StrikeDebug.h"
#include "Component/Transform.h"
#include "Component/CoreObjectData.h"

namespace Strike {

	Object::Object(/*const Scene* scene, */entt::registry& registry) : 
		registry(&registry), objectHandle(registry.create()) {
		
		registry.emplace<Transform>(objectHandle);
		registry.emplace<CoreObjectData>(objectHandle);
	}

	Object::Object(entt::registry& registry, const Transform& transform) :
		registry(&registry), objectHandle(registry.create()){

		registry.emplace<Transform>(objectHandle, transform);
		registry.emplace<CoreObjectData>(objectHandle);
	}

	Object::Object(entt::registry& registry, const bool& isVisible, const bool& isStatic) :
		registry(&registry), objectHandle(registry.create()) {

		registry.emplace<Transform>(objectHandle);
		registry.emplace<CoreObjectData>(objectHandle, isVisible, isStatic);
	}

	Object::Object(entt::registry& registry, const Transform& transform, const bool& isVisible, const bool& isStatic) : 
		registry(&registry), objectHandle(registry.create()) {

		registry.emplace<Transform>(objectHandle, transform);
		registry.emplace<CoreObjectData>(objectHandle, isVisible, isStatic);
	}

	Object::Object(entt::entity objectHandle, entt::registry& registry) : 
		registry(&registry), objectHandle(objectHandle) {}

	Renderable Object::getRenderable() {
		//STRIKE_ASSERT(!(hasComponent<MeshRenderer>() && hasComponent<SpriteRenderer>()), LOG_PLATFORM_CORE, "Object cannot have two renderable components!");

		if(hasComponent<SpriteRenderer>())
			return Renderable::createRenderable(getComponent<SpriteRenderer>(), getComponent<Transform>());
		/* else if (hasComponent<MeshRenderer>()) {

		}*/
		else
			return Renderable::createNonRenderable();

		return Renderable();
	}

	bool Object::isRenderable() {
		//STRIKE_ASSERT(!(hasComponent<MeshRenderer>() && hasComponent<SpriteRenderer>()), LOG_PLATFORM_CORE,  "Object cannot have two renderable components!");

		return getRenderable().isRenderable();
	}

}
