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
        moistureSensorLevel5(),
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
        batteryLevel();
        return true;
    }

    uint16_t * Sensor::Values()
    {
        return values;
    }

    void Sensor::lightLevel()
    {
        values[0] = lightSensor->lightLevel();
    }

    void Sensor::moisture()
    {
        values[3] = moistureSensorLevel1->moisture();
        values[4] = moistureSensorLevel2->moisture();
        values[5] = moistureSensorLevel3->moisture();
        values[6] = moistureSensorLevel4->moisture();
        values[7] = moistureSensorLevel5->moisture();
    }

    void Sensor::airTemperature()
    {
        values[1] = airTemperatureSensor->temperature();
    }

    void Sensor::groundTemperature()
    {
        values[2] = groundTemperatureSensor->temperature();
    }

    void Sensor::batteryLevel()
    {
        values[8] = 100;
    }

}
