#pragma once

#include "stdint.h"
#include <array>

namespace Pulu {
    struct sensorValues {
        std::array<uint16_t, 1> light;
        std::array<int16_t, 2> temperature;
        std::array<uint16_t, 4> moisture;
        float battery;
    };
};