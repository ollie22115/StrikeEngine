#pragma once

#include <cstdint>
#include <random>

namespace Strike {
    template<typename T>
    inline T random();

    template<>
    uint16_t random<uint16_t>();

    template<>
    uint32_t random<uint32_t>();
}