#pragma once

#include "Texture.h"
#include "Resource/ResourceManager.h"

namespace Strike {

    class RendererResourceStore {
    public:
        template<typename T>
        static ResourceHandle load(const std::string& filePath);
        
        template<typename T>
        static const T* const get(const ResourceHandle& handle);

    private:
        static ResourceManager<Texture2D> textureManager;
        //static ResourceManager<TextureAtlas2D> textureAtlasManager;
        //static ResourceManager<Shader> shaderManager;
        //static ResourceManager<Material> materialManager;
    };

    template<>
    ResourceHandle RendererResourceStore::load<Texture2D>(const std::string& filePath);

    template<>
    const Texture2D* const RendererResourceStore::get<Texture2D>(const ResourceHandle& handle);

}