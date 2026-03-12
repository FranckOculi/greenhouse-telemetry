#include "MQTTPublisher.hpp"

#include <iostream>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>

MQTTPublisher::MQTTPublisher(const std::string& address, const std::string& client_id, const std::string& topic) 
: MQTTBase(address, client_id, topic) {
    connect();
}

void MQTTPublisher::publish(const std::string& payload, int qos) {
    mqtt::message_ptr msg = mqtt::make_message(topic, payload);
    msg->set_qos(qos);
    client.publish(msg)->wait();
    std::cout << "[SEND] " << topic << " -> " << payload << std::endl;
}