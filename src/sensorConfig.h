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
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
                std::array<sensorConfig, 2> temperature;
            #endif
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
                std::array<sensorConfig, 1> light;
            #endif
            #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
                std::array<sensorConfig, 1> moisture;
            #endif
        };
    };
};