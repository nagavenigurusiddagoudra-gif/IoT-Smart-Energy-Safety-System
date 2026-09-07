# IoT-Smart-Energy-Safety-System
**IoT-Based Smart Energy &amp; Safety Management System using ESP32 — monitors temperature, humidity, gas, occupancy and light, with automatic appliance control and Blynk IoT monitoring.**

# IoT-Based Smart Energy & Safety Management System

An ESP32-based IoT system for smart energy management, environmental monitoring, automatic appliance control, and gas safety monitoring using Blynk IoT.

## 📌 Project Overview

The IoT-Based Smart Energy & Safety Management System is designed to improve energy efficiency and safety in smart environments. The system uses an ESP32 as the main controller and integrates multiple sensors to monitor temperature, humidity, human presence, light intensity, and gas levels.

Based on the sensor readings, the ESP32 automatically controls electrical appliances such as a fan and light. In case of a gas leak or abnormal gas level, the system activates a buzzer and displays a safety alert. Sensor data and system status are also transmitted to the Blynk IoT platform for real-time remote monitoring.

## 🎯 Objectives

- Monitor temperature and humidity in real time.
- Detect human presence using a PIR sensor.
- Automatically control the fan based on temperature and occupancy.
- Automatically control the light based on occupancy and ambient light.
- Monitor gas levels for safety.
- Generate an alert when the gas level exceeds the programmed threshold.
- Display system information on a 16×2 LCD.
- Monitor sensor values remotely using Blynk IoT.
- Reduce unnecessary energy consumption through automation.

## ✨ Key Features

- 🌡️ Temperature & Humidity Monitoring
- 👤 Human Presence Detection
- 💡 Automatic Light Control
- 🌀 Automatic Fan Control
- 🛡️ Gas Safety Monitoring
- 🔔 Gas Alert Buzzer
- 📟 LCD Local Display
- ☁️ Blynk IoT Cloud Monitoring
- 📊 Historical Sensor Data
- ⚡ Energy-Saving Automation

## 🔧 Hardware Requirements

- ESP32 DevKit
- DHT22 Temperature & Humidity Sensor
- PIR Motion Sensor
- LDR / Photoresistor
- MQ-2 Gas Sensor
- Relay Module
- LED (Light)
- Buzzer
- 16×2 I2C LCD
- Resistor
- PCB / Connecting Wires
- Power Supply

## 💻 Software Requirements

- Arduino IDE
- ESP32 Board Package
- Blynk IoT
- Required Arduino Libraries:
  - DHT Sensor Library
  - Adafruit Unified Sensor
  - LiquidCrystal I2C
  - Blynk
  - WiFi

## 📍 Pin Configuration

| Component | ESP32 Pin |
|---|---:|
| DHT22 Data | GPIO 4 |
| Relay | GPIO 18 |
| LED / Light | GPIO 19 |
| Buzzer | GPIO 5 |
| PIR Sensor | GPIO 27 |
| LDR | GPIO 34 |
| MQ-2 Gas Sensor | GPIO 35 |
| LCD SDA | GPIO 21 |
| LCD SCL | GPIO 22 |

## ⚙️ Working Principle

The sensors continuously collect information from the surrounding environment. The ESP32 receives and processes these sensor readings.

### Fan Control

The fan is turned ON when:

**Person detected + Temperature > 30°C**

Otherwise, the fan remains OFF.

### Light Control

The light is turned ON when:

**Person detected + Low ambient light**

Otherwise, the light remains OFF.

### Gas Safety

When the gas sensor reading exceeds the programmed threshold:

**Gas Level > 2500 → Buzzer ON + Gas Alert**

The gas alert is also displayed on the LCD and sent to the Blynk IoT dashboard.

## 🔄 System Flow

```text
Sensors
   ↓
ESP32 Controller
   ↓
Read Sensor Values
   ↓
Process & Compare Conditions
   ↓
┌───────────────┬───────────────┐
│               │               │
Fan Control   Light Control   Gas Safety
│               │               │
Relay          LED             Buzzer
│               │               │
└───────────────┴───────────────┘
                ↓
             LCD Display
                ↓
          Wi-Fi Connection
                ↓
           Blynk IoT Cloud
                ↓
       Remote Monitoring
