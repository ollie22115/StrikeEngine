#include "StrikePCH.h"
#include "ResourceData.h"
#include <stb_image.h>
#include <cstring>
#include "ResourceLoader.h"

namespace Strike{
    
    TextureData2D::TextureData2D(const uint32_t& desiredBitsPerPixel, const uint32_t& width, const uint32_t& height) {

        this->width = width;
		this->height = height;
		this->bitsPerPixel = desiredBitsPerPixel;

        data = std::make_unique<unsigned char[]>(bitsPerPixel * width * height);
        for(uint32_t i = 0; i < width * height * bitsPerPixel; i++)
            data[i] = 255;
    }

    TextureData2D::TextureData2D(const TextureData2D& other) {

        this->width = other.width;
        this->height = other.height;
        this->bitsPerPixel = other.bitsPerPixel;

        this->data = std::make_unique<unsigned char[]>(other.bitsPerPixel * other.width * other.height);

        std::memcpy(this->data.get(), other.data.get(), other.bitsPerPixel * other.height * other.width);

    }

    TextureData2D::TextureData2D(TextureData2D &&other) {
        
        this->data = std::move(other.data);
        this->width = other.width;
        this->height = other.height;
        this->bitsPerPixel = other.bitsPerPixel;

        other.data = nullptr;

    }

    TextureData2D::TextureData2D(std::unique_ptr<unsigned char[]>& data, const uint32_t &width, const uint32_t &height, const uint32_t &bitsPerPixel) {
        this->data = std::move(data);
        this->width = width;
        this->height = height;
        this->bitsPerPixel = bitsPerPixel;
    }

    TextureAtlasData::TextureAtlasData(const uint32_t& width, const uint32_t& height, const uint32_t& bitsPerPixel) :
            width(width), height(height), bitsPerPixel(bitsPerPixel) {

        binPacker.Init(width, height, false);
    }

    bool TextureAtlasData::addSubTexture(TextureData2D& textureData, const uint32_t& border) {

        //pack texture into atlas
        rbp::Rect packedRect = binPacker.Insert(textureData.width + border * 2, textureData.height + border * 2, 
            rbp::MaxRectsBinPack::RectBestAreaFit);

        if(packedRect.width == 0 || packedRect.height == 0){
            STRIKE_ERROR(false, LOG_PLATFORM_CORE, "Could not pack texture into atlas: ");
            return false;
        }
        
        //add border to texture
        TextureData2D borderedTextureData(bitsPerPixel, 
            textureData.width + (2 * border), textureData.height + (2 * border));
         
        //ZZZ Double check clamping logic
        auto clamp = [](const int32_t& val, const int32_t& min, const int32_t& max) {
            return val < min ? min : (val > max ? max : val); 
        };

        for(int32_t y = 0; y < borderedTextureData.height; y++) 
            for(int32_t x = 0; x < borderedTextureData.width; x++) {

            int32_t srcX = clamp(x - border, 0, textureData.width - 1);
            int32_t srcY = clamp(y - border, 0, textureData.height - 1);
            
            int32_t srcIndex = (srcY * textureData.width + srcX) * bitsPerPixel;
            int32_t dstIndex = (y * borderedTextureData.width + x) * bitsPerPixel;

            for(int32_t b = 0; b < bitsPerPixel; b++)
                borderedTextureData.data[dstIndex + b] = textureData.data[srcIndex + b];
        }

        subTextures.emplace_back(borderedTextureData, (uint32_t) packedRect.x, (uint32_t) packedRect.y,
            (uint32_t) packedRect.width, (uint32_t) packedRect.height);

        return true;
    }
}