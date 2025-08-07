#pragma once
#include <string>

namespace Strike {

	struct TextureData{
		unsigned char* data;
		uint32_t width, height, bitsPerPixel;

		TextureData() = default;
		TextureData(unsigned char* data, const uint32_t& width, const uint32_t& height, 
			const uint32_t& bitsPerPixel) : 
			data(data), width(width), height(height), bitsPerPixel(bitsPerPixel) {}
		~TextureData();
	};

	class FileLoader {
	public:
		static std::string loadTextFile(const std::string& filePath);
		static TextureData genTextureFromImage(const std::string& filePath, const int32_t& desiredBPP = 4,
			const bool& flipVerticle = true);
	};

}