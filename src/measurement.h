#pragma once

#include "sensorValues.h"
#include "sensorStatus.h"

namespace Pulu {
    struct measurement {
        Sensors::values values;
        Sensors::status status;
    };
};