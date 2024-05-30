#include <ArduinoJson.h>
#define ledpin 2 //defining the OUTPUT pin for LED
int intensity;

void setup() {
  Serial.begin(115200);
  pinMode(ledpin,OUTPUT);
  }

void loop() 
{
  Receive();
  analogWrite(ledpin, intensity);
}

void Receive()
{
  if (Serial.available())
  {
    StaticJsonDocument<50> doc;
    DeserializationError err = deserializeJson(doc, Serial);
    if (err == DeserializationError::Ok)
    {
      intensity = doc["intensity"].as<int>();
      Serial.println("intensity:"+String(intensity));
    }
  }
  else {while (Serial.available()>0){Serial.read();}}
}
