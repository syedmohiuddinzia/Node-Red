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

![NodesArchitecture](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T2-%20OddEvenJSON/2.PNG =250x) </br>

ESP32 Node MCU (Microcontroller Unit) processes a program in which a count increments after each two seconds. And a value of count is modulus division by 2, if it is 1 then "odd" is saved in flag else if it is 0 then "even" is saved in flag. A function of JSON transmit is created that contains labels for **count** and **flag**. These two labels are packet and transmitted after each time main loop runs. </br>

In Node Red application **Serial In Node** reads the data of ESP32 Node MCU. The data read is printed in **Debug Node** separately after each line but has an enter symbol binded with it, therefore first we need to remove it. For removing the enter **↵** symbol, a **Function Node** is used and below given javascript program is to be written in it. </br>
```
msg.payload = msg.payload.trim();
return msg;
```
This **Function Node** is connected right **↵** after the **Serial Node**. If **Debug Node** is connected after the function node then the each data is received separately without enter symbol. </br>

![Data1](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T2-%20OddEvenJSON/3.PNG) </br>

Now the data received looks organized but is in a string form therefore we need is to convert it into objects. For this reason a JSON node is connected right after the function and the data will be converted to objects that can be further used as wanted. </br>

![Data2](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T2-%20OddEvenJSON/4.PNG) </br>

At an end a dashboard is built by using two text display nodes. One text node will display a Number and the second text node will display a Flag as shown below. </br>

![Dashboard](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T2-%20OddEvenJSON/1.PNG) </br>

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. </br>
**Step 2.** </br>
Copy Arduino code given below in Arduino IDE. </br>
```
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
        "id": "eb5ad423c8fbc05f",
        "type": "serial in",
        "z": "58d163b8c6dfbfe1",
        "name": "ESP32 Serial Port",
        "serial": "fdf528aa7c448b35",
        "x": 210,
        "y": 80,
        "wires": [
            [
                "4911ad2980dc5857"
            ]
        ]
    },
    {
        "id": "4911ad2980dc5857",
        "type": "function",
        "z": "58d163b8c6dfbfe1",
        "name": "Trim",
        "func": "msg.payload = msg.payload.trim();\nreturn msg;",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 210,
        "y": 40,
        "wires": [
            [
                "b0bcd2f20b38e2bc"
            ]
        ]
    },
    {
        "id": "0ecb86781f8f4b49",
        "type": "debug",
        "z": "58d163b8c6dfbfe1",
        "name": "",
        "active": true,
        "tosidebar": true,
        "console": false,
        "tostatus": false,
        "complete": "payload",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 430,
        "y": 120,
        "wires": []
    },
    {
        "id": "e107660e8405e834",
        "type": "ui_text",
        "z": "58d163b8c6dfbfe1",
        "group": "d7b74e7766b2aae6",
        "order": 2,
        "width": 0,
        "height": 0,
        "name": "Flag",
        "label": "Flag",
        "format": "{{msg.payload.flag}}",
        "layout": "row-spread",
        "className": "",
        "x": 470,
        "y": 80,
        "wires": []
    },
    {
        "id": "59364d1f2a06c892",
        "type": "ui_text",
        "z": "58d163b8c6dfbfe1",
        "group": "d7b74e7766b2aae6",
        "order": 1,
        "width": 0,
        "height": 0,
        "name": "Number",
        "label": "Number",
        "format": "{{msg.payload.count}}",
        "layout": "row-spread",
        "className": "",
        "x": 460,
        "y": 40,
        "wires": []
    },
    {
        "id": "b0bcd2f20b38e2bc",
        "type": "json",
        "z": "58d163b8c6dfbfe1",
        "name": "",
        "property": "payload",
        "action": "",
        "pretty": false,
        "x": 330,
        "y": 40,
        "wires": [
            [
                "59364d1f2a06c892",
                "e107660e8405e834",
                "0ecb86781f8f4b49"
            ]
        ]
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
        "bin": "false",
        "out": "char",
        "addchar": "",
        "responsetimeout": "10000"
    },
    {
        "id": "d7b74e7766b2aae6",
        "type": "ui_group",
        "name": "Odd or Even",
        "tab": "f56dcd513927ea2d",
        "order": 1,
        "disp": true,
        "width": "6",
        "collapse": false,
        "className": ""
    },
    {
        "id": "f56dcd513927ea2d",
        "type": "ui_tab",
        "name": "Odd or Even",
        "icon": "dashboard",
        "disabled": false,
        "hidden": false
    }
]
```
**Step 6.** </br>
Deploy the Node-Red.
