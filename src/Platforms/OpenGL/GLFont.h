#pragma once

#include <cstdint>
#include <unordered_map>
#include "Resource/ResourceData.h"
#include "GLTextureAtlas.h"

namespace Strike {

    class GLFont {
    public:
        struct Glyph {
            int32_t subTextureIndex;
            uint32_t bearingX, bearingY, advance;

            Glyph(const int32_t& subTextureIndex, const uint32_t& bearingX, const uint32_t& bearingY, const uint32_t& advance) :
                subTextureIndex(subTextureIndex), bearingX(bearingX), bearingY(bearingY), advance(advance) {}

            ~Glyph() = default;
        };

        GLFont(const FontData& fontData);

        inline const Glyph& getGlyph(const char& c) const {
            //return glyphs.at(c);
        }

        inline const Glyph& operator[](const char& c) {
            //return glyphs[c];
        }

        void bind(const uint32_t& slot = 0) const;

        ~GLFont() = default;

    private:
        std::unordered_map<char, Glyph> glyphs;
        GLTextureAtlas textureAtlas;
    };

}