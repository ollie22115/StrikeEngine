#pragma once
#include <glm/glm.hpp>

namespace Strike {

	struct Transform {
		Transform() = default;
		Transform(const Transform& other) = default;
		Transform(const glm::mat4& other) : transformMatrix(other) {}

		glm::mat4 transformMatrix = glm::mat4(1.0f);

		operator glm::mat4& () { return transformMatrix; }
		operator const glm::mat4& () const { return transformMatrix; }
	};

}