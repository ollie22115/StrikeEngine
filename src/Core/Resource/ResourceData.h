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

        static TextureData2D createBorderedTexture(const TextureData2D& textureData, const uint32_t& borderSizePx = 2);
    };


    struct TextureAtlasData{
        TextureAtlasData() = default;
        TextureAtlasData(const uint32_t& width, const uint32_t& height, const uint32_t& bitsPerPixel);

        //TODO!!! change to unique_ptr of TextureData2D
        inline void addSubTexture(TextureData2D& textureData, const uint32_t& borderSizePx = 2) {
            subTextures.push_back(TextureData2D::createBorderedTexture(textureData, borderSizePx));
        };
        
        uint32_t width, height, bitsPerPixel = 4;
        std::vector<TextureData2D> subTextures;
    };

    //FontData uses Freetype, 
    struct FontData {
        struct GlyphData{
            TextureData2D textureData;
            uint32_t advance, bearingX, bearingY, pitch;

            GlyphData() = default;

            GlyphData(std::unique_ptr<unsigned char[]> data, const uint32_t& width, const uint32_t& height,
                const uint32_t& advance, const uint32_t& bearingX, const uint32_t& bearingY, const uint32_t& pitch) :
                    textureData(data, width, height, 1, 1, TextureParams::Wrap::ClampToBorder, TextureParams::Wrap::ClampToBorder), 
                    advance(advance), bearingX(bearingX), bearingY(bearingY), pitch(pitch) {}

            GlyphData(GlyphData&& other);

            ~GlyphData() = default;
        };
        
        FontData() = default;

        FontData(std::unique_ptr<FreeTypeFace> freeTypeFace, const uint32_t& fontSize, const std::string& charactersToGenerate = "") : 
            fontSize(fontSize), charactersToGenerate(charactersToGenerate), freeTypeFace(std::move(freeTypeFace)) {};

        FontData(FontData&& other) : fontSize(other.fontSize), charactersToGenerate(charactersToGenerate), freeTypeFace(std::move(other.freeTypeFace)) {}

        GlyphData operator[](const char& c) const;

        ~FontData() = default;

        uint32_t fontSize = 32;
        std::string charactersToGenerate = "";

    private:
        std::unique_ptr<FreeTypeFace> freeTypeFace;
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