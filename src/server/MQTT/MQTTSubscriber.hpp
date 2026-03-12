#ifndef __MQTT_SUBSCRIBER__
#define __MQTT_SUBSCRIBER__

#include "MQTT/MQTTBase.hpp"
#include "server/db/database_service.hpp"

#include <mqtt/async_client.h>
#include <string>

class MQTTSubscriberCallback : public virtual mqtt::callback {
    public :
        MQTTSubscriberCallback(DatabaseService db);
        void message_arrived(mqtt::const_message_ptr msg) override;

    private :
        DatabaseService _db;
};

class MQTTSubscriber : public MQTTBase {
    public:
        MQTTSubscriber(const std::string& address, const std::string& client_id, const std::string& topic, DatabaseService& db);
        ~MQTTSubscriber() = default;

        void subscribe();

    private:
        DatabaseService _db;
        MQTTSubscriberCallback _cb;
};

#endif