CXX = g++
CXXFLAGS = -Wall -Wextra
TEMPERATURE_SRC = src/sensors/temperature

all: sensor-temperature

sensor-temperature: src/main.o $(TEMPERATURE_SRC)/driver.o $(TEMPERATURE_SRC)/sensor.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f sensor-temperature src/*.o $(TEMPERATURE_SRC)/*.o

.PHONY: all clean