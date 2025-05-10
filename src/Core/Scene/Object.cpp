#include "StrikePCH.h"
#include "Object.h"

#include "Component/SpriteRenderer.h"

#include "Utils/Math.h"
#include "Debugging/StrikeDebug.h"

namespace Strike {

	std::vector<std::shared_ptr<RenderableComponent>> Object::getRenderableComponents() {
		std::vector<std::shared_ptr<RenderableComponent>> renderableComponents;
		
		for (std::shared_ptr<Component>& component : components) if (component->isRenderable())
				renderableComponents.push_back(std::dynamic_pointer_cast<RenderableComponent>(component));
		
		return renderableComponents;
	}

	std::shared_ptr<Component> Object::getComponentByEnum(const Component::Type& componentType) {

		for (auto component : components)
			if (component->getType() == componentType) 
				return component;

		return nullptr;
	}

	Object::~Object() {}

	//TODO!!! TEMPORARY CODE
	void fixSpriteOnScreen(Object& object, const uint32_t& x0, const uint32_t& y0, const uint32_t& x1, const uint32_t& y1, const float& rotation,
		const uint32_t& screenWidth, const uint32_t& screenHeight) {

		uint32_t width = x1 - x0;
		uint32_t height = y1 - y0;

		std::shared_ptr<SpriteRenderer> spriteRenderer = 
			std::static_pointer_cast<SpriteRenderer>(object.getComponentByEnum(Component::Type::SpriteRenderer));

		STRIKE_ASSERT(spriteRenderer != nullptr, LOG_PLATFORM_CORE, "Object does not contain Sprite Renderer Component");

		object.transform = TransformMaths::genIdentityMatrix();

		//Scale
		float scaleX = (float)width / (float)spriteRenderer->getWidth();
		float scaleY = (float)height / (float)spriteRenderer->getHeight();
		TransformMaths::scale(object.transform, scaleX, scaleY);

		//Rotate
		TransformMaths::rotate(object.transform, Math::degreesToRadians(rotation), glm::vec3(0, 0, 1));

		//Translate to coordinates (0, 0) on screen and by x0 and y0
		TransformMaths::translate(object.transform, ((float)spriteRenderer->getWidth() * scaleX) / 2.0f, ((float)spriteRenderer->getHeight() * scaleY) / 2.0f);
		TransformMaths::translate(object.transform, x0, y0);
	}
	//TEMPORARY CODE END!!!

	EnttObject::EnttObject(/*const Scene* scene, */entt::registry& registry) : 
		registry(&registry), objectHandle(registry.create()), transform(TransformMaths::genIdentityMatrix()), isVisible(true), isStatic(false) {
	}

	EnttObject::EnttObject(entt::registry& registry, const bool& isVisible, const bool& isStatic) : 
		registry(&registry), objectHandle(registry.create()), transform(TransformMaths::genIdentityMatrix()), isVisible(isVisible), isStatic(isStatic) {}
	
}
