#include "MQTTBase.hpp"

const std::string MQTTBase::SENSOR = "sensor";
const std::string MQTTBase::SERVER = "server";
const std::string MQTTBase::TEMPERATURE = "temperature";
const std::string MQTTBase::HUMIDITY = "humidity";

const std::string MQTTBase::ADDRESS = "tcp://localhost:1883";

int MQTTBase::QOS = 1;

MQTTBase::MQTTBase(const std::string& address, const std::string& client_id, const std::string& topic) 
: client(address, client_id), topic(topic) {}

MQTTBase::~MQTTBase() {
    try {
        if (client.is_connected()) {
            client.disconnect();
            std::cout << "[INFO] " << topic << " -> Disconnected !" << std::endl;
        }
    } catch (...) {}
}

void MQTTBase::connect(mqtt::callback* cb) {
    mqtt::connect_options connect_options;
    connect_options.set_keep_alive_interval(20);
    connect_options.set_clean_session(false);

    if (cb) {
        client.set_callback(*cb);
    }

    try {
        std::cout << "[INFO] " << topic << " -> Connecting to broker" << std::endl;
        client.connect(connect_options)->wait();
        std::cout << "[INFO] " << topic << " -> Connected !" << std::endl;
    } catch (const mqtt::exception& exc) {
        std::cerr << "[ERROR] " << topic << " -> Connection failed " << exc.what() << std::endl;
        throw;
    }
}

std::string MQTTBase::get_client_id(std::string client_name, std::string topic) {
    return client_name + '/' + topic; 
}