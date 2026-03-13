# Greenhouse 🌱
Greenhouse is an **in-progress C++ project** designed to manage and monitor multiple sensors in a greenhouse environment.

## :book: Description
The goal is to create an application to monitor greenhouse sensors, such as temperature and humidity, while supporting scalable sensor management and **MQTT-based communication**.

#### Current status
- The project is still in progress:
- code is not yet optimized for embedded runtime.
- Sensor drivers are currently simulated.
- MQTT is used for publishing sensor data, with **Mosquitto** as the broker.
- InfluxDB is used to store sensor data.
- Grafana to monitor metrics.

#### Features
- Sensor stack :
  - Sensor drivers with interface classes, e.g., **humidity_driver, temperature_driver**.
  - Simulated sensors for testing the system without hardware.
  - **MQTT publisher** using **Paho MQTT C++** to publish sensor data.
  - A test `main` program that continuously publishes sensor readings to a broker.
- A server stack :
  - **MQTTSubscribers** using **Paho MQTT C++** to receive sensor data.
  - **InfluxDB** to store sensor metrics.
  - Database service using the simple `influxdb-cpp` header as client from **orca-zhang**.
  - A test `main` program that continuously displays sensor readings received from the broker.

## :hammer_and_wrench: Requirements
- g++
- Make
- Paho MQTT C++
- Mosquitto (MQTT broker) for testing
- InfluxDB
- Grafana to monitor metrics

## :rocket: Usage
### 1️⃣ Build the server

```bash
make server
```
This will create the "server" binary.

### 2️⃣ Build sensors stack

```bash
make sensors
```
This will create the "sensors" binary.

### 3️⃣ Start a broker

Using Mosquitto for example:

```bash
systemctl start mosquitto
```

### 4️⃣ Run the program
```bash
./server
./sensors
```
- Sensors will push their random values to the broker.
- The server will store sensor metrics to the database.

### 5️⃣ Monitor metrics

Using grafana for example:
```bash
systemctl start grafana-server
```

Now we can monitor metrics from `http://localhost:3000`.

## :building_construction: TODO
-   [x] Create sensor stack (interface, driver and class) for embedded devices
-   [x] Implement publisher feature for sensors (MQTT)
-   [x] Create server stack :
    - [x] Subscriber server
    - [x] Sensor data persistence
    - [x] Broker setup
-   [x] Synchronize sensor publishments 
-   [ ] Implement error handling and logging
-   [ ] Optimize embedded code base for embedded runtime