#include <ArduinoJson.h>
long count=0;
String flag;

void setup() 
{
  Serial.begin(115200);
}

void loop() 
{
  if((count%2)==0){flag="even";}
  else if((count%2)==1){flag="odd";}
  Transmit();
  delay(3000);
  count++;
}

void Transmit()
{
    StaticJsonDocument<70> doc;
    doc["count"] = count;
    doc["flag"] = flag;
    serializeJson(doc, Serial);
    Serial.println("");
}
