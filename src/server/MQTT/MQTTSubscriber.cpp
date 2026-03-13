#include "MQTTSubscriber.hpp"

#include <iostream>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>
#include <ctime>
#include <stdarg.h>
#include <stdlib.h>
#include <mutex>
#include <optional>

struct SensorCache {
    std::optional<int> humidity;
    std::optional<int> temperature;
    std::mutex mtx;
};

SensorCache _cache;

MQTTSubscriberCallback::MQTTSubscriberCallback(DatabaseService db) : _db(db) {}

void MQTTSubscriberCallback::message_arrived(mqtt::const_message_ptr msg) {
    time_t current_time = time(NULL);
    tm *tm_info = localtime(&current_time);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(stdout, "[%s] - ", buffer);

    std::cout << msg->get_topic() << " -> " << msg->to_string() << std::endl;

    std::string payload = msg->get_payload();
    int value = std::stoi(payload);
    
    std::lock_guard<std::mutex> lock(_cache.mtx);
    if (msg->get_topic() == "temperature") {
        _cache.temperature = value;
    } else if (msg->get_topic() == "humidity") {
        _cache.humidity = value;
    }

    if (_cache.humidity.has_value() && _cache.temperature.has_value()) {
        try {
            std::cout << "Registering value\n";

            DatabaseService::Raw h {
                "humidity",
                _cache.humidity.value()
            };

            DatabaseService::Raw t {
                "temperature",
                _cache.temperature.value()
            };

            _db.insert(DatabaseService::NAME, h, t);
            std::cout << "Value registered\n";

            _cache.humidity.reset();
            _cache.temperature.reset();
        } catch (std::exception& exc) {
            std::cerr << "[ERROR] -> Registration failed " << exc.what() << std::endl;
            _cache.humidity.reset();
            _cache.temperature.reset();
        }
    }
}

MQTTSubscriber::MQTTSubscriber(const std::string& address, const std::string& client_id, const std::string& topic, DatabaseService& db)
: MQTTBase(address, client_id, topic), _db(db), _cb(db) {
    connect(&_cb);
    subscribe();
}

void MQTTSubscriber::subscribe() {
    try {
        std::cout << "[INFO] " << topic << " -> Subscribing to " << topic << std::endl;
        client.subscribe(topic, MQTTSubscriber::QOS)->wait();
        std::cout << "[INFO] " << topic << " -> Subscribed !" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "[ERROR] " << topic << " -> Connection failed " << exc.what() << std::endl;
        throw;
    }
}