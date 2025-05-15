#pragma once
#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>

namespace Strike {

	struct Camera{
		Camera() = default;
		Camera(const Camera& other) = default;
		Camera(const float& viewWidth, const float& viewHeight) : viewWidth(viewWidth), viewHeight(viewHeight) {};

		float viewWidth = 1280.0f, viewHeight = 800.0f;

		static glm::mat4 getViewMatrix(Transform& transform);
		static glm::mat4 getProjectionMatrix(const Camera& camera);
	};

}