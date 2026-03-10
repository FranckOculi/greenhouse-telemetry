CXX = g++
CXXFLAGS = -Wall -Wextra

TEMPERATURE_SRC = src/sensors/temperature
HUMIDITY_SRC = src/sensors/humidity
SENSORS_SRC = src/main.o \
$(TEMPERATURE_SRC)/temperature_driver.o \
$(TEMPERATURE_SRC)/temperature_sensor.o \
$(HUMIDITY_SRC)/humidity_driver.o \
$(HUMIDITY_SRC)/humidity_sensor.o

all: sensors

sensors: $(SENSORS_SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f sensors src/*.o $(TEMPERATURE_SRC)/*.o $(HUMIDITY_SRC)/*.o

.PHONY: all clean