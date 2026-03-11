CXX = g++
CXXFLAGS = -Wall -Wextra -I src/
LIBS = -lpaho-mqttpp3 -lpaho-mqtt3as -lpaho-mqtt3c -pthread

MQTT_PATH = src/MQTT
MQTT_SRC = $(MQTT_PATH)/MQTTBase.O

SENSORS_PATH = src/sensors
TEMPERATURE_PATH = $(SENSORS_PATH)/temperature
HUMIDITY_PATH = $(SENSORS_PATH)/humidity
MQTT_PUBLISHER_PATH = $(SENSORS_PATH)/MQTT
SENSORS_SRC = \
$(MQTT_PATH)/MQTTBase.o \
$(SENSORS_PATH)/main.o \
$(TEMPERATURE_PATH)/temperature_driver.o \
$(TEMPERATURE_PATH)/temperature_sensor.o \
$(HUMIDITY_PATH)/humidity_driver.o \
$(HUMIDITY_PATH)/humidity_sensor.o \
$(MQTT_PUBLISHER_PATH)/MQTTPublisher.o

SERVER_PATH = src/server
MQTT_SUBSCRIBER_PATH = $(SERVER_PATH)/MQTT
SERVER_SRC = \
$(MQTT_PATH)/MQTTBase.o \
$(SERVER_PATH)/main.o \
$(MQTT_SUBSCRIBER_PATH)/MQTTSubscriber.o

sensors: $(SENSORS_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@  $(LIBS)

server: $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@  $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f sensors server \
	$(MQTT_PATH)/*.o \
	$(SERVER_PATH)/main.o \
	$(SENSORS_PATH)/*.o $(TEMPERATURE_PATH)/*.o $(HUMIDITY_PATH)/*.o $(MQTT_PUBLISHER_PATH)/*.o \

.PHONY: clean