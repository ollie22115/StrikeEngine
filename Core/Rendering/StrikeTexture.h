#pragma once
#include <string>

namespace Strike {

	struct StrikeTexture {
		std::string filePath;
		bool mipmap;

		inline StrikeTexture(const std::string& filePath, const bool& mipmap = false) : filePath(filePath), mipmap(mipmap) {}
	};

}