#pragma once
#include "../EventsAndInput/EventState.h"
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "../Rendering/RenderableComponent.h"
#include <Buffer.h>
#include <VertexLayout.h>

namespace Strike {

	class Log {
	public:
		static void logKeyState(const EventState& eventState);
		static void logWindowEventsState(const EventState& eventState);
		static void logError(const std::string& errorMsg);

		static void logVector4(glm::vec4 vector);
		static void logVector3(glm::vec3 vector);
		static void logVector2(glm::vec2 vector);

		static void logMatrix4(glm::mat4 matrix);

		static void logObjectTransformedPos(RenderableObject& object);

		static void logVertexBuffer(const uint32_t& offset, const uint32_t& size, glm::mat4& transform);
		static void logIndexBuffer(const uint32_t offset, const uint32_t size);

		static std::string logKey(const uint16_t& keyCode);

	private:
	};

}