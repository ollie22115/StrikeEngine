#include "StrikePCH.h"
#include "FreeType.h"

namespace Strike {
    
    std::unique_ptr<unsigned char[]> FreeTypeFace::LoadedFreeTypeGlyph::copyBuffer() const {
        auto newBuffer = std::make_unique<unsigned char[]>(pitch * height);

        memcpy(newBuffer.get(), buffer, pitch * height);
        return newBuffer;
    }

    FreeTypeFace::FreeTypeFace(FreeTypeFace &&other) {
        this->faceHandle = other.faceHandle;
        this->loadedGlyph = other.loadedGlyph;

        other.faceHandle = nullptr;
        other.loadedGlyph = LoadedFreeTypeGlyph();
    }

    void FreeTypeFace::loadGlyph(const char &c, const uint32_t &width, const uint32_t &height) const
    {

        FT_Set_Pixel_Sizes(faceHandle, 0, height);

        STRIKE_ERROR(!FT_Load_Char(faceHandle, c, FT_LOAD_RENDER), LOG_PLATFORM_CORE, 
            "FreeType failed to load character!");

        this->loadedGlyph.character = c;
        this->loadedGlyph.height = faceHandle->glyph->bitmap.rows;
        this->loadedGlyph.width = faceHandle->glyph->bitmap.width;
        this->loadedGlyph.pitch = faceHandle->glyph->bitmap.pitch;
        this->loadedGlyph.buffer = faceHandle->glyph->bitmap.buffer;
        this->loadedGlyph.advance = faceHandle->glyph->advance.x;
        this->loadedGlyph.bearingX = faceHandle->glyph->metrics.horiBearingX;
        this->loadedGlyph.bearingY = faceHandle->glyph->metrics.horiBearingY;
    }

    FreeTypeFace::~FreeTypeFace() {
        if(faceHandle) 
            STRIKE_ERROR(!FT_Done_Face(faceHandle), LOG_PLATFORM_CORE, "FreeType failed to free face!");
    }




    FreeTypeLibrary::FreeTypeLibrary() {
        STRIKE_ERROR(!FT_Init_FreeType(&libraryHandle), LOG_PLATFORM_CORE, "FreeType failed to initialised!");
    }

    FreeTypeFace FreeTypeLibrary::genFace(const std::string &filePath, const uint32_t &faceIndex) {
        FT_Face faceHandle;
        FT_New_Face(libraryHandle, filePath.c_str(), faceIndex, &faceHandle);
        
        return FreeTypeFace(faceHandle); //TODO!!! Could cause an error
    }

    FreeTypeLibrary &getFreeTypeLibrary() {
        static FreeTypeLibrary freeTypeLibrary;
        return freeTypeLibrary;
    }
}