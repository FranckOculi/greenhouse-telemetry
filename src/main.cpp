#include "sensors/temperature/driver.hpp"
#include "sensors/temperature/sensor.hpp"

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
    AHT20DriverSimulated driver;
    TemperatureSensor t_sensor(driver);

    signal(SIGINT, handle_signal);

    while (!stop) {
        printf("%.2f\n", t_sensor.read());

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}