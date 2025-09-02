#pragma once

#include "Utils/Vector.h"

#include "ResourceHandle.h"

namespace Strike{

    struct TextureData2D{
        unsigned char* data;
            uint32_t width, height, bitsPerPixel;

        TextureData2D() = default;
        TextureData2D(unsigned char* data, const uint32_t& width, const uint32_t& height, 
            const uint32_t& bitsPerPixel) : 
            data(data), width(width), height(height), bitsPerPixel(bitsPerPixel) {}
        
        ~TextureData2D();
    };


    struct TextureAtlasData{
        struct SubTexture {
            glm::vec4 coords;
        };

        TextureAtlasData() = default;
        TextureAtlasData(const std::string& texturePath, const std::vector<SubTexture> subTextures) :
            texturePath(texturePath), subTextures(subTextures) {}

        std::string texturePath;
        std::vector<SubTexture> subTextures;

        glm::vec4 getUVCoords(const SubTexture& subTexture);
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
        MaterialData(const ResourceHandle& shaderHandle, const ResourceHandle& textureHandle, const glm::vec4& textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)) :
            shaderHandle(shaderHandle), textureHandle(textureHandle), textureCoords(textureCoords) {} 

        ResourceHandle shaderHandle;
        ResourceHandle textureHandle;
        glm::vec4 textureCoords = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    };
}