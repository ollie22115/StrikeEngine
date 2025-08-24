#pragma once

#define STRIKE_SHADER_VERTEX		1
#define STRIKE_SHADER_PIXEL			2

#ifdef STRIKE_OPENGL
#include "OpenGL/GLProgram.h"
#endif

namespace Strike {

#ifdef STRIKE_OPENGL
	using Shader = GLProgram;
#endif

}