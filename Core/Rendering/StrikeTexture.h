#pragma once
#include <string>

namespace Strike {

	struct StrikeTexture {
		std::string filePath;

		inline StrikeTexture(const std::string& filePath) : filePath(filePath) {}
	};

}