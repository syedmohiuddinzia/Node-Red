void setup() 
{
   Serial.begin(115200);
}

long count=0;
String flag;
void loop() 
{
   if((count%2)==0){flag="even";}
   else if((count%2)==1){flag="odd";}
   Serial.println(count);
   Serial.println(flag);
   count++;
   delay(2000);
}
