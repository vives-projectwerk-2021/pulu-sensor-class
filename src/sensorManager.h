#pragma once

#define fakeTemperature
#ifdef fakeTemperature
    #include "FakeTemperatureSensor.h"
#else
    #include "TCN75.h"
#endif

#define fakeLight
#ifdef fakeLight
    #include "fakeLightSensor.h"
#else
    #include "LTR329ALS.h"
#endif

//#define fakeMoisture
#ifdef fakeMoisture
    #include "fakeMoistSensor.h"
#else
    #include "MoistureSensors.h"
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

            bool init(); // true = success
            sensorValues values();

        private:
            void sleep_all();
            void wake_all();
            
        private:
            #ifdef fakeMoisture
                std::array<FakeMoistSensor, 4> moistureSensors;
            #else
                std::array<MoistureSensors*, 1> moistureSensors;
            #endif
            #ifdef fakeTemperature
                std::array<FakeTemperatureSensor, 2> temperatureSensors;
            #else
                std::array<TCN75*, 2> temperatureSensors;
            #endif
            #ifdef fakeLight
                std::array<FakeLightSensor, 1> lightSensors;
            #else
                std::array<LTR329ALS*, 1> lightSensors;
            #endif
            Battery batterySensor;
    };
};