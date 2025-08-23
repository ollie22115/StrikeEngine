#include "StrikePCH.h"
#include "Texture.h"
#include "Utils/FileLoader.h"

namespace Strike{
    
    bool TextureCore::operator==(const TextureCore &other) const {
        return filePath == other.getFilePath();
    }
    
}
