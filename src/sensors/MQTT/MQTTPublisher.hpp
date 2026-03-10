#ifndef __MQTT_PUBLISHER__
#define __MQTT_PUBLISHER__

#include <mqtt/async_client.h>
#include <string>

class MQTTPublisher {
    public:
        MQTTPublisher(const std::string& address, const std::string& client_id, const std::string& topic);
        ~MQTTPublisher();
        void publish(const std::string& payload, int qos = 0);

    private:
        mqtt::async_client client;
        std::string topic;
        mqtt::token_ptr connection_token;
};

#endif