#pragma once

#include <vector>
#include <string>
#include "ResourceData.h"
#include "ResourceEntry.h"
#include "ResourceBuffer.h"
#include "Utils/Vector.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"
#include "Rendering/Font.h"

namespace Strike{

    class ResourceLoader {
    public:
        static TextureData2D loadTexture2D(const std::string& filePath, const int32_t& desiredBitsPerPixel = 4);
        //static TextureAtlasData loadTextureAtlas(const std::string& filePath);
        static ShaderData loadShaderData(const std::string& filePath);
        //static MaterialData loadMaterialData(const std::string& filePath);
        static FontData loadFontData(const std::string& filePath, 
            const uint32_t& fontSize, const std::string& charactersToGenerate);

        template<typename T, typename... Args>
        static ResourceBuffer loadResourceData(const std::string& filePath, Args&&... args);
    };


    template<>
    ResourceBuffer ResourceLoader::loadResourceData<Texture2D>(const std::string& filePath);
    template<>
    ResourceBuffer ResourceLoader::loadResourceData<Texture2D>(const std::string& filePath, const int32_t& desiredBitsPerPixel);
    template<>
    ResourceBuffer ResourceLoader::loadResourceData<Shader>(const std::string& filePath);
    template<>
    ResourceBuffer ResourceLoader::loadResourceData<Font>(const std::string& filePath, 
            const uint32_t& fontSize, const std::string& charactersToGenerate);
   




    template<typename T>
    void constructEntry(ResourceEntry<T>& entry, const ResourceBuffer& data, 
        const std::string& filePath, const uint32_t& magicNumber);

    template<>
    void constructEntry(ResourceEntry<Texture2D>& entry, const ResourceBuffer& data,
        const std::string& filePath, const uint32_t& magicNumber);

    template<>
    void constructEntry(ResourceEntry<Shader>& entry, const ResourceBuffer& data, 
        const std::string& filePath, const uint32_t& magicNumber);
}