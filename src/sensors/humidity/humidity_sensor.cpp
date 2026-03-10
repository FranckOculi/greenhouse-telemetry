#include "humidity_sensor.hpp"

HumiditySensor::HumiditySensor(IHumidityDriver& d) : _driver(d) {
    _driver.init();
}
    
float HumiditySensor::read() {
    uint32_t raw = _driver.read_raw();
    float humidity = (float(raw) / (1 << 20)) * 100.0f;

    return humidity;
}