#pragma once

#include "ResourceData.h"
#include "ResourceEntry.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

namespace Strike {

    using ResourceBuffer = std::variant<TextureData2D, ShaderData, MaterialData, TextureAtlasData, FontData>;
    
}