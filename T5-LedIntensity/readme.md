# JSON (JavaScript object notation syntax) </br>

+ JSON stands for JavaScript Object Notation
+ JSON is a lightweight format for storing and transporting data
+ JSON is often used when data is sent from a server to a web page
+ JSON is "self-describing" and easy to understand

# Requirements

**1. Windows, Linux OS** </br>
**2. Arduino IDE** </br>
**3. Node Red** </br>
**4. ESP32 MCU** </br>
**5. USB Type B, Micro Cable** </br>

# Working

![NodesArchitecture](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T4-%20SwitchLEDJSON/4.PNG) </br>

We need to convert it into objects. For this reason a JSON node is connected right after the function and the data will be converted to objects that can be further used as wanted. ESP32 Node MCU (Microcontroller Unit) processes a program in which we  switching LED connecting at output pin containing two main scenarios (HIGH defined by 0) and (LOW defined by 1) when our input is high it give data to controller and controller give the 5v to our output led and shown the message at msg.playload is **0** which means High and vice versa. These two labels are packet and transmitted after each time input is given by user and main loop runs. </br>

<!-- In Node Red application **Serial In Node** reads the data of ESP32 Node MCU. The data read is printed in **Debug Node** separately after each line but has an enter symbol binded with it, therefore first we need to remove it. For removing the enter **↵** symbol, a **Function Node** is used and below given javascript program is to be written in it. </br>
```
msg.payload = msg.payload.trim();
return msg;
```
This **Function Node** is connected right **↵** after the **Serial Node**. If **Debug Node** is connected after the function node then the each data is received separately without enter symbol. </br> -->
The output on display screen have two cases one is for **power: 0** which means LED is glowing and other is **power 1** which means led is turn off

![Data1](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T4-%20SwitchLEDJSON/2.PNG) </br>

Now the data received looks organized in form when input is HIGH it shows High in output screen in contineously until the second input could'nt given . </br>

![Data2](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T4-%20SwitchLEDJSON/3.PNG) </br>

At an end a dashboard is built by using two text display nodes. One text node will display a HIGH state button and the second text node will display a LOW state button as shown below. </br>

![Dashboard](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T4-%20SwitchLEDJSON/1.PNG) </br>

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. </br>
**Step 2.** </br>
Copy Arduino code given below in Arduino IDE. </br>
```
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
        "payload": "{\"power\":0}",
        "payloadType": "json",
        "topic": "power",
        "topicType": "msg",
        "x": 190,
        "y": 140,
        "wires": [
            [
                "dc3769e405b793fa",
                "da8f99e112820657"
            ]
        ]
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

