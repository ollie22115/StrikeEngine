#pragma once

#include <glad/glad.h>
#include "GLTexture.h"
#include "Resource/ResourceData.h"
#include "Resource/ResourceManager.h"

namespace Strike{

    class GLTextureAtlas{
    public:
        struct SubTexture {
            float u0, v0, u1, v1;

            SubTexture(const float& u0, const float& v0, const float& u1, const float& v1) :
                u0(u0), v0(v0), u1(u1), v1(v1) {}

            ~SubTexture() = default;
        };

        GLTextureAtlas(const TextureAtlasData& textureAtlasData);

        inline ResourcePointer<GLTexture2D>& getTexture() { return texture; }
        inline const ResourcePointer<GLTexture2D>& getTexture() const { return texture; }

        inline GLuint getId() { return texture->getId(); }
        inline GLuint getId() const { return texture->getId(); }

        inline uint32_t getWidth() { return texture->getWidth(); }
        inline uint32_t getWidth() const { return texture->getWidth(); }

        inline uint32_t getHeight() { return texture->getHeight(); }
        inline uint32_t getHeight() const { return texture->getHeight(); }

        const SubTexture& getSubTexture(const uint32_t& index) const {
            return subTextures[index];
        }

        const SubTexture& operator[](const uint32_t& index){
            return subTextures[index];
        }

        void bind(const uint32_t& slot = 0) const;

        ~GLTextureAtlas() = default;

    private:
        ResourcePointer<GLTexture2D> texture;

        std::vector<SubTexture> subTextures;
    };

}