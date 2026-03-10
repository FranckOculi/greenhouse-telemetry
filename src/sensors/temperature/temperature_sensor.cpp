#include "temperature_sensor.hpp"

TemperatureSensor::TemperatureSensor(ITemperatureDriver& d) : _driver(d) {
    _driver.init();
}

float TemperatureSensor::read() {
    uint32_t raw = _driver.read_raw();
    float temp = ((float)raw) / (1 << 20) * 200.0f - 50.0f;

    return temp;
}