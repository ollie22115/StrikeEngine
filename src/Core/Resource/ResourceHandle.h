#pragma once

#include <string>

namespace Strike {

    using ResourceHandle = uint64_t;

    ResourceHandle constructHandle(const uint32_t& position, const uint32_t& magicNumber);

    uint32_t getPosition(const ResourceHandle& handle);

    uint32_t getMagicNumber(const ResourceHandle& handle);
}