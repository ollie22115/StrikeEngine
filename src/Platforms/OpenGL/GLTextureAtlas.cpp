#include "GLTextureAtlas.h"

#include "Rendering/Renderer.h"

namespace Strike {

    GLTextureAtlas::GLTextureAtlas(const TextureAtlasData &textureAtlasData) {
        binPacker.Init(textureAtlasData.width, textureAtlasData.height, false);
        texture = Renderer::emplaceResource<GLTexture2D>("", textureAtlasData.bitsPerPixel, textureAtlasData.width, textureAtlasData.height);

        texture->bind();
        for(const auto& textureData : textureAtlasData.subTextures) {

            rbp::Rect packedRect = binPacker.Insert(textureData.width, textureData.height, 
                rbp::MaxRectsBinPack::RectBestAreaFit);

            if(packedRect.width == 0 || packedRect.height == 0){
                STRIKE_ERROR(false, LOG_PLATFORM_CORE, "Could not pack texture into atlas: ");
                return;
            }
                    
            glTexSubImage2D(GL_TEXTURE_2D, 0, packedRect.x, packedRect.y, packedRect.width, packedRect.height, 
                GL_RGBA, GL_UNSIGNED_BYTE, textureData.data.get());

            float u0 = (float) packedRect.x / (float) getWidth();
            float v0 = (float) packedRect.y / (float) getHeight();
            float u1 = ((float) packedRect.x + (float) packedRect.width) / (float) getWidth();
            float v1 = ((float) packedRect.y + (float) packedRect.height) / (float) getHeight();

            subTextures.emplace_back(u0, v0, u1, v1);
            
        }
    }

    bool GLTextureAtlas::addSubTexture(const TextureData2D& textureData, const uint32_t& border){
        rbp::Rect packedRect = binPacker.Insert(textureData.width + border * 2, textureData.height + border * 2, 
            rbp::MaxRectsBinPack::RectBestAreaFit);
        if(packedRect.width == 0 || packedRect.height == 0){
            STRIKE_ERROR(false, LOG_PLATFORM_CORE, "Could not pack texture into atlas: ");
            return false;
        }

        TextureData2D borderedTextureData = TextureData2D::createBorderedTexture(textureData, border);
        
        glTexSubImage2D(GL_TEXTURE_2D, 0, packedRect.x, packedRect.y, packedRect.width, packedRect.height, 
                GL_RGBA, GL_UNSIGNED_BYTE, borderedTextureData.data.get());

        float u0 = (float) packedRect.x / (float) getWidth();
        float v0 = (float) packedRect.y / (float) getHeight();
        float u1 = ((float) packedRect.x + (float) packedRect.width) / (float) getWidth();
        float v1 = ((float) packedRect.y + (float) packedRect.height) / (float) getHeight();

        subTextures.emplace_back(u0, v0, u1, v1);

        return true;
    }

    void GLTextureAtlas::bind(const uint32_t &slot) const {
        texture->bind(slot);
    }

}