CXX = g++
CXXFLAGS = -Wall -Wextra
LIBS = -lpaho-mqttpp3 -lpaho-mqtt3c -pthread

TEMPERATURE_SRC = src/sensors/temperature
HUMIDITY_SRC = src/sensors/humidity
MQTT_SRC = src/sensors/MQTT
SENSORS_SRC = src/main.o \
$(TEMPERATURE_SRC)/temperature_driver.o \
$(TEMPERATURE_SRC)/temperature_sensor.o \
$(HUMIDITY_SRC)/humidity_driver.o \
$(HUMIDITY_SRC)/humidity_sensor.o \
$(MQTT_SRC)/MQTTPublisher.o

sensors: $(SENSORS_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@  $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f sensors src/*.o $(TEMPERATURE_SRC)/*.o $(HUMIDITY_SRC)/*.o $(MQTT_SRC)/*.o

.PHONY: clean