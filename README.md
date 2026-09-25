# Temperature Regulation System

A small closed-loop temperature system with two parts: **Arduino** firmware that reads a **DS18B20** digital temperature sensor and drives a fan motor with PWM, and a **Qt desktop application** that shows the live temperature and talks to the board over serial.

## How it works

```
DS18B20 ──1-Wire──► Arduino Uno ──USB serial (9600 baud)──► Qt desktop app
                        │   ◄──── motor speed command ─────────┘
                        └──PWM──► Fan motor
```

- The Arduino sends a new temperature reading every second, formatted as comma-separated values.
- The Qt app finds the Arduino Uno on its own (by USB vendor and product ID), buffers the serial stream, parses the values and shows them on an LCD-style display.
- The app can send a speed value back, and the Arduino applies it to the motor as a PWM duty cycle.

## Repository structure

```
dallas_temp_sensor/   # Arduino sketch (DS18B20 + PWM motor control)
DS18B20_Qt/           # Qt Widgets application (QSerialPort)
```

## Getting started

### Arduino
1. Install the **OneWire** and **DallasTemperature** libraries.
2. Connect the DS18B20 data line to **pin 9** (with a 4.7 kΩ pull-up) and the motor driver to **pin 13**.
3. Upload `dallas_temp_sensor/dallas_temp_sensor.ino`.

### Qt application
1. Open `DS18B20_Qt/DS18B20_Qt.pro` in **Qt Creator** (Qt 5+ with the `serialport` module).
2. Build and run with the Arduino plugged in.

## Tech stack

`C++` · `Qt Widgets` · `QSerialPort` · `Arduino` · `DS18B20` · `PWM`

## Author

**Abdelbaki Ghodhbani** — [LinkedIn](https://www.linkedin.com/in/abdelbaki-ghodhbani) · [GitHub](https://github.com/abdelbaki-ghodhbani)
