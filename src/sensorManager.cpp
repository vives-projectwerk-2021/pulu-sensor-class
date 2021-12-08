#include "sensorManager.h"

namespace Pulu {
    sensorManager::sensorManager(Sensors::config config) {
        #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            lightSensors = {
                FakeLightSensor()
            };
        #else
            lightSensors = {
                new LTR329ALS(config.light[0].i2c, config.light[0].address)
            };
        #endif
        #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
            moistureSensors = {
                FakeMoistSensor(),
                FakeMoistSensor(),
                FakeMoistSensor(),
                FakeMoistSensor()
            };
        #else
            moistureSensors = {
                new FDC1004(config.moisture[0].i2c, config.moisture[0].address)
            };
        #endif
        #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            temperatureSensors = {
                FakeTemperatureSensor(),
                FakeTemperatureSensor()
            };
        #else
            for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
                temperatureSensors[i] = new TCN75(
                        config.temperature[i].i2c,
                        config.temperature[i].address
                    );
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
        wake_all();
        sensorValues values;
        sensorManager_DEBUG("start reading values");
        for(uint8_t i = 0; i<lightSensors.size(); i++) {
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
                values.light[i] = lightSensors[i].lightLevel();
            #else
                values.light[i] = lightSensors[i]->readLux();
            #endif
            sensorManager_DEBUG("light[%d]: %d", i, values.light[i]);
        }
        for(uint8_t i = 0; i<moistureSensors.size(); i++) {
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
                values.moisture[i] = moistureSensors[i].moisture();
                sensorManager_DEBUG("moisture[%d]: %d", i, values.moisture[i]);
            #else
                int16_t results[4];
                moistureSensors[i]->readFdcChannels(results);
                values.moisture[0] = results[0];
                sensorManager_DEBUG("moisture[%d]: %d", 0, values.moisture[0]);
                values.moisture[1] = results[1];
                sensorManager_DEBUG("moisture[%d]: %d", 1, values.moisture[1]);
                values.moisture[2] = results[2];
                sensorManager_DEBUG("moisture[%d]: %d", 2, values.moisture[2]);
                values.moisture[3] = results[3];
                sensorManager_DEBUG("moisture[%d]: %d", 3, values.moisture[3]);
            #endif
        }
        for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
                values.temperature[i] = temperatureSensors[i].temperature();
            #else
                values.temperature[i] = temperatureSensors[i]->temperature();
            #endif
            sensorManager_DEBUG("temperature[%d]: %d", i, values.temperature[i]);
        }
        #if MBED_CONF_APP_NUCLEO
            values.battery = batterySensor.voltage();
        #else
            values.battery = ((AnalogIn(PA_4).read_u16()*3.3)/pow(2,16))*((330000.0+220000.0)/330000.0);
        #endif

        sensorManager_DEBUG("battery: %f", values.battery);
        sleep_all();
        return values;
    }

    void sensorManager::sleep_all() {
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            for(uint8_t i = 0; i<lightSensors.size(); i++) {
                lightSensors[i]->sleep();
            }
        #endif
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
                temperatureSensors[i]->sleep();
            }
        #endif
    }
    void sensorManager::wake_all() {
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            for(uint8_t i = 0; i<lightSensors.size(); i++) {
                lightSensors[i]->wake();
            }
        #endif
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
                temperatureSensors[i]->wake();
            }
        #endif
        // give time to sensors to start measuring after wake up
        ThisThread::sleep_for(200ms);
    }
};