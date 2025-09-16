#include "StrikePCH.h"
#include "Bounds.h"
#include "Utils/TransformMaths.h"

namespace Strike {

	bool BoxBounds::boxCast(const BoxBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1) {
		std::array<glm::vec4, 4> boundsVertices = { transform * glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f), transform * glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			transform * glm::vec4(0.5f, 0.5f, 0.0f, 1.0f), transform * glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f) };

		if (x0 > boundsVertices[2].x || x1 < boundsVertices[0].x || y1 < boundsVertices[0].y || y0 > boundsVertices[2].y)
			return false;
		else
			return true;
	}

	bool BoxBounds::rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY) {
		//TODO!!!
		return false;
	}

	bool BoxBounds::rayCast(const BoxBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY, const float& maxDistance) {
		//TODO!!!
		return false;
	}



	bool RadiusBounds::boxCast(const RadiusBounds& bounds, const Transform& transform, const float& x0, const float& y0, const float& x1, const float& y1) {
		//TODO!!! Test

		glm::vec4 origin = glm::vec4(TransformMaths::getTranslations(transform), 1.0f);
		glm::vec3 scales = TransformMaths::getScales(transform);
		float r = std::max(scales.x, std::min(scales.y, scales.z));

		float closestX = std::max(x0, std::min(origin.x, x1));
		float closestY = std::max(y1, std::min(origin.y, y0));

		float dx = closestX - origin.x;
		float dy = closestY - origin.y;

		return (dx * dx + dy * dy) <= (r * r);
	}

	bool RadiusBounds::rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY) {
		//TODO!!!
		return false;
	}

	bool RadiusBounds::rayCast(const RadiusBounds& bounds, const Transform& transform, const float& oX, const float& oY, const float& dX, const float& dY, const float& maxDistance) {
		//TODO!!!
		return false;
	}

}
