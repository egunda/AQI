# 🏡 Arduino Air Quality & Environment Monitor

This project uses an **Arduino Uno** to create a real-time environmental monitor displayed on a 16x2 I2C LCD screen. It integrates three primary sensors: the **MQ-135 Gas Sensor** for air quality, and the **DHT11** for temperature and humidity.

## ✨ Features

* **Real-time Air Quality Monitoring:** Reads the raw analog value (A: 0-1023) from the MQ-135 sensor and provides an interpreted status (**GOOD**, **MODERATE**, or **DANGER**).
* **Temperature and Humidity Display:** Displays ambient temperature (in Celsius) and relative humidity.
* **Optimized LCD Layout:** Efficiently displays all sensor data on a 16x2 screen:
    * **Line 1:** Air Quality Value and Temperature (`A:125 T:25C`)
    * **Line 2:** Humidity Value and Air Quality Status (`H:60% MODERATE`)

## ⚙️ Hardware Components

| Component | Quantity | Notes |
| :--- | :--- | :--- |
| **Arduino Uno** | 1 | |
| **16x2 I2C LCD** | 1 | (Common Address: 0x27) |
| **MQ-135 Gas Sensor** | 1 | (Air Quality, Analog Output) |
| **DHT11 Sensor** | 1 | (Temperature & Humidity) |
| **Jumper Wires** | Varies | |
| **Breadboard** | 1 | (Optional, for connections) |

## 🔌 Wiring Diagram & Connections

Follow these connections carefully. The I2C LCD uses pins A4 and A5 for communication, and the sensors use dedicated analog pins.

### Sensor Pinout

| Sensor | Pin | Arduino Pin | Purpose |
| :--- | :--- | :--- | :--- |
| **MQ-135** | A0 | **A0** | Air Quality Analog Data |
| **DHT11** | Data | **A3** | Temp/Humidity Digital Data |
| **I2C LCD** | SDA | **A4** | I2C Data |
| **I2C LCD** | SCL | **A5** | I2C Clock |

* All VCC pins connect to Arduino's **5V**.
* All GND pins connect to Arduino's **GND**.



## 💻 Software & Libraries

This project requires the following libraries to be installed in your Arduino IDE:

1.  **LiquidCrystal_I2C Library:** Used for communicating with the 16x2 I2C LCD.
    * *(Search for `LiquidCrystal I2C` in the Library Manager)*
2.  **DHT sensor library:** Used for reading temperature and humidity from the DHT11.
    * *(Search for `DHT sensor library` by Adafruit in the Library Manager)*
3.  **Adafruit Unified Sensor:** A dependency required by the DHT library.
    * *(Search for `Adafruit Unified Sensor` in the Library Manager)*

## 🚀 Getting Started

1.  **Install Libraries:** Install the three required libraries via the Arduino Library Manager.
2.  **Upload Code:** Copy the full code block (e.g., `main.ino`) into a new Arduino sketch and upload it to the Arduino Uno board.
3.  **Calibration:** Allow the MQ-135 sensor to "burn-in" for at least 5-10 minutes after initial power-on to get stable readings. Adjust the air quality thresholds (`< 200`, `< 400`) in the code based on your clean-air baseline.

## 📝 Code Logic Summary

The `loop()` function performs the following steps every 1.5 seconds:
1.  Reads temperature and humidity from **A3** (DHT11).
2.  Reads the raw air quality value from **A0** (MQ-135).
3.  Determines the status (`GOOD`, `MODERATE`, `DANGER`) based on the AQ value.
4.  Updates **Line 1** with Air Quality and Temperature.
5.  Updates **Line 2** with Humidity and the Air Quality Status.
