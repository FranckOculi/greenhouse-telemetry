#include "MQTT/MQTTSubscriber.hpp"
#include "db/database_service.hpp"

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
    DatabaseService db(DatabaseService::HOST, DatabaseService::PORT, DatabaseService::NAME);

    MQTTSubscriber h_subscriber(MQTTSubscriber::ADDRESS, MQTTSubscriber::get_client_id(MQTTSubscriber::SERVER, MQTTSubscriber::HUMIDITY), MQTTSubscriber::HUMIDITY, db);
    MQTTSubscriber t_subscriber(MQTTSubscriber::ADDRESS, MQTTSubscriber::get_client_id(MQTTSubscriber::SERVER, MQTTSubscriber::TEMPERATURE), MQTTSubscriber::TEMPERATURE, db);

    signal(SIGINT, handle_signal);

    std::cout << "[INFO] Waiting for message..." << std::endl;

    while (!stop) {}

    return 0;
}