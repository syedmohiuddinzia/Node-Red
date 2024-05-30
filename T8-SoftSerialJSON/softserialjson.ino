#include <ArduinoJson.h>
#define rxPin 16
#define txPin 17
#define ledpin 2
int intensity;
long count=0;
String flag;
long lastMsg = 0;

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, rxPin, txPin);
}

void loop() 
{
  long now = millis();
  if (now - lastMsg > 3000) 
  { 
    lastMsg = now;
    if((count%2)==0){flag="even";}
    else if((count%2)==1){flag="odd";}
    Transmit();
    count++;
  }
  Receive();
  analogWrite(ledpin, intensity);
}

void Transmit()
{
    StaticJsonDocument<50> doc;
    doc["count"] = count;
    doc["flag"] = flag;
    serializeJson(doc, Serial);
    Serial.println("");
    serializeJson(doc, Serial2);
    Serial2.println("");
}

void Receive()
{
  if (Serial2.available())
  {
    StaticJsonDocument<50> doc;
    DeserializationError err = deserializeJson(doc, Serial2);
    if (err == DeserializationError::Ok)
    {
      intensity = doc["intensity"].as<int>();
      Serial.println("intensity: "+String(intensity));
    }
  }
  else {while (Serial2.available()>0){Serial2.read();}}
}
