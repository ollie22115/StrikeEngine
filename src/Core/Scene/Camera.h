#pragma once

#include <glm/glm.hpp>

namespace Strike {

	class TopDownCamera {
	public:

		TopDownCamera(const float& viewWidth = 1280.0f, const float& viewHeight = 800.0f) : 
			transform(glm::mat4(1.0f)), viewWidth(viewWidth), viewHeight(viewHeight) {};

		inline glm::mat4& getTransform() { return transform; }
		inline float getViewWidth() { return viewWidth; }
		inline float getViewHeight() { return viewHeight; }
		inline void setViewWidth(const float& viewWidth) { this->viewWidth = viewWidth; }
		inline void setViewHeight(const float& viewHeight) { this->viewHeight = viewHeight; }

		void moveCamera(float x = 0.0f, float y = 0.0f, float z = 0.0f);

		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();

	private:
		glm::mat4 transform;
		float viewWidth, viewHeight;
	};

}