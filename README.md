# Smart Baby Cradle

An IoT-based smart baby cradle monitoring system that uses sensors to track temperature, humidity, sound (crying detection), and diaper wetness, along with a camera for video monitoring. The system integrates with Blynk for remote monitoring and control, including servo motor control for cradle rocking.

## Features

- **Temperature & Humidity Monitoring**: Uses DHT11 sensor to monitor ambient temperature and humidity.
- **Crying Detection**: Sound sensor detects baby crying and sends alerts via Blynk.
- **Diaper Wetness Detection**: Soil moisture sensor monitors diaper wetness levels.
- **Video Monitoring**: ESP32 camera provides live video streaming via web server.
- **Remote Control**: Servo motor for cradle rocking, controllable via Blynk app.
- **Alerts**: Automatic notifications for high temperature, high wetness, and crying detection.
- **IoT Integration**: Connects to Blynk cloud for real-time data visualization and remote access.

## Hardware Requirements

- ESP8266 microcontroller (for sensors)
- ESP32-CAM module (for camera)
- DHT11 temperature and humidity sensor
- Sound sensor module
- Soil moisture sensor
- Servo motor
- Jumper wires and breadboard
- Power supply (appropriate for ESP modules)

### Pin Connections (ESP8266)

- DHT11: D4 (GPIO 2)
- Sound Sensor: D2 (GPIO 4)
- Soil Moisture: A0
- Servo: D1 (GPIO 5)
- Servo Switch: D6 (dummy pin for Blynk control)

## Software Requirements

- Arduino IDE
- Blynk app and account
- Required libraries:
  - ESP8266WiFi
  - BlynkSimpleEsp8266
  - DHT
  - Servo
  - SimpleTimer (included)

## Setup Instructions

1. **Install Arduino IDE** and add ESP8266 and ESP32 board support.

2. **Install Libraries**:
   - Open Arduino IDE Library Manager and install:
     - Blynk
     - DHT sensor library
     - Servo
   - Or use the included libraries in the project folders.

3. **Blynk Setup**:
   - Create a Blynk account and new project.
   - Get the Auth Token and update in the code.
   - Configure virtual pins in Blynk app:
     - V5: Temperature gauge
     - V7: Wetness gauge
     - Servo control switch

4. **Upload Code**:
   - For sensors (ESP8266): Upload `Sensors_code/Sensors_code.ino`
   - For camera (ESP32): Upload `CameraWebServer/CameraWebServer.ino`

5. **WiFi Configuration**:
   - Update SSID and password in both codes.

6. **Hardware Assembly**:
   - Connect sensors as per pin connections.
   - Ensure proper power supply.

## Usage

1. Power on the devices.
2. Open Blynk app to monitor sensor data and control the servo.
3. Access camera stream via the ESP32's IP address (check serial monitor for URL).
4. Receive alerts for temperature > 25°C, wetness > 30%, or crying detection.

## Circuit Diagram

Refer to the included PNG files:
- `Ckt Connection.png`: Main circuit connections
- `Camera and TTL Programmer.png`: Camera module connections

## Project Structure

- `Sensors_code/`: Arduino code for ESP8266 sensor monitoring
- `CameraWebServer/`: ESP32 camera web server code
- `blynk-library-master/`: Blynk library (if needed)
- `ESP8266wifi-master/`: ESP8266 WiFi library
- `SimpleTimer-master/`: Timer library for periodic updates

## Contributing

Feel free to contribute improvements or report issues.

## License

This project is open-source. Check individual library licenses for details.