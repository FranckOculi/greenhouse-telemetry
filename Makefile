CXX = g++
CFLAGS = -Wall -Wextra

sensor-temperature: src/main.o src/sensors/temperature/driver.o src/sensors/temperature/sensor.o
	$(CXX) $(CGLAGS) -o $@ $^

%.o: src/%.cpp src/sensors/temperature/%.cpp
	$(CXX) $(CGLAGS) -o $@ -c $^

clean:
	rm -rf src/*.o src/sensors/temperature/*.o

.PHONY: clean