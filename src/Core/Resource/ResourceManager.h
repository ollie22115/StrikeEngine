#pragma once

#include <iostream>

#include <unordered_map>
#include <vector>
#include <string>

#include "ResourceLoader.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

#include "ResourceHandle.h"

namespace Strike{

    template<typename T>
    class ResourceManager{
    /* TODO!!! Implement the following when switching from string handles to uint32_t handles
        struct Entry {
            Entry() = default;
            Entry(const std::string& filePath, const ResourceHandle& handle) :
                filePath(filePath), handle(handle) {}

            std::string filePath;
            ResourceHandle handle;

            ~Entry() = default;
        };
    */

    public:
        ResourceHandle load(const std::string& filePath);
        T* get(const ResourceHandle& handle);
        inline void clear(){ resourceMap.clear(); }

    private:
        ResourceHandle getHandleFromFilePath(const std::string& filePath);
        std::unordered_map<ResourceHandle, T> resourceMap;
    };

    template<typename T>
    inline T* ResourceManager<T>::get(const ResourceHandle& handle) {
        auto it = resourceMap.find(handle);
        if (it == resourceMap.end())
            return nullptr;
        
        return &it->second;
    }

    template <typename T>
    inline ResourceHandle ResourceManager<T>::getHandleFromFilePath(const std::string &filePath) {
        return filePath;
    }

    template<>
    ResourceHandle ResourceManager<Texture2D>::load(const std::string& filePath);

    template<>
    ResourceHandle ResourceManager<Shader>::load(const std::string& filePath);

}