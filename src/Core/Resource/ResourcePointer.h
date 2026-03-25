#pragma once

#include <cstdint>
#include "IResourceManagerPointer.h"

namespace Strike{

    template <typename T>
    class ResourcePointer {
    public:
        ResourcePointer() : handle(0), managerPtr(nullptr) {}

        ResourcePointer(const ResourceHandle& handle, IResourceManagerPointer<T>* managerPtr) :
            handle(handle), managerPtr(managerPtr) {
            
            STRIKE_ASSERT(this->managerPtr->isValid(this->handle), LOG_PLATFORM_CORE, "Invalid Pointer Creation, Magic Numbers don't align");

            this->managerPtr->incrementRefCount(handle);
        }

        ResourcePointer(const ResourcePointer& other){
            this->handle = other.handle;
            this->managerPtr = other.managerPtr;
            this->managerPtr->incrementRefCount(handle);
        }

        inline ResourceHandle getHandle() { return handle; }

        inline T& operator*() {
            return *(this->managerPtr->get(handle));
        }

        inline const T& operator*() const {
            return *(this->managerPtr->get(handle));
        }

        inline T* operator->() {
            return this->managerPtr->get(handle);
        }

        inline const T* operator->() const {
            return this->managerPtr->get(handle);
        }

        inline void operator=(const ResourcePointer& other){
            if(*this == other) return;

            if(*this) this->managerPtr->decrementRefCount(handle);

            handle = other.handle;
            this->managerPtr = other.managerPtr;
            this->managerPtr->incrementRefCount(handle);
        }

        inline bool operator==(const ResourcePointer& other) const {
            return this->handle == other.handle && this->managerPtr == other.managerPtr;
        }

        operator bool() const {
            return this->handle != 0 || this->managerPtr != nullptr;
        }

        ~ResourcePointer() {
            if(!this->managerPtr) return;

            if(this->managerPtr->isValid(this->handle))
                this->managerPtr->decrementRefCount(this->handle);
        }

    private:
        ResourceHandle handle;
        IResourceManagerPointer<T>* managerPtr;
    };

}

