#pragma once

#ifdef STRIKE_OPENGL

#include <glad/glad.h>

#define STRIKE_TEXTURE_WRAP_REPEAT GL_REPEAT
#define STRIKE_TEXTURE_WRAP_CLAMP_TO_BORDER GL_CLAMP_TO_BORDER
#define STRIKE_TEXTURE_FILTER_NEAREST GL_NEAREST
#define STRIKE_TEXTURE_FILTER_LINEAR GL_LINEAR

#else

#define STRIKE_TEXTURE_WRAP_REPEAT 0
#define STRIKE_TEXTURE_WRAP_CLAMP_TO_BORDER 0
#define STRIKE_TEXTURE_FILTER_NEAREST 0
#define STRIKE_TEXTURE_FILTER_LINEAR 0

#endif

namespace Strike{
    
    class TextureParams{
    public:
        enum class Wrap {
            Repeat = STRIKE_TEXTURE_WRAP_REPEAT,
            ClampToBorder = STRIKE_TEXTURE_WRAP_CLAMP_TO_BORDER	
        };

        enum class Filter {
            Nearest = STRIKE_TEXTURE_FILTER_NEAREST,
            Linear = STRIKE_TEXTURE_FILTER_LINEAR
        };
    };

}
