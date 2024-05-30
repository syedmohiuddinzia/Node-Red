char incomingByte;
String incomingString;
#define ledpin 2 //defining the OUTPUT pin for LED
int intensity=0; 

void setup() {
  Serial.begin(115200);
  pinMode(ledpin,OUTPUT);
  }

void loop() {
  if (Serial.available() > 0) {
    //incomingByte = Serial.read();
    //Serial.println(incomingByte);
    incomingString = Serial.readString();
    Serial.println(incomingString);
    intensity=incomingString.toInt();
    analogWrite(ledpin, intensity);
  }
}
