#include "temperature/temperature_driver.hpp"
#include "temperature/temperature_sensor.hpp"
#include "humidity/humidity_driver.hpp"
#include "humidity/humidity_sensor.hpp"
#include "MQTT/MQTTPublisher.hpp"

#include <iostream>
#include <csignal>
#include <atomic>
#include <chrono>
#include <thread>

std::atomic<bool> stop(false);

void handle_signal(int) {
    stop = true;
}

int main(void) {
    AHT20TemperatureDriverSimulated t_driver;
    TemperatureSensor t_sensor(t_driver);

    AHT20HumidityDriverSimulated h_driver;
    HumiditySensor h_sensor(h_driver);

    MQTTPublisher t_publisher(MQTTPublisher::ADDRESS, MQTTPublisher::get_client_id(MQTTPublisher::SENSOR, MQTTPublisher::TEMPERATURE), MQTTPublisher::TEMPERATURE);
    MQTTPublisher h_publisher(MQTTPublisher::ADDRESS, MQTTPublisher::get_client_id(MQTTPublisher::SENSOR, MQTTPublisher::HUMIDITY), MQTTPublisher::HUMIDITY);

    signal(SIGINT, handle_signal);

    while (!stop) {
        std::cout << "[INFO] Waking up sensors..." << std::endl;

        std::string t_value = std::to_string(t_sensor.read());
        t_publisher.publish(t_value);

        std::string h_value = std::to_string(h_sensor.read());
        h_publisher.publish(h_value);

        std::cout << "[INFO] Going to sleep for 10 seconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}