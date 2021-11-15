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
            FakeMoistSensor()
        };
        #ifdef fakeTemperature
            temperatureSensors = {
                FakeTemperatureSensor(),
                FakeTemperatureSensor()
            };
        #else
            temperatureSensors = {
                TCN75(&i2c, 0x48<<1),
                TCN75(&i2c, 0x49<<1)
            };
        #endif
        batterySensor = Battery();
    };

    bool sensorManager::init() {
        // TODO: init all sensors when not fake
        sensorManager_DEBUG("init: SUCCESS");
        return true;
    }

    sensorValues sensorManager::values() {
        sensorValues values;
        sensorManager_DEBUG("start reading values");
        for(uint8_t i = 0; i<lightSensors.size(); i++) {
            values.light[i] = lightSensors[i].lightLevel();
            sensorManager_DEBUG("light[%d]: %d", i, values.light[i]);
        }
        for(uint8_t i = 0; i<moistureSensors.size(); i++) {
            values.moisture[i] = moistureSensors[i].moisture();
            sensorManager_DEBUG("moisture[%d]: %d", i, values.moisture[i]);
        }
        for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
            #ifdef fakeTemperature
                values.temperature[i] = temperatureSensors[i].temperature();
            #else
                temperatureSensors[i].wake();
                wait_us(500);
                values.temperature[i] = temperatureSensors[i].temperature();
                wait_us(500);
                temperatureSensors[i].sleep();
            #endif
            sensorManager_DEBUG("temperature[%d]: %d", i, values.temperature[i]);
        }
        values.battery = batterySensor.voltage();
        sensorManager_DEBUG("battery: %f", values.battery);
        return values;
    }
};