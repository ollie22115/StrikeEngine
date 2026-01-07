#pragma once

#include <vector>
#include <string>
#include "ResourceData.h"
#include "Utils/Vector.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

namespace Strike{

    class ResourceLoader {
    public:
        static TextureData2D loadTexture2D(const std::string& filePath, int32_t desiredBitsPerPixel = 4);
        //static TextureAtlasData loadTextureAtlas(const std::string& filePath);
        static ShaderData loadShaderData(const std::string& filePath);
        //static MaterialData loadMaterialData(const std::string& filePath);

        template<typename T>
        static ResourceData loadResourceData(const std::string& filePath);
    };

    template<>
    ResourceData ResourceLoader::loadResourceData<Texture2D>(const std::string& filePath);


    template<>
    ResourceData ResourceLoader::loadResourceData<Shader>(const std::string& filePath);
}