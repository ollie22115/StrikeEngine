#pragma once

#include "Component/Component.h"
#include "Component/RenderableComponent.h"
#include <string>
#include <memory>

#include "Utils/Transform.h"

namespace Strike {

	struct Object {
		std::string id;
		glm::mat4 transform;
		std::vector<std::shared_ptr<Component>> components;
		bool isVisible;
		const bool isStatic;

		Object(const std::string& id, const glm::mat4& transform = Transform::genIdentityMatrix(), const bool& isVisible = true, const bool& isStatic = false) :
			id(id), transform(transform), isVisible(isVisible), isStatic(isStatic) {
		}

		inline void addComponent(const std::shared_ptr<Component>& component) { components.push_back(component); }

		std::vector<std::shared_ptr<RenderableComponent>> getRenderableComponents();

		std::shared_ptr<Component> getComponent(const Component::Type& componentType);

		bool containsComponentType(Component::Type componentType);

		~Object();
	};


	//TODO!!! THROWAWAY CODE
	void fixSpriteOnScreen(Object& object, const uint32_t& x0, const uint32_t& y0, const uint32_t& x1, const uint32_t& y1, 
		const uint32_t& screenWidth = 1280.0f, const uint32_t& screenHeight = 800.0f);
}