#pragma once
#include <string>

//TODO!!! Delete Later
#include "Resource/ResourceData.h"

namespace Strike {

	class FileLoader {
	public:
		static std::string loadTextFile(const std::string& filePath);
	};

}