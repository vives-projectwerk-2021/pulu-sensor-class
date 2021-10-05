#include "mbed.h"
#include "Sensor.h"

namespace Pulu
{

    Sensor::Sensor():
        lightSensor(),
        moistureSensorLevel1(),
        moistureSensorLevel2(),
        moistureSensorLevel3(),
        moistureSensorLevel4(),
        airTemperatureSensor(),
        groundTemperatureSensor()
    {
        // DEFINE ALL OBJECT OF CLASSES
    }

    bool Sensor::Read()
    {
        lightLevel();
        moisture();
        airTemperature();
        groundTemperature();
    }

    uint16_t Sensor::GetValues()
    {
        return values;
    }

    void Sensor::lightLevel()
    {
        values[0] = lightSensor.lightLevel();
    }

    void Sensor::moisture()
    {
        values[1] = moistureSensorLevel1.moisture();
        values[2] = moistureSensorLevel2.moisture();
        values[3] = moistureSensorLevel3.moisture();
        values[4] = moistureSensorLevel4.moisture();
    }

    void Sensor::airTemperature()
    {
        values[5] = airTemperatureSensor.temperature();
    }

    void Sensor::groundTemperature()
    {
        values[6] = groundTemperatureSensor.temperature();
    }

    void Sensor::batteryLevel()
    {
        values[7] = 100;
    }

}
