#pragma once
#include <string>

//TODO!!! Delete Later
#include "Resource/ResourceData.h"

namespace Strike {

	class FileLoader {
	public:
		static std::string loadTextFile(const std::string& filePath);
		static TextureData2D genTextureFromImage(const std::string& filePath, const int32_t& desiredBPP = 4,
			const bool& flipVerticle = true);
	};

}