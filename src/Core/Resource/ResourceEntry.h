#pragma once

namespace Strike {
    
    template<typename T>
    struct ResourceEntry {
        ResourceEntry() = default;

        inline T& getResource() { return resource.value(); }
        inline const T& getResource() const { return resource.value(); }

        inline const std::string& getFilePath() const { return filePath; }

        inline uint32_t getMagicNumber() const { return magicNumber; }

        inline bool inUse() const { return resource.has_value(); }

        inline void setNextFreePos(const uint32_t& nextFreePos) { this->nextFreePos = nextFreePos;}

        inline uint32_t getRefCount() const { return refCount; }

        inline void incrementRefCount() { refCount++; }
        inline void decrementRefCount() { refCount--; }
        
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
            refCount = 0;
        }

        ~ResourceEntry() = default;

    private:
        std::optional<T> resource;

        uint32_t refCount = 0;
        
        std::string filePath = "";
        uint32_t nextFreePos = 0;
        uint32_t magicNumber = 0;
        

        template<typename U, uint32_t poolSize>
        friend class ResourceManager;
    };
    
}