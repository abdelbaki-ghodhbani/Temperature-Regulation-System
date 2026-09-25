/*
 * Temperature Regulation System - Arduino side
 *
 * - Reads a DS18B20 temperature sensor (1-Wire, pin 9)
 * - Sends the temperature to the Qt application over USB serial (9600 baud),
 *   formatted as comma-separated values: "23.50,"
 * - Receives the fan command (0-255) from the Qt application and applies it
 *   as a PWM duty cycle on MOTOR_PIN (through a transistor / motor driver)
 */
#include <DallasTemperature.h>
#include <OneWire.h>

#define ONE_WIRE_PIN   9
#define MOTOR_PIN      5     // must be a PWM-capable pin (Uno: 3, 5, 6, 9, 10, 11)
#define MIN_DUTY       50    // below this duty the motor does not start: switch it off

OneWire ow(ONE_WIRE_PIN);
DallasTemperature temp_sensor(&ow);

void setup()
{
  pinMode(MOTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 0);
  temp_sensor.begin();
  Serial.begin(9600);
  Serial.setTimeout(100);
}

void loop()
{
  /* Measure and send the temperature */
  temp_sensor.requestTemperatures();
  float temp = temp_sensor.getTempCByIndex(0);
  Serial.print(temp);
  Serial.print(",");
  Serial.flush();

  delay(1000);

  /* Apply the latest fan command received from the Qt application */
  if (Serial.available()) {
    int val = Serial.readStringUntil('\n').toInt();
    val = constrain(val, 0, 255);
    if (val < MIN_DUTY) val = 0;
    analogWrite(MOTOR_PIN, val);
  }
}
