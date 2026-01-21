#pragma once

#include <variant>
#include "Utils/Vector.h"

#include "ResourceHandle.h"

#include <MaxRectsBinPack.h>

namespace Strike{

    struct TextureData2D{
        
        std::unique_ptr<unsigned char[]> data;
        uint32_t width, height, bitsPerPixel;


        TextureData2D(const uint32_t& desiredBitsPerPixel = 4, const uint32_t& width = 1, const uint32_t& height = 1);
        TextureData2D(std::unique_ptr<unsigned char[]>& data, const uint32_t& width, const uint32_t& height, 
            const uint32_t& bitsPerPixel);
        TextureData2D(const TextureData2D& other);
        TextureData2D(TextureData2D&& other);
        
        
        ~TextureData2D() = default;
    };


    struct TextureAtlasData{
        struct SubTexture {
            TextureData2D textureData;
            uint32_t x, y, width, height;

            SubTexture(TextureData2D& textureData, 
                const uint32_t& x, const uint32_t& y, const uint32_t& width, const uint32_t& height) :
                textureData(textureData), x(x), y(y), width(width), height(height) {}

            ~SubTexture() = default;
        };

        TextureAtlasData() = default;
        TextureAtlasData(const uint32_t& width, const uint32_t& height, const uint32_t& bitsPerPixel);

        uint32_t width, height, bitsPerPixel = 4;
        std::vector<SubTexture> subTextures;

        bool addSubTexture(TextureData2D& textureData, const uint32_t& borderSize = 2);

    private:
        
        rbp::MaxRectsBinPack binPacker; 
    };


    struct ShaderData{
        ShaderData() = default;
        ShaderData(const std::string& vertexSrc, const std::string& fragSrc) :
            vertexSrc(vertexSrc), fragSrc(fragSrc) {}

        std::string vertexSrc;
        std::string fragSrc;
    };

    struct MaterialData{
        MaterialData() = default;
        MaterialData(const std::string& shaderPath, const std::string& texturePath, const glm::vec4& textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) :
            shaderPath(shaderPath), texturePath(texturePath), textureCoords(textureCoords) {}

        std::string shaderPath;
        std::string texturePath;
        
        glm::vec4 textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    };

    using ResourceData = std::variant<TextureData2D, ShaderData, MaterialData, TextureAtlasData>;

}