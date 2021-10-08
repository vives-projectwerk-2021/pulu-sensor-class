#pragma once

#include "fakeLightSensor.h"
#include "fakeMoistSensor.h"
#include "FakeTemperatureSensor.h"
#include <array>
#include "sensorValues.h"

namespace Pulu {
    class sensorManager {
        public:
            sensorManager();

            bool init(); // true = success
            sensorValues values();
            
        private:
            std::array<FakeLightSensor, 1> lightSensors;
            std::array<FakeMoistSensor, 4> moistureSensors;
            std::array<FakeTemperatureSensor, 2> temperatureSensors;
    };
};