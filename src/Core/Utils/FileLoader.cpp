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

}