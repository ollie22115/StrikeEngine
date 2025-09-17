#include "StrikePCH.h"
#include "ResourceHandle.h"
#include "Utils/Random.h"

namespace Strike {

    ResourceHandle constructHandle(const uint32_t& position, const uint32_t& magicNumber) {
        return (static_cast<uint64_t>(magicNumber) << 32) | position;
    }

    uint32_t getPosition(const ResourceHandle &handle) {
        return static_cast<uint32_t>(handle & 0xFFFFFFFF);
    }

    uint32_t getMagicNumber(const ResourceHandle& handle) {
        return static_cast<uint32_t>(handle >> 32);
    }

    ResourceHandle genHandle(const uint32_t& position){
        uint32_t magicNumber = random<uint32_t>();
        return constructHandle(position, magicNumber);
    }
    
}