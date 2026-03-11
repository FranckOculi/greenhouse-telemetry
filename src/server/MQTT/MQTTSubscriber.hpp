#ifndef __MQTT_SUBSCRIBER__
#define __MQTT_SUBSCRIBER__

#include "MQTT/MQTTBase.hpp"

#include <mqtt/async_client.h>
#include <string>

class MQTTSubscriberCallback : public virtual mqtt::callback {
    public :
        void message_arrived(mqtt::const_message_ptr msg) override;
};

class MQTTSubscriber : public MQTTBase {
    public:
        MQTTSubscriber(const std::string& address, const std::string& client_id, const std::string& topic);
        ~MQTTSubscriber() = default;

        void subscribe();

    private:
        MQTTSubscriberCallback cb;
};

#endif