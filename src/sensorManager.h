#pragma once

#if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
    #include "fakeLightSensor.h"
#else
    #include "LTR329ALS.h"
#endif

#if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
    #include "FakeTemperatureSensor.h"
#else
    #include "TCN75.h"
#endif

#if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
    #include "fakeMoistSensor.h"
#else
    #include "FDC1004.h"
#endif

#include "battery.h"

#include "sensorValues.h"
#include "sensorConfig.h"
#include <array>

#define sensorManager_DEBUG(x, ...)   //set as comment to enable debugging
#ifndef sensorManager_DEBUG
#define sensorManager_DEBUG(x, ...) printf("[sensorManager]\t" x "\r\n", ##__VA_ARGS__)
#endif

namespace Pulu {
    class sensorManager {
        public:
            sensorManager(Sensors::config config);

            sensorValues values();

        private:
            void sleep_all();
            void wake_all();
            
        private: // light
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
                std::array<FakeLightSensor, 1> lightSensors;
            #else
                std::array<LTR329ALS*, 1> lightSensors;
            #endif
        private: // temperature
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
                std::array<FakeTemperatureSensor, 2> temperatureSensors;
            #else
                std::array<TCN75*, 2> temperatureSensors;
            #endif
        private: // moisture
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
                std::array<FakeMoistSensor, 1> moistureSensors;
            #else
                std::array<FDC1004*, 1> moistureSensors;
            #endif
        private: // battery
            Battery batterySensor;
    };
};