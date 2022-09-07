# digitalWrite()
It have mainly 2 parameters. first parameter contain the pin no of output and second parameter contains the state of selected pin (either **HIGH** or **LOW**)

If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the corresponding value: 5V (or 3.3V on 3.3V boards) for HIGH, 0V (ground) for LOW.

If the pin is configured as an INPUT, digitalWrite() will enable (HIGH) or disable (LOW) the internal pullup on the input pin. It is recommended to set the pinMode() to INPUT_PULLUP to enable the internal pull-up resistor. See the Digital Pins tutorial for more information.

***Syntax:*** </br>
 digitalWrite(pin, value)

***Parameters:*** </br>
pin: the Arduino pin number.</br>
value: HIGH or LOW.



# Requirements

**1. Windows, Linux OS** </br>
**2. Arduino IDE** </br>
**3. Node Red** </br>
**4. ESP32 MCU** </br>
**5. USB Type B, Micro Cable** </br>

# Working

![NodesArchitecture](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T3-%20SwitchLED/2.PNG?raw=true) 

ESP32 Node MCU (Microcontroller Unit) processes a program in which we  switching LED connecting at output pin containing two main scenarios (HIGH defined by 0) and (LOW defined by 1) when our input is high it give data to controller and controller give the 5v to our output led and shown the message at msg.playload is **0** which means High and vice versa </br>

<!-- In Node Red application **Serial In Node** reads the data of ESP32 Node MCU. The data read is printed in **Debug Node** separately after each line but has an enter symbol binded with it, therefore first we need to remove it. For removing the enter **↵** symbol, a **Function Node** is used and below given javascript program is to be written in it. </br>
```
msg.payload = msg.payload.trim();
return msg;
```
This **Function Node** is connected right **↵** after the **Serial Node**. If **Debug Node** is connected after the function node then the each data is received separately without enter symbol. Now the data received is not saved in a variable therefore we need to save it in two different variables. The flag variable will either have "odd" or "even" and number variable will have a number. For this purpose another **Function Node** is connected at the end of first **Function Node**. It changes msg.payload to msg.data={flag:"xxxx", number:xxxx}.
```
if(msg.payload==="odd")
{
msg.data={flag:msg.payload, number}
}
else if(msg.payload==="even")
{
msg.data={flag:msg.payload, number}
}
else
{
number=Number(msg.payload)
}
return msg
``` --> 

At an end a dashboard is built by using two text display nodes. One text node will display a **HIGH in GREEN** and the second text node will display a **LOW in RED** as shown below. </br>

![Dashboard](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T3-%20SwitchLED/1.PNG?raw=true)

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. </br>
ModuleModule**Step 2.** </br>
Copy Arduino code given below in Arduino IDE. </br>

```
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
    intensity=int(incomingString);
    digitalWrite(ledpin, intensity);
  }
}

```
**Step 3.** </br>
Upload the arduino code in ESP32 MCU. </br>
**Step 4.** </br>
Open Node-Red application by writing 'node-red' on cmd in windows or terminal on linux os. </br>
**Step 5.** </br>
Copy JSON code given below and import in Node-Red application. </br>
```
[
    {
        "id": "47207cf76d12b981",
        "type": "ui_button",
        "z": "58d163b8c6dfbfe1",
        "name": "High",
        "group": "d7b74e7766b2aae6",
        "order": 0,
        "width": 0,
        "height": 0,
        "passthru": false,
        "label": "High",
        "tooltip": "",
        "color": "white",
        "bgcolor": "green",
        "className": "",
        "icon": "",
        "payload": "1",
        "payloadType": "num",
        "topic": "power",
        "topicType": "msg",
        "x": 170,
        "y": 100,
        "wires": [
            [
                "dc3769e405b793fa",
                "da8f99e112820657"
            ]
        ]
    },
    {
        "id": "45266e61451c2a6a",
        "type": "ui_button",
        "z": "58d163b8c6dfbfe1",
        "name": "Low",
        "group": "d7b74e7766b2aae6",
        "order": 0,
        "width": 0,
        "height": 0,
        "passthru": false,
        "label": "Low",
        "tooltip": "",
        "color": "white",
        "bgcolor": "red",
        "className": "",
        "icon": "",
        "payload": "0",
        "payloadType": "num",
        "topic": "power",
        "topicType": "msg",
        "x": 170,
        "y": 140,
        "wires": [
            [
                "dc3769e405b793fa",
                "da8f99e112820657"
            ]
        ]
    },
    {
        "id": "dc3769e405b793fa",
        "type": "serial out",
        "z": "58d163b8c6dfbfe1",
        "name": "ESP32 Serial Port",
        "serial": "fdf528aa7c448b35",
        "x": 370,
        "y": 140,
        "wires": []
    },
    {
        "id": "da8f99e112820657",
        "type": "debug",
        "z": "58d163b8c6dfbfe1",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "false",
        "statusVal": "",
        "statusType": "auto",
        "x": 350,
        "y": 100,
        "wires": []
    },
    {
        "id": "d7b74e7766b2aae6",
        "type": "ui_group",
        "name": "ESP32 BuiltIn LED",
        "tab": "08d00e0951b9a3d3",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "fdf528aa7c448b35",
        "type": "serial-port",
        "serialport": "COM3",
        "serialbaud": "115200",
        "databits": "8",
        "parity": "none",
        "stopbits": "1",
        "waitfor": "",
        "dtr": "none",
        "rts": "none",
        "cts": "none",
        "dsr": "none",
        "newline": "\\n",
        "bin": "bin",
        "out": "char",
        "addchar": "",
        "responsetimeout": "10000"
    },
    {
        "id": "08d00e0951b9a3d3",
        "type": "ui_tab",
        "name": "Switch LED",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    }
]
```
**Step 6.** </br>
Deploy the Node-Red.
