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

	void FileLoader::getTextureDimensions(const std::string& filePath, uint32_t& width, uint32_t& height) {
		std::ifstream fileStream(filePath);

		int32_t w, h, bPP;

		stbi_load(filePath.c_str(), &w, &h, &bPP, 0);

		width = w;
		height = h;
	}

}