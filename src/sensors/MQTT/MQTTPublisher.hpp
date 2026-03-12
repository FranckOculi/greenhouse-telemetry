#ifndef __MQTT_PUBLISHER__
#define __MQTT_PUBLISHER__

#include "MQTT/MQTTBase.hpp"

#include <mqtt/async_client.h>
#include <string>

class MQTTPublisher : public MQTTBase {
    public:
        MQTTPublisher(const std::string& address, const std::string& client_id, const std::string& topic);
        ~MQTTPublisher() = default;

        void publish(const std::string& payload, int qos = 0);
};

#endif