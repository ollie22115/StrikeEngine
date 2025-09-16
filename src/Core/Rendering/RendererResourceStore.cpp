#include "RendererResourceStore.h"

namespace Strike{
    
    template<>
    ResourceHandle RendererResourceStore::load<Texture2D>(const std::string& filePath) {
        return textureManager.load(filePath);
    }

    template<>
    const Texture2D* const RendererResourceStore::get<Texture2D>(const ResourceHandle& handle) {
        return textureManager.getResourceFromHandle(handle);
    }

}