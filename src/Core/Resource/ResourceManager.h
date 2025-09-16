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
            ResourcePointer(const ResourceHandle& handle, ResourceManager<T>* managerPtr) :
                handle(handle), managerPtr(managerPtr) {
                managerPtr->resourcePool[getPosition(handle) - 1].refCount++;
            }

            ResourcePointer(const ResourcePointer& other){
                handle = other.handle;
                managerPtr = other.managerPtr;
                managerPtr->resourcePool[getPosition(handle) - 1].refCount++;
            }

            T* operator->() {
                return managerPtr->getResourceFromHandle(handle);
            }

            ~ResourcePointer() {
                //TODO!!!
                uint32_t position = getPosition(handle);
                Entry& entry = managerPtr->resourcePool[position - 1];
                
                entry.refCount--;

                if(entry.refCount == 0){
                    entry.destruct();
                    entry.nextFreePos = firstFreePos;
                    managerPtr->firstFreePos = position;
                }

            }

        private:
            ResourceHandle handle;
            ResourceManager* managerPtr;
        };



        class ResourceIterator {
            //TODO!!! Update to accomodate changes
        public:
            ResourceIterator(const std::array<Entry, STRIKE_DEFAULT_POOL_SIZE>& resourcePool) :
            resourcePoolPtr(&resourcePool) {}

            auto begin() const { return resourcePoolPtr->cbegin(); }
            auto end() const { return resourcePoolPtr->cend(); }

        private:
            const std::array<Entry, STRIKE_DEFAULT_POOL_SIZE>* resourcePoolPtr;
        };
            


        ResourceHandle/*ResourcePointer*/ load(const std::string& filePath);
        T* getResourceFromHandle(const ResourceHandle& handle);

        template<typename... Args>
        inline ResourceHandle/*ResourcePointer*/ emplace(const std::string& name, Args&&... args){
            ResourceHandle handle = getHandleFromFilePath(name);
            resourcePool[getPosition(handle) - 1].construct(name, getMagicNumber(handle), std::forward<Args>(args)...);

            return handle;
            //resourcePool[getPosition(handle) - 1].refCount++;
            //return ResourcePointer(handle, this);
        }

        inline ResourceIterator iterator() const { return ResourceIterator(resourcePool); }

        inline void clear(){ 
            for(size_t i = 0; i < resourcePool.size(); i++)
                resourcePool[i].destruct();
            
            for(size_t i = 0; i < resourcePool.size() - 1; i++)
                resourcePool[i].nextFreePos = i + 2;

            resourcePool[resourcePool.size() - 1].nextFreePos = 0;

            firstFreePos = 1;
        }

        static ResourceHandle genHandle(const uint32_t& position);

    private:
        std::array<Entry, STRIKE_DEFAULT_POOL_SIZE> resourcePool;

        uint32_t firstFreePos = 1; //0 is reserved for invalid handle
        //uint32_t firstTakenPos = 0; TODO!!! Implement when Implementing the taken list

        ResourceHandle getHandleFromFilePath(const std::string& filePath);


        //friend class ResourcePointer;
    };

    /*template<typename T>
    using ResourcePointer = ResourceManager<T>::ResourcePointer;*/

    template<typename T>
    inline T* ResourceManager<T>::getResourceFromHandle(const ResourceHandle& handle) {

        uint32_t position = getPosition(handle);
        uint32_t magicNumber = getMagicNumber(handle);
        STRIKE_ASSERT(handle != 0 || position != 0, LOG_PLATFORM_CORE, "Null Resource Handle Cannot be Used to retrieve Resource");
        Entry& entry = resourcePool[position - 1];
        STRIKE_ASSERT(entry.getMagicNumber() == magicNumber, LOG_PLATFORM_CORE, "Invalid Resource Handle, Magic Numbers don't align");

        return &entry.getResource();

    }

    template <typename T>
    inline ResourceHandle ResourceManager<T>::getHandleFromFilePath(const std::string &filePath) {

        ResourceHandle handle = genHandle(firstFreePos);
        STRIKE_ASSERT(firstFreePos > 0, LOG_PLATFORM_CORE, "Resource Pool Full");
        firstFreePos = resourcePool[firstFreePos - 1].nextFreePos;
        return handle;

    }

    template <typename T>
    inline ResourceHandle ResourceManager<T>::genHandle(const uint32_t& position) {
        uint32_t magicNumber = random<uint32_t>();
        return constructHandle(position, magicNumber);
    }

    template<>
    ResourceHandle/*ResourcePointer*/ ResourceManager<Texture2D>::load(const std::string& filePath);

    template<>
    ResourceHandle/*ResourcePointer*/ ResourceManager<Shader>::load(const std::string& filePath);

}