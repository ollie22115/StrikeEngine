#include "StrikePCH.h"
#include "Random.h"

namespace Strike {

    template<>
    uint16_t random<uint16_t>(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint16_t> dist(0, 0xFFFF);

        return dist(gen);
    }

    template<>
    uint32_t random<uint32_t>(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

        return dist(gen);
    }
}