#include "GLTextureAtlas.h"

#include "Rendering/Renderer.h"

Strike::GLTextureAtlas::GLTextureAtlas(const TextureAtlasData &textureAtlasData) {
    //TODO!!!
    texture = Renderer::emplaceResource<GLTexture2D>("", textureAtlasData.bitsPerPixel, textureAtlasData.width, textureAtlasData.height);

    texture->bind();
    for(const auto& subTexData : textureAtlasData.subTextures) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, subTexData.x, subTexData.y, subTexData.width, subTexData.height,
            GL_RGBA, GL_UNSIGNED_BYTE, subTexData.textureData.data.get());

        float u0 = (float) subTexData.x / (float) getWidth();
        float v0 = (float) subTexData.y / (float) getHeight();
        float u1 = ((float) subTexData.x + (float) subTexData.width) / (float) getWidth();
        float v1 = ((float) subTexData.y + (float) subTexData.height) / (float) getHeight();

        subTextures.emplace_back(u0, v0, u1, v1);
    }
}

void Strike::GLTextureAtlas::bind(const uint32_t &slot) const {
    texture->bind(slot);
}