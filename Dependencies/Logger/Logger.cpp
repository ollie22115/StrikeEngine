#include "StrikePCH.h"
#include "Logger.h"
#include "Logger.h"
#include "Logger.h"
#include "Logger.h"

namespace Strike {
	std::ostream& operator<<(std::ostream& os, const glm::vec4& vector) {
		os << "vec4(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.a << ")";

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
