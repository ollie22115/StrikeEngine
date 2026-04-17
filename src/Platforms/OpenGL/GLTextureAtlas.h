#pragma once

#include <glad/glad.h>
#include <MaxRectsBinPack.h>
#include "GLTexture.h"
#include "Resource/ResourceData.h"
#include "Resource/ResourcePointer.h"

namespace Strike{

    class GLTextureAtlas{
    public:
        struct SubTexture { //TODO!!! Give SubTexture a ResourcePointer to texture (will help with paging)
            ResourcePointer<GLTexture2D> texture;
            glm::vec4 textureCoords;

            SubTexture(ResourcePointer<GLTexture2D> texture, const float& u0, const float& v0, const float& u1, const float& v1) :
                texture(texture), textureCoords(glm::vec4(u0, v0, u1, v1)) {}


            inline float& u0() { return textureCoords[0]; }
            inline const float& u0() const { return textureCoords[0]; }

            inline float& v0() { return textureCoords[1]; }
            inline const float& v0() const { return textureCoords[1]; }

            inline float& u1() { return textureCoords[2]; }
            inline const float& u1() const { return textureCoords[2]; }

            inline float& v1() { return textureCoords[3]; }
            inline const float& v1() const { return textureCoords[3]; }

            
            ~SubTexture() = default;
        };

        GLTextureAtlas(const TextureAtlasData& textureAtlasData);
        GLTextureAtlas(const uint32_t& width, const uint32_t& height, const uint32_t& bitsPerPixel);

        inline ResourcePointer<GLTexture2D>& getTexture() { return texture; }
        inline const ResourcePointer<GLTexture2D>& getTexture() const { return texture; }

        inline GLuint getId() { return texture->getId(); }
        inline GLuint getId() const { return texture->getId(); }

        inline uint32_t getWidth() { return texture->getWidth(); }
        inline uint32_t getWidth() const { return texture->getWidth(); }

        inline uint32_t getHeight() { return texture->getHeight(); }
        inline uint32_t getHeight() const { return texture->getHeight(); }


        bool addSubTexture(const TextureData2D& textureData, const uint32_t& border = 2);

        inline const SubTexture& getSubTexture(const uint32_t& index) const {
            return subTextures[index];
        }

        inline const SubTexture& operator[](const uint32_t& index){
            return subTextures[index];
        }

        inline size_t subTextureCount() const { return subTextures.size(); }

        void bind(const uint32_t& slot = 0) const;

        ~GLTextureAtlas() = default;

    private:
        ResourcePointer<GLTexture2D> texture;

        std::vector<SubTexture> subTextures;

        rbp::MaxRectsBinPack binPacker; 
    };

}