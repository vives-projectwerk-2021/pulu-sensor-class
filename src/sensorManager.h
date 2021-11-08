#pragma once

#include "fakeLightSensor.h"
#include "fakeMoistSensor.h"
#include "FakeTemperatureSensor.h"
#include "battery.h"
#include "sensorValues.h"
#include <array>

#define sensorManager_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef sensorManager_DEBUG
#define sensorManager_DEBUG(x, ...) printf("[sensorManager]\t" x "\r\n", ##__VA_ARGS__)
#endif

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
            Battery batterySensor;
    };
};