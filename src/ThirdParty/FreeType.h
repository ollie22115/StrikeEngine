#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Strike {

    class FreeTypeFace {
    public:

        struct LoadedFreeTypeGlyph {
            char character;
            uint32_t width, height, pitch, advance, bearingX, bearingY;
            unsigned char* buffer;

            LoadedFreeTypeGlyph() = default;

            std::unique_ptr<unsigned char[]> copyBuffer() const;
        };

    
        FreeTypeFace(const FT_Face& faceHandle) : faceHandle(faceHandle) {}
        
        FreeTypeFace(FreeTypeFace&& other);


        inline LoadedFreeTypeGlyph& getLoadedGlyph() { return loadedGlyph; }
        inline const LoadedFreeTypeGlyph& getLoadedGlyph() const { return loadedGlyph; }

        void loadGlyph(const char& c, const uint32_t& width, const uint32_t& height) const;


        ~FreeTypeFace();

    private:
        FT_Face faceHandle;
        mutable LoadedFreeTypeGlyph loadedGlyph;
    };

    class FreeTypeLibrary {
    public:
        FreeTypeLibrary();


        FreeTypeFace genFace(const std::string& filePath, const uint32_t& faceIndex = 0);


    private:
        FT_Library libraryHandle;
    };



    FreeTypeLibrary& getFreeTypeLibrary();

}