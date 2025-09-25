#include "ResourceManager.h"

namespace Strike{

    template<>
    void constructEntry(ResourceEntry<Texture2D>& entry, const ResourceData& data,
        const std::string& filePath, const uint32_t& magicNumber){

        entry.construct(filePath, magicNumber, std::get<TextureData2D>(data));
    
    }

    template<>
    void constructEntry(ResourceEntry<Shader>& entry, const ResourceData& data, 
        const std::string& filePath, const uint32_t& magicNumber){

        entry.construct(filePath, magicNumber, std::get<ShaderData>(data));
    }
}