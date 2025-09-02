#pragma once

#include <iostream>

#include <unordered_map>
#include <vector>
#include <string>

#include "ResourceLoader.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

#include "ResourceHandle.h"
#include "Utils/Random.h"

namespace Strike{

    template<typename T>
    class ResourceManager {
    public:
        ResourceManager() = default;

        struct Entry {
            Entry() = default;

            Entry(const std::string& filePath/*, const uint32_t& magicNumber*/) : 
                filePath(filePath), resource()/*, magicNumber(magicNumber)*/ {}

            template<typename... Args>
            Entry(const std::string& filePath, const uint32_t& magicNumber, Args&&... args) :
                filePath(filePath), magicNumber(magicNumber), resource(std::forward<Args>(args)...) {}

            inline T& getResource() { return resource; }
            inline const T& getResource() const { return resource; }

            inline const std::string& getFilePath() const { return filePath; }

            inline uint32_t getMagicNumber() const { return magicNumber; }

            ~Entry() = default;

        private:
            T resource;
            uint32_t magicNumber;
            std::string filePath;
        };



        class ResourceIterator {
        public:
            ResourceIterator(const std::unordered_map<ResourceHandle, Entry>& resourceMapPtr) : 
                resourceMapPtr(&resourceMapPtr) {}

            auto begin() const { return resourceMapPtr->cbegin(); }
            auto end() const { return resourceMapPtr->cend(); }

        private:
            const std::unordered_map<ResourceHandle, Entry>* resourceMapPtr;
        };
        

        ResourceHandle load(const std::string& filePath);
        T* get(const ResourceHandle& handle);

        template<typename... Args>
        inline ResourceHandle emplace(const std::string& name, Args&&... args){
            ResourceHandle handle = getHandleFromFilePath(name);
            resourceMap.emplace(
                std::piecewise_construct,
                std::forward_as_tuple(getPosition(handle)),
                std::forward_as_tuple(name, getMagicNumber(handle), std::forward<Args>(args)...)
            );

            return handle;
        }

        inline ResourceIterator iterator() const { return ResourceIterator(resourceMap); }

        inline void clear(){ resourceMap.clear(); }

        static ResourceHandle genHandle(const uint32_t& position);

    private:
        ResourceHandle nextHandle = 1; //0 is reserved for invalid handle

        ResourceHandle getHandleFromFilePath(const std::string& filePath);
        std::unordered_map<ResourceHandle, /*T*/Entry> resourceMap;
    };

    template<typename T>
    inline T* ResourceManager<T>::get(const ResourceHandle& handle) {
        
        uint32_t position = getPosition(handle);
        uint32_t magicNumber = getMagicNumber(handle);

        auto entry = resourceMap.find(position);
        if(entry == resourceMap.end())
            return nullptr;

        STRIKE_ASSERT(magicNumber == entry->second.getMagicNumber(), LOG_PLATFORM_CORE, "Invalid Resource Handle");

        return &entry->second.getResource();

        /*
        auto it = resourceMap.find(handle);
        if (it == resourceMap.end())
            return nullptr;

        return &it->second.getResource();
        */
    }

    template <typename T>
    inline ResourceHandle ResourceManager<T>::getHandleFromFilePath(const std::string &filePath) {
        
        nextHandle++;
        return genHandle(nextHandle - 1);

    }

    template<>
    ResourceHandle ResourceManager<Texture2D>::load(const std::string& filePath);

    template<>
    ResourceHandle ResourceManager<Shader>::load(const std::string& filePath);

    template <typename T>
    inline ResourceHandle ResourceManager<T>::genHandle(const uint32_t &position) {
        uint32_t magicNumber = random<uint32_t>();
        return (static_cast<uint64_t>(magicNumber) << 32) | position;
    }

}