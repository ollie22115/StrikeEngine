#pragma once

#include <variant>
#include "Utils/Vector.h"
#include "Rendering/TextureParams.h"

#include "ResourceHandle.h"

#include <MaxRectsBinPack.h>
#include "FreeType.h"

namespace Strike{

    struct TextureData2D {
        
        std::unique_ptr<unsigned char[]> data;
        uint32_t width, height, bitsPerPixel, desiredInternalBitsPerPixel;
        TextureParams::Wrap wrapS, wrapT = TextureParams::Wrap::Repeat;
        TextureParams::Filter minFilter, magFilter = TextureParams::Filter::Linear;


        TextureData2D(const uint32_t& desiredBitsPerPixel = 4, const uint32_t& width = 1, const uint32_t& height = 1,
            const TextureParams::Wrap& wrapS = TextureParams::Wrap::Repeat, const TextureParams::Wrap& wrapT = TextureParams::Wrap::Repeat,
            const TextureParams::Filter& minFilter = TextureParams::Filter::Linear, const TextureParams::Filter& magFilter = TextureParams::Filter::Linear);

        TextureData2D(std::unique_ptr<unsigned char[]>& data, const uint32_t& width, const uint32_t& height,
            const uint32_t& bitsPerPixel, const uint32_t& desiredInternalBitsPerPixel = 4,
            const TextureParams::Wrap& wrapS = TextureParams::Wrap::Repeat, const TextureParams::Wrap& wrapT = TextureParams::Wrap::Repeat,
            const TextureParams::Filter& minFilter = TextureParams::Filter::Linear, const TextureParams::Filter& magFilter = TextureParams::Filter::Linear);

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

        //TODO!!! change to unique_ptr of TextureData2D
        bool addSubTexture(TextureData2D& textureData, const uint32_t& borderSize = 2);

    private:
        
        rbp::MaxRectsBinPack binPacker; 
    };

    //FontData uses Freetype, 
    struct FontData {
        struct GlyphData{
            TextureData2D textureData;
            uint32_t advance, bearingX, bearingY, pitch;

            GlyphData() = default;

            GlyphData(std::unique_ptr<unsigned char[]>& data, const uint32_t& width, const uint32_t& height,
                const uint32_t& advance, const uint32_t& bearingX, const uint32_t& bearingY, const uint32_t& pitch) :
                    textureData(data, width, height, 1, 1, TextureParams::Wrap::ClampToBorder, TextureParams::Wrap::ClampToBorder), 
                    advance(advance), bearingX(bearingX), bearingY(bearingY), pitch(pitch) {}

            GlyphData(GlyphData&& other);

            ~GlyphData() = default;
        };
        
        FontData() = default;

        FontData(FontData&& other);

        FontData(std::unique_ptr<FT_Library>& freeTypeHandle, std::unique_ptr<FT_Face>& freeTypeFace, const uint32_t& fontSize, const std::string& charactersToGenerate = "") :
            freeTypeHandle(std::move(freeTypeHandle)), freeTypeFaceHandle(std::move(freeTypeFace)), charactersToGenerate(charactersToGenerate) {};

        GlyphData operator[](const char& c);

        ~FontData();

        uint32_t fontSize = 32;
        std::string charactersToGenerate = "";

    private:
        std::unique_ptr<FT_Library> freeTypeHandle;
        std::unique_ptr<FT_Face> freeTypeFaceHandle;
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

}