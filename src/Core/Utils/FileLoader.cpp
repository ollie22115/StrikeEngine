#include "StrikePCH.h"
#include "FileLoader.h"

#include <stb_image.h>

#include <fstream>
#include <sstream>

namespace Strike {

	std::string FileLoader::loadTextFile(const std::string& filePath) {
		std::ifstream fileStream(filePath);
		std::stringstream stringStream;

		std::string line;
		while (std::getline(fileStream, line)) 
			stringStream << line << "\n";
		
		return stringStream.str();
	}

    TextureData2D FileLoader::genTextureFromImage(const std::string &filePath, const int& desiredBPP,
		 const bool& flipVerticle) {
		
		int32_t width, height, bitsPerPixel;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, desiredBPP);

#ifdef STRIKE_DEBUG
		if (!data) Log::logError(LOG_PLATFORM_OPENGL, "stbi Failed to load image");
#endif

        return TextureData2D(data, width, height, bitsPerPixel);
    }

}