#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Colour.h"

namespace Strike {

	struct Material {

		Material() = default;
		Material(const std::string& texturePath, const std::string& shaderPath) :
			texturePath(texturePath), shaderPath(shaderPath) {};
		Material(const Material& other) = default;

		std::string texturePath = "Default";	//TODO!!! For now will only use one texture in material
		std::string shaderPath;

		bool operator ==(const Material& other) const;
	};

}
