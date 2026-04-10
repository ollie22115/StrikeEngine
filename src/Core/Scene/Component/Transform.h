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
		inline glm::vec4 operator*(const glm::vec4& other) const  { return transformMatrix * other; }

		inline glm::vec3 getTranslation() const {
			//TODO!!! check this
			return glm::vec3(transformMatrix[3][0], transformMatrix[3][1], transformMatrix[3][2]);
		}

		inline glm::vec3 getScale() const {
			//TODO!!! check this
			return glm::vec3(transformMatrix[0][0], transformMatrix[1][1], transformMatrix[2][2]);
		}

		/*
		inline glm::vec3 getRotation() const {
			//TODO!!!
		}
		*/
	};

}