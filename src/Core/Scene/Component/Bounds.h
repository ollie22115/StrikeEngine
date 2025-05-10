#pragma once

#include "Component.h"
#include <glm/glm.hpp>

#define BOUNDS_COMPONENTS BoxBounds, RadiusBounds

namespace Strike {

	/*
	
	struct BoxBounds {
		BoxBounds() = default;
		BoxBounds(BoxBounds& other) = default;
		BoxBounds(const float& width, const float& height) : width(width), height(height) {}
		
		static boxCast(const BoxBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1);
		static rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY);
		static rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		float width = 1.0f;
		float height = 1.0f;
	};

	struct RadiusBounds {
		RadiusBounds() = default;
		RadiusBounds(RadiusBounds& other) = default;
		RadiusBounds(const float& radius) : radius(radius) 

		static boxCast(const RadiusBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1);
		static rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY);
		static rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance);

		float radius = 1.0f;
	};

	*/

	class Bounds : public Component {
	public:
		Bounds() : Component(Component::Type::Bounds) {};

		virtual bool boxCast(const glm::mat4& transform, const float& x0, const float& y0, const float& x1, const float& y1) = 0;
		virtual bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY) = 0;
		virtual bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY, 
			const float& maxDistance) = 0;
	};

	class RectangleBounds : public Bounds{
	public:
		RectangleBounds() : Bounds() {};
		
		bool boxCast(const glm::mat4& transform, const float& x0, const float& y0, const float& x1, const float& y1) override;
		bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY) override;
		bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY, 
			const float& maxDistance) override;

		bool isRenderable() override {
			return false;
		}
	};

	class CircleBounds : public Bounds {
	public:
		CircleBounds() : Bounds() {};

		bool boxCast(const glm::mat4& transform, const float& x0, const float& y0, const float& x1, const float& y1) override;
		bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY) override;
		bool rayCast(const glm::mat4& transform, const float& oX, const float& oY, const float& dX, const float& dY,
			const float& maxDistance) override;

		bool isRenderable() override {
			return false;
		}
	};
}