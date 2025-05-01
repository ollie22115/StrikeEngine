#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace Strike {

	class Camera : public Component {
	public:
		Camera(const float& viewWidth = 1280.0f, const float& viewHeight = 800.0f);

		inline float getViewWidth() { return viewWidth; }
		inline float getViewHeight() { return viewHeight; }
		inline void setViewWidth(const float& viewWidth) { this->viewWidth = viewWidth; }
		inline void setViewHeight(const float& viewHeight) { this->viewHeight = viewHeight; }

		glm::mat4 getViewMatrix(const glm::mat4& transform);
		glm::mat4 getProjectionMatrix();

		bool isRenderable() override;

	private:
		float viewWidth, viewHeight;
	};

}