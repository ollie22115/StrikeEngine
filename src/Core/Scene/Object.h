#pragma once

#include "Component/Component.h"
#include "Component/RenderableComponent.h"
#include "Component/Transform.h"
#include <string>
#include <memory>
#include <entt.hpp>

#include "Utils/TransformMaths.h"

#include "Component/SpriteRenderer.h"
#include "Component/Camera.h"
#include "Component/Bounds.h"

#define ALL_COMPONENTS Transform,

namespace Strike {

	struct EnttObject {
		Transform transform = TransformMaths::genIdentityMatrix();
		bool isVisible = true;
		const bool isStatic = false;

		EnttObject(/*const Scene* scene, */entt::registry& registry);

		EnttObject(/*const Scene* scene, */entt::registry& registry, const bool& isVisible, const bool& isStatic);

		template <typename T>
		inline T& getComponent(){
			return registry->get<T>(objectHandle);
		}

		template<>
		inline Transform& getComponent<Transform>() {
			return transform;
		}

		template<typename T, typename... Args>
		inline T& addComponent(Args&&... args) {
			return registry->emplace<T>(objectHandle, std::forward<Args>(args)...);
		}

		template <typename T>
		bool hasComponent() {
			return registry->all_of<T>(objectHandle);
		}

		~EnttObject() {
			registry->destroy(objectHandle);
		}

	private:
		//Scene* scene;
		entt::entity objectHandle;
		entt::registry* registry;
	};


	struct Object {
		std::string id;
		glm::mat4 transform;
		std::vector<std::shared_ptr<Component>> components;
		bool isVisible;
		const bool isStatic;

		Object(const std::string& id, const bool& isStatic = false, const bool& isVisible = true, const glm::mat4& transform = TransformMaths::genIdentityMatrix()) :
			id(id), transform(transform), isVisible(isVisible), isStatic(isStatic) {
		}

		inline void addComponent(const std::shared_ptr<Component>& component) { components.push_back(component); }

		std::vector<std::shared_ptr<RenderableComponent>> getRenderableComponents();

		std::shared_ptr<Component> getComponentByEnum(const Component::Type& componentType);

		template <typename T>
		bool hasComponent();

		template<typename T>
		std::shared_ptr<T> getComponent();

		template <>
		std::shared_ptr<SpriteRenderer> getComponent<SpriteRenderer>();

		template <>
		std::shared_ptr<Camera> getComponent<Camera>();

		template <>
		std::shared_ptr<Bounds> getComponent<Bounds>();

		~Object();
	};

	template <typename T>
	inline bool Object::hasComponent() {
		return getComponent<T>() != nullptr;
	}

	template<typename T>
	inline std::shared_ptr<T> Object::getComponent() {
		return nullptr;
	}

	template<>
	inline std::shared_ptr<SpriteRenderer> Object::getComponent<SpriteRenderer>() {
		return std::static_pointer_cast<SpriteRenderer>(getComponentByEnum(Component::Type::SpriteRenderer));
	}

	template<>
	inline std::shared_ptr<Camera> Object::getComponent<Camera>() {
		return std::static_pointer_cast<Camera>(getComponentByEnum(Component::Type::Camera));
	}

	template<>
	inline std::shared_ptr<Bounds> Object::getComponent<Bounds>() {
		return std::static_pointer_cast<Bounds>(getComponentByEnum(Component::Type::Bounds));
	}

	//TODO!!! THROWAWAY CODE
	void fixSpriteOnScreen(Object& object, const uint32_t& x0, const uint32_t& y0, const uint32_t& x1, const uint32_t& y1, const float& rotation = 0.0f,
		const uint32_t& screenWidth = 1280.0f, const uint32_t& screenHeight = 800.0f);
}
