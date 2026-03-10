# Greenhouse 🌱
Greenhouse is an in-progress C++ project designed to manage and monitor multiple sensors in a greenhouse environment.

## :book: Description
The goal is to create an application to monitor greenhouse sensors, such as temperature and humidity, while supporting scalable sensor management and MQTT-based communication.

As the project is still in progress:
- The code is not yet optimized for embedded runtime.
- Sensor drivers are currently simulated.
- MQTT is used for publishing sensor data, with Mosquitto as the broker.

Currently, Greenhouse includes:
- Sensor drivers with interface classes, e.g., humidity_driver, temperature_driver.
- Simulated sensors for testing the system without hardware.
- MQTT publisher using Paho MQTT C++.
- A test `main` program that continuously publishes sensor data to a broker.

## :hammer_and_wrench: Requirements
- g++
- Make
- Paho MQTT c++
- Mosquitto (MQTT broker) for testing

## :rocket: Usage
### 1️⃣ Build the project

```bash
make sensors
```
This will create the "sensors" binary.

### 2️⃣ Start a broker and subscribers
In my case, I'm using Mosquitto.
```bash
systemctl start mosquitto
mosquitto -t temperature -v
mosquitto -t humidity -v
```

### 3️⃣  Run the program
```bash
./sensors
```
Sensors will push their random values to the broker.

<br/>

## :building_construction: TODO
-   [x] Create sensor stack (interface, driver and class) for embedded devices
-   [x] Implement publisher feature for sensors (MQTT)
-   [ ] Create server stack :
        - Broker setup
        - Subscriber server to collect and store sensor data
-   [ ] Create persistence for sensor data
-   [ ] Add Dashboard for visualising metrics
-   [ ] Implement error handling and logging
-   [ ] Optimize embedded code base for embedded runtime
-   [ ] Add configuration management for sensors and broker