#pragma once

#include <iostream>

#include <unordered_map>
#include <vector>
#include <string>

#include "IResourceManagerPointer.h"
#include "ResourceEntry.h"
#include "ResourcePointer.h"
#include "ResourceLoader.h"
#include "Rendering/Texture.h"
#include "Rendering/Shader.h"

#include "ResourceHandle.h"
#include "Utils/Random.h"

#define STRIKE_DEFAULT_POOL_SIZE 256


//TODO!!! Think about behaviour of ResourceManager when full
namespace Strike {

    template<typename T, uint32_t poolSize = STRIKE_DEFAULT_POOL_SIZE>
    class ResourceManager : public IResourceManagerPointer<T> {
    public:

        ResourceManager() : firstFreePos(1) {

            for(size_t i = 0; i < resourcePool.size() - 1; i++)
                resourcePool[i].setNextFreePos(i + 2);
            resourcePool[resourcePool.size() - 1].setNextFreePos(0);

        }

        class ResourceIterator {
        public:
            ResourceIterator(const std::array<ResourceEntry<T>, STRIKE_DEFAULT_POOL_SIZE>& resourcePool, ResourceManager* managerPtr) {
                for(size_t i = 0; i < resourcePool.size(); i++) if(resourcePool[i].inUse())
                    inUseResources.push_back(ResourcePointer<T>(constructHandle(i + 1, resourcePool[i].getMagicNumber()), managerPtr));
            }

            auto cbegin() const { return inUseResources->cbegin(); }
            auto begin() { return inUseResources.begin(); }
            auto cend() const { return inUseResources->cend(); }
            auto end() { return inUseResources.end(); }

        private:
            std::vector<ResourcePointer<T>> inUseResources;
        };
            
        inline uint32_t getFreeCount() const {
            uint32_t count = 0;
            for(ResourceEntry<T> entry : resourcePool)
                if(!entry.inUse()) count++;
        }

        template <typename... Args>
        ResourcePointer<T> load(const std::string& filePath, Args&&... args);

        template<typename... Args>
        inline ResourcePointer<T> emplace(const std::string& name, Args&&... args){
            ResourceHandle handle = getHandleFromFilePath(name);
            resourcePool[getPosition(handle) - 1].construct(name, getMagicNumber(handle), std::forward<Args>(args)...);

            resourcePool[getPosition(handle) - 1].refCount++;
            return ResourcePointer(handle, this);
        }

        inline ResourceIterator iterator() { return ResourceIterator(resourcePool, this); }

        inline void clear(){ 
            for(size_t i = 0; i < resourcePool.size(); i++){
                resourcePool[i].destruct();
            }
                
            for(size_t i = 0; i < resourcePool.size() - 1; i++)
                resourcePool[i].nextFreePos = i + 2;

            resourcePool[resourcePool.size() - 1].nextFreePos = 0;

            firstFreePos = 1;
        }


    protected:
        inline void incrementRefCount(const ResourceHandle& handle) override {
            uint32_t position = getPosition(handle);
            
            STRIKE_ASSERT(isValid(handle), LOG_PLATFORM_CORE, "Invalid Pointer, Magic Numbers don't align");

            resourcePool[position - 1].incrementRefCount();
        }

        inline void decrementRefCount(const ResourceHandle& handle) override {
            uint32_t position = getPosition(handle);

            STRIKE_ASSERT(isValid(handle), LOG_PLATFORM_CORE, "Invalid Pointer, Magic Numbers don't align");
            
            resourcePool[position - 1].decrementRefCount();
            if(resourcePool[position - 1].getRefCount() <= 0){
                resourcePool[position - 1].destruct();
                resourcePool[position - 1].setNextFreePos(firstFreePos);
                this->firstFreePos = position;
            }
        }

        inline T* get(const ResourceHandle& handle) override {
            uint32_t position = getPosition(handle);
            
            STRIKE_ASSERT(isValid(handle), LOG_PLATFORM_CORE, "Invalid Pointer Creation, Magic Numbers don't align");
            
            return &resourcePool[position - 1].getResource();
        }

        inline bool isValid(const ResourceHandle& handle) const override {
            uint32_t position = getPosition(handle);
            uint32_t magicNumber = getMagicNumber(handle);

            return resourcePool[position - 1].getMagicNumber() == magicNumber;
        }


    private:
        std::array<ResourceEntry<T>, poolSize> resourcePool;

        uint32_t firstFreePos = 1; //0 is reserved for invalid handle

        ResourceHandle getHandleFromFilePath(const std::string& filePath);
    };



    template <typename T, uint32_t poolSize>
    inline ResourceHandle ResourceManager<T, poolSize>::getHandleFromFilePath(const std::string &filePath) {

        ResourceHandle handle = genHandle(firstFreePos);
        STRIKE_ASSERT(firstFreePos > 0, LOG_PLATFORM_CORE, "Resource Pool Full");
        firstFreePos = resourcePool[firstFreePos - 1].nextFreePos;
        return handle;

    }


    template<typename T, uint32_t poolSize>
    template<typename... Args>
    inline ResourcePointer<T> ResourceManager<T, poolSize>::load(const std::string& filePath, Args&&... args){
        
        for(size_t i = 0; i < resourcePool.size(); i++){
            ResourceEntry<T>& entry = resourcePool[i];
            if(entry.inUse() && entry.getFilePath() == filePath)
                return ResourcePointer(constructHandle(i + 1, entry.getMagicNumber()), this);
            
        }

        ResourceHandle handle = getHandleFromFilePath(filePath);

        ResourceBuffer data = ResourceLoader::loadResourceData<T>(filePath, std::forward<Args>(args)...);
        constructEntry<T>(resourcePool[getPosition(handle) - 1], data, filePath, getMagicNumber(handle));

        return ResourcePointer(handle, this);

    }
}