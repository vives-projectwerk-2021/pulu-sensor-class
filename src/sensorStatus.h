#pragma once

#include "stdint.h"
#include <array>

namespace Pulu {
    namespace Sensors {
        enum sensorStatus {
            SUCCESS = 0,
            WAKE_UP_FAILURE = 1,
            MEASUREMENT_FAILURE = 2,
            SLEEP_FAILURE = 3,
            BATTERY_SAVE_READ_ERROR = 1,
            BATTERY_SLOPE_ERROR = 2,
            BATTERY_LOW_ALERT = 3
        };

        struct status {
            std::array<sensorStatus, 1> light = {{sensorStatus::SUCCESS}};
            std::array<sensorStatus, 2> temperature = {{sensorStatus::SUCCESS, sensorStatus::SUCCESS}};
            std::array<sensorStatus, 1> moisture = {{sensorStatus::SUCCESS}};
            sensorStatus battery = sensorStatus::SUCCESS;
        };
    };
};