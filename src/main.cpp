#include "sensors/temperature/temperature_driver.hpp"
#include "sensors/temperature/temperature_sensor.hpp"
#include "sensors/humidity/humidity_driver.hpp"
#include "sensors/humidity/humidity_sensor.hpp"
#include "sensors/MQTT/MQTTPublisher.hpp"

#include <iostream>
#include <csignal>
#include <atomic>
#include <chrono>
#include <thread>

std::atomic<bool> stop(false);

const std::string ADDRESS = "tcp://localhost:1883";

void handle_signal(int) {
    stop = true;
}

int main(void) {
    AHT20TemperatureDriverSimulated t_driver;
    TemperatureSensor t_sensor(t_driver);

    AHT20HumidityDriverSimulated h_driver;
    HumiditySensor h_sensor(h_driver);

    MQTTPublisher t_publisher(ADDRESS, TemperatureSensor::SENSOR_ID, TemperatureSensor::SENSOR_NAME);
    MQTTPublisher h_publisher(ADDRESS, HumiditySensor::SENSOR_ID, HumiditySensor::SENSOR_NAME);

    signal(SIGINT, handle_signal);

    while (!stop) {
        std::cout << "[INFO] Waking up sensors..." << std::endl;

        std::string t_value = std::to_string(t_sensor.read());
        t_publisher.publish(t_value, 1);

        std::string h_value = std::to_string(h_sensor.read());
        h_publisher.publish(h_value, 1);

        std::cout << "[INFO] Going to sleep for 10 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}