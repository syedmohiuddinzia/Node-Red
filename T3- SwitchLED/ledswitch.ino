char incomingByte;
String incomingString;
#define ledpin 2 //defining the OUTPUT pin for LED

void setup() {
  Serial.begin(115200);
  pinMode(ledpin,OUTPUT);
  }

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.println(incomingByte);
    //incomingString = Serial.readString();
    //Serial.println(incomingString);
    if(incomingByte == '0'){digitalWrite(ledpin, LOW);Serial.println("low");}
    else if(incomingByte == '1'){digitalWrite(ledpin, HIGH);Serial.println("high");}
    
  }
}
