#pragma once
#include "ResourceHandle.h"

namespace Strike {

    template<typename T>
    class ResourcePointer;

    template<typename T>
    class IResourceManagerPointer {
    protected:
        virtual void incrementRefCount(const ResourceHandle&) = 0;
        virtual void decrementRefCount(const ResourceHandle&) = 0;
        virtual T* get(const ResourceHandle&) = 0;
        virtual bool isValid(const ResourceHandle&) const = 0;

        virtual ~IResourceManagerPointer() = default;

        friend class ResourcePointer<T>;
    };

}