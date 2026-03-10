#include "MQTTPublisher.hpp"

#include <iostream>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>

MQTTPublisher::MQTTPublisher(const std::string& address, const std::string& client_id, const std::string& topic) : client(address, client_id), topic(topic) {
    mqtt::connect_options connect_options;
    connect_options.set_keep_alive_interval(20);
    connect_options.set_clean_session(false);

    try {
        std::cout << "[INFO] " << topic << " -> Connecting to broker" << std::endl;
        client.connect(connect_options)->wait();
        std::cout << "[INFO] " << topic << " -> Connected !" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "[ERROR] " << topic << " -> Connection failed " << exc.what() << std::endl;
        throw;
    }
}

MQTTPublisher::~MQTTPublisher() {
    try {
        client.disconnect();
        std::cout << "[INFO] " << topic << " -> Disconnected !" << std::endl;
    } catch (...) {}
}

void MQTTPublisher::publish(const std::string& payload, int qos) {
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(qos);
    client.publish(msg)->wait();
    std::cout << "[SEND] " << topic << " -> " << payload << std::endl;
}