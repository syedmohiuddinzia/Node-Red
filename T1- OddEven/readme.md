# Serial Communication

In telecommunication and data transmission, serial communication is the process of sending data one bit at a time, sequentially, over a communication channel or computer bus. This is in contrast to parallel communication, where several bits are sent as a whole, on a link with several parallel channels. Serial communication is used for all long-haul communication and most computer networks, where the cost of cable and synchronization difficulties make parallel communication impractical. Serial computer buses are becoming more common even at shorter distances, as improved signal integrity and transmission speeds in newer serial technologies have begun to outweigh the parallel bus's advantage of simplicit </div>

# Requirements

**1. Windows OS** </br>
**2. Arduino IDE** </br>
**3. Node Red** </br>
**4. ESP32 MCU** </br>
**5. USB Type B, Micro Cable** </br>

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. 
**Step 2.** </br>
Copy Arduino code given below in Arduino IDE.
```
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
**Step 3.** </br>
Upload the arduino code in ESP32 MCU.
**Step 4.** </br>
Open Node-Red application by writing 'node-red' on cmd in windows or terminal on linux os.
**Step 5.** </br>
![ProteusSimulationBluetoothInstruction5](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/5.png)</br>
**Step 6.** </br>
![ProteusSimulationBluetoothInstruction6](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/6.png)</br>
**Step 7.** </br>
![ProteusSimulationBluetoothInstruction7](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/7.png)</br>
**Step 8.** </br>
![ProteusSimulationBluetoothInstruction8](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/8.png)</br>
**Step 9.** </br>
![ProteusSimulationBluetoothInstruction9](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/9.png)</br>
**Step 10.** </br>
![ProteusSimulationBluetoothInstruction10](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/10.png)</br>
**Step 11.** </br>
![ProteusSimulationBluetoothInstruction11](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/11.png)</br>
**Step 12.** </br>
![ProteusSimulationBluetoothInstruction12](https://github.com/syedmohiuddinzia/ProteusSimulationBluetooth/blob/main/BluetoothConnectionInstructions/12.png)</br>
