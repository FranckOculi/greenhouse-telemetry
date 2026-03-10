#include "sensors/temperature/temperature_driver.hpp"
#include "sensors/temperature/temperature_sensor.hpp"
#include "sensors/humidity/humidity_driver.hpp"
#include "sensors/humidity/humidity_sensor.hpp"

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

    signal(SIGINT, handle_signal);

    while (!stop) {
        printf("Temprature : %.2f°c\n", t_sensor.read());
        printf("Humidity : %.f%%\n", h_sensor.read());

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}