#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "Colour.h"
#include "Texture.h"
#include "Shader.h"

#ifdef STRIKE_OPENGL
#include "OpenGL/GLMaterial.h"
#endif

namespace Strike {

#ifdef STRIKE_OPENGL
	using Material = GLMaterial;
#endif

}
