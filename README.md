# Temperature Regulation System

A closed-loop temperature control system with two parts. The **Arduino Uno** reads a **DS18B20** digital temperature sensor and drives a DC fan with **PWM**. A **Qt desktop application** shows the live temperature, lets you set a target temperature, and computes the fan command.

## How it works

```
DS18B20 ──1-Wire (D9)──► Arduino Uno ──USB serial 9600 baud──► Qt desktop app
                             │   ◄──── fan command 0–255 ──────────┘
                             └──PWM (D5)──► transistor / driver ──► DC fan
```

1. Every second the Arduino sends the temperature as comma-separated text (`23.50,`).
2. The Qt app finds the Arduino Uno automatically (USB VID 0x2341 / PID 0x0043), buffers the serial stream, parses each reading and shows it on an LCD-style display.
3. The app computes a **proportional cooling command**:
   - temperature ≤ target: fan **off** (0)
   - temperature above target: duty = 255 × (T − T<sub>target</sub>) / 5 °C, capped at **255** (full speed 5 °C above the target)
4. The command goes back to the Arduino (`"128\n"`), which applies it as a PWM duty cycle on D5. Values below 50 switch the fan off, because the motor cannot start at such a low duty.

The target temperature is set with a slider in the app (25–125 °C).

## Repository structure

```
dallas_temp_sensor/   # Arduino sketch: DS18B20 reading + PWM fan control
DS18B20_Qt/           # Qt Widgets application (QSerialPort)
```

## Getting started

### Arduino
1. Install the **OneWire** and **DallasTemperature** libraries in the Arduino IDE.
2. Wiring:
   | Part | Arduino Uno |
   |---|---|
   | DS18B20 data | **D9**, with a 4.7 kΩ pull-up to 5 V |
   | Fan driver input (NPN transistor / MOSFET gate) | **D5** (PWM) |
   | Fan supply | external supply through the transistor, with a flyback diode |
3. Upload `dallas_temp_sensor/dallas_temp_sensor.ino`.

### Qt application
1. Open `DS18B20_Qt/DS18B20_Qt.pro` in **Qt Creator** (Qt 5 or later, with the `serialport` module).
2. Build and run with the Arduino plugged in over USB.

## Tech stack

`C++` · `Qt Widgets` · `QSerialPort` · `Arduino` · `DS18B20 / 1-Wire` · `PWM` · `Proportional control`

## Author

**Abdelbaki Ghodhbani**, Embedded Software Engineer: [LinkedIn](https://www.linkedin.com/in/abdelbaki-ghodhbani) · [GitHub](https://github.com/abdelbaki-ghodhbani)
