#pragma once

#include "stdint.h"
#include "mbed-fake-light-sensor/src/fakeLightSensor.h"
#include "mbed-fake-moisture-sensor/src/fakeMoistSensor.h"
#include "mbed-fake-temperature-sensor/src/FakeTemperatureSensor.h"

namespace Pulu
{
    class Sensor
    {
        #define totalSensors 8

        public:
            Sensor();
            bool Read();
            uint16_t * GetValues();

        private:
            void lightLevel();
            void moisture();
            void airTemperature();
            void voidTemperature();
            void batteryLevel();
            uint16_t values[totalSensors];
            FakeLightSensor * lightSensor;

            FakeMoistSensor * moistureSensorLevel1;
            FakeMoistSensor * moistureSensorLevel2;
            FakeMoistSensor * moistureSensorLevel3;
            FakeMoistSensor * moistureSensorLevel4;

            FakeTemperatureSensor * airTemperature;
            FakeTemperatureSensor * groundTemperature;

    };  
};