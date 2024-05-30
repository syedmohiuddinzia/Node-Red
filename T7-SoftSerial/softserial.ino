#define rxPin 16
#define txPin 17
#define ledpin 2
int intensity;
long count=0;
String flag;
long lastMsg = 0;
char incomingByte;
String incomingString;

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
}

void Transmit()
{
   Serial.println(count);
   Serial.println(flag);
   Serial2.println(count);
   Serial2.println(flag);
}

void Receive()
{
  if (Serial2.available()>0)
  {
    //incomingByte = Serial.read();
    //Serial.println(incomingByte);
    incomingString = Serial2.readString();
    Serial.println(incomingString);
    intensity=incomingString.toInt();
    analogWrite(ledpin, intensity); 
  }
}
