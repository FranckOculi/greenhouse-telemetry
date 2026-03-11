#include "MQTT/MQTTSubscriber.hpp"

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
    MQTTSubscriber h_subscriber(MQTTSubscriber::ADDRESS, MQTTSubscriber::get_client_id(MQTTSubscriber::SERVER, MQTTSubscriber::HUMIDITY), MQTTSubscriber::HUMIDITY);
    MQTTSubscriber t_subscriber(MQTTSubscriber::ADDRESS, MQTTSubscriber::get_client_id(MQTTSubscriber::SERVER, MQTTSubscriber::TEMPERATURE), MQTTSubscriber::TEMPERATURE);

    signal(SIGINT, handle_signal);

    std::cout << "[INFO] Waiting for message..." << std::endl;

    while (!stop) {}

    return 0;
}