#pragma once

#include "stdint.h"
#include "fakeLightSensor.h"
#include "fakeMoistSensor.h"
#include "FakeTemperatureSensor.h"

namespace Pulu
{
    class Sensor
    {
        #define totalSensors 9

        public:
            Sensor();
            bool Read();
            uint16_t * Values();

        private:
            void lightLevel();
            void moisture();
            void airTemperature();
            void groundTemperature();
            void batteryLevel();
            uint16_t values[totalSensors];
            FakeLightSensor * lightSensor;

            FakeMoistSensor * moistureSensorLevel1;
            FakeMoistSensor * moistureSensorLevel2;
            FakeMoistSensor * moistureSensorLevel3;
            FakeMoistSensor * moistureSensorLevel4;
            FakeMoistSensor * moistureSensorLevel5;

            FakeTemperatureSensor * airTemperatureSensor;
            FakeTemperatureSensor * groundTemperatureSensor;

    };  
};