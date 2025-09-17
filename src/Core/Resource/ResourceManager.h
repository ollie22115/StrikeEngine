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

#define STRIKE_DEFAULT_POOL_SIZE 256

namespace Strike{

    template<typename T>
    class ResourceManager {
    public:
        ResourceManager() : firstFreePos(1) {

            for(size_t i = 0; i < resourcePool.size() - 1; i++)
                resourcePool[i].nextFreePos = i + 2;

            resourcePool[resourcePool.size() - 1].nextFreePos = 0;

        }

        struct Entry {
            Entry() = default;

            inline T& getResource() { return resource.value(); }
            inline const T& getResource() const { return resource.value(); }

            inline const std::string& getFilePath() const { return filePath; }

            inline uint32_t getMagicNumber() const { return magicNumber; }

            inline bool inUse() const { return resource.has_value(); }

            inline void setNextFreePos(const uint32_t& nextFreePos) { this->nextFreePos = nextFreePos;}
            
            template <typename... Args>
            inline void construct(const std::string& filePath, const uint32_t& magicNumber, Args&&... args) {
                resource.emplace(std::forward<Args>(args)...);
                this->filePath = filePath;
                this->magicNumber = magicNumber;
                this->nextFreePos = 0;
            }
            
            inline void destruct(){
                resource.reset();
                filePath = "";
                magicNumber = 0;
            }

            ~Entry() = default;

        private:
            std::optional<T> resource;

            uint32_t refCount = 0;
            
            std::string filePath = "";
            uint32_t nextFreePos = 0;
            uint32_t magicNumber = 0;
            

            friend class ResourceManager;
        };



        class ResourcePointer{
        public:
            ResourcePointer() : handle(0), managerPtr(nullptr) {}

            ResourcePointer(const ResourceHandle& handle, ResourceManager<T>* managerPtr) :
                handle(handle), managerPtr(managerPtr) {
                managerPtr->resourcePool[getPosition(handle) - 1].refCount++;
            }

            ResourcePointer(const ResourcePointer& other){
                handle = other.handle;
                managerPtr = other.managerPtr;
                managerPtr->resourcePool[getPosition(handle) - 1].refCount++;
            }

            inline ResourceHandle getHandle() { return handle; }

            inline T& operator*() {
                return resourcePool[getPosition(handle) - 1].getResource();
            }

            inline T* operator->() {
                return managerPtr->getResourceFromHandle(handle);
            }

            inline void operator=(const ResourcePointer& other){
                if(*this == other) return;

                if(*this){
                    uint32_t position = getPosition(handle);
                    Entry& entry = managerPtr->resourcePool[position - 1];
                    
                    entry.refCount--;

                    if(entry.refCount == 0){
                        entry.destruct();
                        entry.nextFreePos = managerPtr->firstFreePos;
                        managerPtr->firstFreePos = position;
                    }
                }

                handle = other.handle;
                managerPtr = other.managerPtr;
                managerPtr->resourcePool[getPosition(handle) - 1].refCount++;
            }

            inline bool operator==(const ResourcePointer& other) const {
                return handle == other.handle && managerPtr == other.managerPtr;
            }

            operator bool() const {
                return handle != 0 || managerPtr != nullptr;
            }

            ~ResourcePointer() {
                uint32_t position = getPosition(handle);
                Entry& entry = managerPtr->resourcePool[position - 1];
                
                entry.refCount--;

                if(entry.refCount == 0){
                    entry.destruct();
                    entry.nextFreePos = managerPtr->firstFreePos;
                    managerPtr->firstFreePos = position;
                }

            }

        private:
            ResourceHandle handle;
            ResourceManager* managerPtr;
        };



        class ResourceIterator {
        public:
            ResourceIterator(const std::array<Entry, STRIKE_DEFAULT_POOL_SIZE>& resourcePool, ResourceManager* managerPtr) {
                for(size_t i = 0; i < resourcePool.size(); i++) if(resourcePool[i].inUse())
                    inUseResources.push_back(ResourcePointer(constructHandle(i + 1, resourcePool[i].getMagicNumber()), managerPtr));
            }

            auto cbegin() const { return inUseResources->cbegin(); }
            auto begin() { return inUseResources.begin(); }
            auto cend() const { return inUseResources->cend(); }
            auto end() { return inUseResources.end(); }

        private:
            std::vector<ResourcePointer> inUseResources;
        };
            


        ResourcePointer load(const std::string& filePath);
        ResourcePointer getResourcePtrFromHandle(const ResourceHandle& handle);
        T* getResourceFromHandle(const ResourceHandle& handle);

        template<typename... Args>
        inline ResourcePointer emplace(const std::string& name, Args&&... args){
            ResourceHandle handle = getHandleFromFilePath(name);
            resourcePool[getPosition(handle) - 1].construct(name, getMagicNumber(handle), std::forward<Args>(args)...);

            resourcePool[getPosition(handle) - 1].refCount++;
            return ResourcePointer(handle, this);
        }

        inline ResourceIterator iterator() { return ResourceIterator(resourcePool, this); }

        inline void clear(){ 
            for(size_t i = 0; i < resourcePool.size(); i++)
                resourcePool[i].destruct();
            
            for(size_t i = 0; i < resourcePool.size() - 1; i++)
                resourcePool[i].nextFreePos = i + 2;

            resourcePool[resourcePool.size() - 1].nextFreePos = 0;

            firstFreePos = 1;
        }

    private:
        std::array<Entry, STRIKE_DEFAULT_POOL_SIZE> resourcePool;

        uint32_t firstFreePos = 1; //0 is reserved for invalid handle

        ResourceHandle getHandleFromFilePath(const std::string& filePath);


        friend class ResourcePointer;
    };

    template<typename T>
    using ResourcePointer = ResourceManager<T>::ResourcePointer;



    template<typename T>
    inline T* ResourceManager<T>::getResourceFromHandle(const ResourceHandle& handle) {

        uint32_t position = getPosition(handle);
        uint32_t magicNumber = getMagicNumber(handle);
        STRIKE_ASSERT(handle != 0 || position != 0, LOG_PLATFORM_CORE, "Null Resource Handle Cannot be Used to retrieve Resource");
        Entry& entry = resourcePool[position - 1];
        STRIKE_ASSERT(entry.getMagicNumber() == magicNumber, LOG_PLATFORM_CORE, "Invalid Resource Handle, Magic Numbers don't align");
        STRIKE_ASSERT(entry.inUse(), LOG_PLATFORM_CORE, "Resource Handle Points to Unused Resource");

        return &entry.getResource();

    }

    template<typename T>
    inline ResourceManager<T>::ResourcePointer ResourceManager<T>::getResourcePtrFromHandle(const ResourceHandle& handle) {
        return ResourcePointer(handle, this);
    }

    template <typename T>
    inline ResourceHandle ResourceManager<T>::getHandleFromFilePath(const std::string &filePath) {

        ResourceHandle handle = genHandle(firstFreePos);
        STRIKE_ASSERT(firstFreePos > 0, LOG_PLATFORM_CORE, "Resource Pool Full");
        firstFreePos = resourcePool[firstFreePos - 1].nextFreePos;
        return handle;

    }

    template<>
    ResourcePointer<Texture2D> ResourceManager<Texture2D>::load(const std::string& filePath);

    template<>
    ResourcePointer<Shader> ResourceManager<Shader>::load(const std::string& filePath);

}