#include "StrikePCH.h"
#include "Logger.h"

namespace Strike {

	std::string LogColour::getColourCode(uint32_t colourCode) {

		switch (colourCode) {
		case 1:
			return "\033[37m";

		case 2:
			return "\033[90m";

		case 3:
			return "\033[31m";

		case 4:
			return "\033[32m";


		case 5:
			return "\033[34m";

		case 6:
			return "\033[33m";
		}

		return "";

	}

	std::ostream& operator<<(std::ostream& os, const glm::vec4& vector) {
		os << "vec4(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.a << ")";

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const glm::vec3& vector) {
		os << "vec3(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const glm::mat4& matrix) {
		os << "mat4(";

		os << matrix[0][0] << ", " << matrix[0][1] << ", " << matrix[0][2] << ", " << matrix[0][3] << "\n";

		for (int i = 1; i < 3; i++)
			os << "     " << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << ", " << matrix[i][3] << "\n";

		os << "     " << matrix[3][0] << ", " << matrix[3][1] << ", " << matrix[3][2] << ", " << matrix[3][3] << ")";

		return os;
	}
}