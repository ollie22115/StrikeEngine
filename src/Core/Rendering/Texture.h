#pragma once

#ifdef STRIKE_OPENGL
#include "OpenGL/GLTexture.h"
#endif

#define STRIKE_TEXTURE2D 1

namespace Strike {
	
#ifdef STRIKE_OPENGL
	using Texture2D = GLTexture2D;
#endif

}