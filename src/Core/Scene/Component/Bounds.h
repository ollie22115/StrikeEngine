#pragma once

#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>

#define BOUNDS_COMPONENTS BoxBounds, RadiusBounds

namespace Strike {

	struct BoxBounds {
		BoxBounds() = default;
		BoxBounds(BoxBounds& other) = default;
		BoxBounds(const float& width, const float& height) : width(width), height(height) {}
		
		static bool boxCast(const BoxBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1);
		static bool rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY);
		static bool rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		float width = 1.0f;
		float height = 1.0f;
	};

	struct RadiusBounds {
		RadiusBounds() = default;
		RadiusBounds(RadiusBounds& other) = default;
		RadiusBounds(const float& radius) : radius(radius) {};

		static bool boxCast(const RadiusBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1);
		static bool rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY);
		static bool rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		float radius = 1.0f;
	};

}