#pragma once
#include <string>

namespace Strike {

	class FileLoader {
	public:
		static std::string loadTextFile(const std::string& filePath);
		static void getTextureDimensions(const std::string& filePath, uint32_t& width, uint32_t& height);
	};

}