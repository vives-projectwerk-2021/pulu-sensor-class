#include "sensorManager.h"

namespace Pulu {
    sensorManager::sensorManager() {
        lightSensors = {
            FakeLightSensor()
        };
        moistureSensors = {
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor(),
            FakeMoistSensor()
        };
        temperatureSensors = {
            FakeTemperatureSensor(),
            FakeTemperatureSensor()
        };
        batterySensor = Battery();
    };

    bool sensorManager::init() {
        // TODO: init all sensors when not fake
        return true;
    }

    sensorValues sensorManager::values() {
        sensorValues values;
        for(uint8_t i = 0; i<lightSensors.size(); i++) {
            values.light[i] = lightSensors[i].lightLevel();
        }
        for(uint8_t i = 0; i<moistureSensors.size(); i++) {
            values.moisture[i] = moistureSensors[i].moisture();
        }
        for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
            values.temperature[i] = temperatureSensors[i].temperature();
        }
        values.battery = batterySensor.voltage();
        return values;
    }
};