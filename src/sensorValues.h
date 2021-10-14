#pragma once

#include "stdint.h"
#include <array>

namespace Pulu {
    struct sensorValues {
        std::array<uint16_t, 1> light;
        std::array<uint16_t, 8> moisture;
        std::array<uint16_t, 2> temperature;
        float battery;
    };
};