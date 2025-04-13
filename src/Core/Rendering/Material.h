#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Colour.h"

namespace Strike {

	struct Material {

		std::string texturePath;	//TODO!!! For now will only use one texture in material
		std::string shaderPath;

		bool operator ==(const Material& other) const;
	};

}
