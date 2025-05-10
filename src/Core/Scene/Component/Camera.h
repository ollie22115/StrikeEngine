#pragma once
#include "Component.h"
#include "Transform.h"
#include <glm/glm.hpp>

namespace Strike {

	struct EnttCamera{
		EnttCamera() = default;
		EnttCamera(const EnttCamera& other) = default;
		EnttCamera(const float& viewWidth, const float& viewHeight) : viewWidth(viewWidth), viewHeight(viewHeight) {};

		float viewWidth = 1280.0f, viewHeight = 800.0f;

		static glm::mat4 getViewMatrix(Transform& transform);
		static glm::mat4 getProjectionMatrix(const EnttCamera& camera);
	};

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