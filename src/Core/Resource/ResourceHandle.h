#pragma once

#include <string>

#define STRIKE_INVALID_RESOURCE_HANDLE 0

namespace Strike {

    using ResourceHandle = uint64_t;

    ResourceHandle constructHandle(const uint32_t& position, const uint32_t& magicNumber);

    uint32_t getPosition(const ResourceHandle& handle);

    uint32_t getMagicNumber(const ResourceHandle& handle);

}