#pragma once

#include "Resource/ResourceData.h"

#ifdef STRIKE_OPENGL
#include "OpenGL/GLTextureAtlas.h"
#endif

namespace Strike {

#ifdef STRIKE_OPENGL
    using TextureAtlas = GLTextureAtlas;
#endif

}