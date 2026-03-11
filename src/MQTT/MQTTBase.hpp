#ifndef __MQTT_BASE__
#define __MQTT_BASE__

#include <mqtt/async_client.h>
#include <mqtt/connect_options.h>
#include <mqtt/message.h>
#include <string>

class MQTTBase {
    public :
        static const std::string SENSOR;
        static const std::string SERVER;
        
        static const std::string TEMPERATURE;
        static const std::string HUMIDITY;

        static const std::string ADDRESS;

        MQTTBase(const std::string& address, const std::string& client_id, const std::string& topic);
        ~MQTTBase();

        void connect(mqtt::callback* cb = nullptr);

        static std::string get_client_id(std::string client_name, std::string topic);
    
    protected :
        mqtt::async_client client;
        std::string topic;
};

#endif