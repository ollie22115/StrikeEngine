#include "StrikePCH.h"
#include "Object.h"

#include "Component/SpriteRenderer.h"

#include "Debugging/StrikeDebug.h"
#include "Utils/Math.h"

namespace Strike {

	bool Object::containsComponentType(Component::Type componentType) {
		for (auto component : components)
			if (component->getType() == componentType) return true;
		
		return false;
	}

	std::vector<std::shared_ptr<RenderableComponent>> Object::getRenderableComponents() {
		std::vector<std::shared_ptr<RenderableComponent>> renderableComponents;
		
		for (std::shared_ptr<Component>& component : components) if (component->isRenderable())
				renderableComponents.push_back(std::dynamic_pointer_cast<RenderableComponent>(component));
		
		return renderableComponents;
	}

	std::shared_ptr<Component> Object::getComponent(const Component::Type& componentType) {

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
			std::static_pointer_cast<SpriteRenderer>(object.getComponent(Component::Type::SpriteRenderer));

		STRIKE_ASSERT(spriteRenderer != nullptr, LOG_PLATFORM_CORE, "Object does not contain Sprite Renderer Component");

		object.transform = Transform::genIdentityMatrix();

		//Scale
		float scaleX = (float)width / (float)spriteRenderer->getWidth();
		float scaleY = (float)height / (float)spriteRenderer->getHeight();
		Transform::scale(object.transform, scaleX, scaleY);

		//Rotate
		Transform::rotate(object.transform, Math::degreesToRadians(rotation), glm::vec3(0, 0, 1));

		//Translate to coordinates (0, 0) on screen and by x0 and y0
		Transform::translate(object.transform, ((float)spriteRenderer->getWidth() * scaleX) / 2.0f, ((float)spriteRenderer->getHeight() * scaleY) / 2.0f);
		Transform::translate(object.transform, x0, y0);

		//Translate to ND coordinates
		Transform::scale(object.transform, 2.0f/(float)screenWidth, 2.0f/(float)screenHeight);
		Transform::translate(object.transform, -1.0f, -1.0f);
	}
	//TEMPORARY CODE END!!!
}
