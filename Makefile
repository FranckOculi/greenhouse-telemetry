CXX = g++
CXXFLAGS = -Wall -Wextra
LIBS = -lpaho-mqttpp3 -lpaho-mqtt3c -pthread

SENSORS_PATH = src/sensors
TEMPERATURE_PATH = $(SENSORS_PATH)/temperature
HUMIDITY_PATH = $(SENSORS_PATH)/humidity
MQTT_PATH = $(SENSORS_PATH)/MQTT
SENSORS_SRC = $(SENSORS_PATH)/main.o \
$(TEMPERATURE_PATH)/temperature_driver.o \
$(TEMPERATURE_PATH)/temperature_sensor.o \
$(HUMIDITY_PATH)/humidity_driver.o \
$(HUMIDITY_PATH)/humidity_sensor.o \
$(MQTT_PATH)/MQTTPublisher.o

sensors: $(SENSORS_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@  $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f sensors src/main.o $(SENSORS_PATH)/*.o $(TEMPERATURE_PATH)/*.o $(HUMIDITY_PATH)/*.o $(MQTT_PATH)/*.o

.PHONY: clean