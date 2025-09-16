#pragma once

#include <glm/glm.hpp>

namespace Strike {

	class Colour {
	public:
		static glm::vec4 genColour(float r, float g, float b, float a);
		static glm::vec4 red();
		static glm::vec4 blue();
		static glm::vec4 green();
		static glm::vec4 white();
		static glm::vec4 black();
	};

}