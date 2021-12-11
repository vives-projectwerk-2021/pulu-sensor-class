#pragma once

#include "stdint.h"
#include <array>

namespace Pulu {
    namespace Sensors {
        struct values {
            std::array<uint16_t, 1> light;
            std::array<int16_t, 2> temperature;
            std::array<int16_t, 4> moisture;
            float battery;
        };
    };
};