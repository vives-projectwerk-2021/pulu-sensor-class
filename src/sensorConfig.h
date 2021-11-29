#pragma once

#include "I2C.h"
#include "stdint.h"
#include <array>

namespace Pulu {
    namespace Sensors {
        struct sensorConfig {
            I2C* i2c;
            uint8_t address;
        };

        struct config {
            std::array<sensorConfig, 2> temperature;
            std::array<sensorConfig, 1> light;
            std::array<sensorConfig, 1> moisture;
        };
    };
};