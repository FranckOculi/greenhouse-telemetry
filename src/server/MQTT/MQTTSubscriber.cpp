#include "MQTTSubscriber.hpp"

#include <iostream>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>
#include <ctime>
#include <stdarg.h>

void MQTTSubscriberCallback::message_arrived(mqtt::const_message_ptr msg) {
    time_t current_time = time(NULL);
    tm *tm_info = localtime(&current_time);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    fprintf(stdout, "[%s] - ", buffer);

    std::cout << msg->get_topic() << " -> " << msg->to_string() << std::endl;
}

MQTTSubscriber::MQTTSubscriber(const std::string& address, const std::string& client_id, const std::string& topic) 
: MQTTBase(address, client_id, topic) {
    connect(&cb);
    subscribe();
}

void MQTTSubscriber::subscribe() {
    try {
        std::cout << "[INFO] " << topic << " -> Subscribing to " << topic << std::endl;
        client.subscribe(topic, 1)->wait();
        std::cout << "[INFO] " << topic << " -> Subscribed !" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "[ERROR] " << topic << " -> Connection failed " << exc.what() << std::endl;
        throw;
    }
}