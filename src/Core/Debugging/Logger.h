#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace Strike {

	class LogColour {
	public:
		inline static LogColour black() {
			return LogColour(0);
		}
		inline static LogColour white() {
			return LogColour(1);
		}
		inline static LogColour gray() {
			return LogColour(2);
		}
		inline static LogColour red() {
			return LogColour(3);
		}
		inline static LogColour green() {
			return LogColour(4);
		}
		inline static LogColour blue() {
			return LogColour(5);
		}
		inline static LogColour yellow() {
			return LogColour(6);
		}

		friend std::ostream& operator<<(std::ostream& os, const LogColour& colour) {
			os << getColourCode(colour.colourCode);
			return os;
		}

	private:
		uint32_t colourCode;

		inline LogColour(uint32_t colourCode) : colourCode(colourCode) {}

		static std::string getColourCode(uint32_t colourCode);
	};

	std::ostream& operator<<(std::ostream& os, const glm::vec4& vector);
	std::ostream& operator<<(std::ostream& os, const glm::vec3& vector);

	std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix);
}