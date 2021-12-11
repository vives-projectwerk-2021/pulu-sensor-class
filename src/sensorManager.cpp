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
        #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            temperatureSensors = {
                FakeTemperatureSensor(),
                FakeTemperatureSensor()
            };
        #else
            temperatureSensors = {
                new TCN75(config.temperature[0].i2c, config.temperature[0].address),
                new TCN75(config.temperature[1].i2c, config.temperature[1].address)
            };
        #endif
        #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
            moistureSensors = {
                FakeMoistSensor()
            };
        #else
            moistureSensors = {
                new FDC1004(config.moisture[0].i2c, config.moisture[0].address)
            };
        #endif
        batterySensor = Battery();
    };

    measurement sensorManager::do_measurement() {
        measurement m;
        wake_all(m.status);
        sensorValues values;
        sensorManager_DEBUG("starting measurement");
        for(uint8_t i = 0; i<lightSensors.size(); i++) {
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
                m.values.light[i] = lightSensors[i].lightLevel();
            #else
                bool err;
                m.values.light[i] = lightSensors[i]->readLux(&err);
                if(err && !m.status.light[i])
                    m.status.light[i] = Sensors::sensorStatus::MEASUREMENT_FAILURE;
            #endif
            sensorManager_DEBUG("light[%d]: %d", i, m.values.light[i]);
            sensorManager_DEBUG("light[%d] status: %d", i, m.status.light[i]);
        }
        for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
                m.values.temperature[i] = temperatureSensors[i].temperature();
            #else
                bool err;
                m.values.temperature[i] = temperatureSensors[i]->temperature(&err);
                if(err && !m.status.temperature[i])
                    m.status.temperature[i] = Sensors::sensorStatus::MEASUREMENT_FAILURE;
            #endif
            sensorManager_DEBUG("temperature[%d]: %d", i, m.values.temperature[i]);
            sensorManager_DEBUG("temperature[%d] status: %d", i, m.status.temperature[i]);
        }
        for(uint8_t i = 0; i<moistureSensors.size(); i++) {
            int16_t results[4] = {0};
            #if MBED_CONF_PULU_SENSOR_MANAGER_FAKE_MOISTURE
                results[0] = moistureSensors[i].moisture();
                results[1] = moistureSensors[i].moisture();
                results[2] = moistureSensors[i].moisture();
                results[3] = moistureSensors[i].moisture();
            #else
                bool err = moistureSensors[i]->readFdcChannels(results);
                if(err && !m.status.moisture[i])
                    m.status.moisture[i] = Sensors::sensorStatus::MEASUREMENT_FAILURE;
            #endif
            m.values.moisture[4*i] = results[0];
            m.values.moisture[4*i+1] = results[1];
            m.values.moisture[4*i+2] = results[2];
            m.values.moisture[4*i+3] = results[3];
            sensorManager_DEBUG("moisture[%d]: %d", 4*i, m.values.moisture[4*i]);
            sensorManager_DEBUG("moisture[%d]: %d", 4*i+1, m.values.moisture[4*i+1]);
            sensorManager_DEBUG("moisture[%d]: %d", 4*i+2, m.values.moisture[4*i+2]);
            sensorManager_DEBUG("moisture[%d]: %d", 4*i+3, m.values.moisture[4*i+3]);
            sensorManager_DEBUG("moisture[%d-%d] status: %d", 4*i, 4*i+3, m.status.moisture[i]);
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

    void sensorManager::sleep_all(Sensors::status &status) {
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            for(uint8_t i = 0; i<lightSensors.size(); i++) {
                if(lightSensors[i]->sleep() && !status.light[i])
                    status.light[i] = Sensors::sensorStatus::SLEEP_FAILURE;
            }
        #endif
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
                if(temperatureSensors[i]->sleep() && !status.temperature[i])
                    status.temperature[i] = Sensors::sensorStatus::SLEEP_FAILURE;
            }
        #endif
    }
    void sensorManager::wake_all(Sensors::status &status) {
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_LIGHT
            for(uint8_t i = 0; i<lightSensors.size(); i++) {
                if(lightSensors[i]->wake() && !status.light[i])
                    status.light[i] = Sensors::sensorStatus::WAKE_UP_FAILURE;
            }
        #endif
        #if !MBED_CONF_PULU_SENSOR_MANAGER_FAKE_TEMPERATURE
            for(uint8_t i = 0; i<temperatureSensors.size(); i++) {
                if(temperatureSensors[i]->wake() && !status.temperature[i])
                    status.temperature[i] = Sensors::sensorStatus::WAKE_UP_FAILURE;
            }
        #endif
        // give time to sensors to start measuring after wake up
        ThisThread::sleep_for(200ms);
    }
};