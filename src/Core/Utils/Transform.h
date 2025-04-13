#pragma once

#include <glm/glm.hpp>

namespace Strike {

	class Transform {
	public:
		static glm::mat4 genIdentityMatrix();
		static glm::mat4 genScaleMatrix(const float& x = 1.0f, const float& y = 1.0f, const float& z = 1.0f);
		static glm::mat4 genTranslationMatrix(const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);
		static glm::mat4 genRotationMatrix(const float& angle, const glm::vec3& axis);	//angle is in radians

		static void scale(glm::mat4& matrix, const float& x = 1.0f, const float& y = 1.0f, const float& z = 1.0f);
		static void translate(glm::mat4& matrix, const float& x = 0.0f, const float& y = 0.0f, const float& z = 0.0f);
		static void rotate(glm::mat4& matrix, const float& angle, const glm::vec3& axis);		//angle is in radians
	};

}