#include <DallasTemperature.h>
#include <OneWire.h>

#define motor 13

OneWire ow(9);
DallasTemperature temp_sensor(&ow);

void setup()
{
  pinMode(motor, OUTPUT);
  analogWrite(motor, 0);
  temp_sensor.begin();
  Serial.begin(9600);
}

void loop()
{
  temp_sensor.requestTemperatures();
  double temp = temp_sensor.getTempCByIndex(0);
    Serial.print(temp);
  Serial.print(",");
  Serial.flush();
  delay(1000);

    String message = Serial.readStringUntil('\n'); // Read the incoming message
    int val = message.toInt();
    if (val >50){
    analogWrite(motor, val);
    delay(1000);}
    
 


}
