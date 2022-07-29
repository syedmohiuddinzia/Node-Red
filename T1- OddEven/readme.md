# Serial Communication

In telecommunication and data transmission, serial communication is the process of sending data one bit at a time, sequentially, over a communication channel or computer bus. This is in contrast to parallel communication, where several bits are sent as a whole, on a link with several parallel channels. Serial communication is used for all long-haul communication and most computer networks, where the cost of cable and synchronization difficulties make parallel communication impractical. Serial computer buses are becoming more common even at shorter distances, as improved signal integrity and transmission speeds in newer serial technologies have begun to outweigh the parallel bus's advantage of simplicity </div>

# Requirements

**1. Windows, Linux OS** </br>
**2. Arduino IDE** </br>
**3. Node Red** </br>
**4. ESP32 MCU** </br>
**5. USB Type B, Micro Cable** </br>

# Working

ESP32 Node MCU (Microcontroller Unit) processes a program in which a count increments after each two seconds. And a value of count is modulus division by 2, if it is 1 then "odd" is saved in flag else if it is 0 then "even" is saved in flag. And then count and flag variables are printed in new lines after each time main loop runs.

In Node Red application **Serial In Node** reads the data of ESP32 Node MCU. The data read is is printed in **Debug Node** 

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. </br>
**Step 2.** </br>
Copy Arduino code given below in Arduino IDE. </br>
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
        "y": 220,
        "wires": [
            [
                "4911ad2980dc5857"
            ]
        ]
    },
    {
        "id": "3872072e6dc7b89f",
        "type": "function",
        "z": "58d163b8c6dfbfe1",
        "name": "OddEven",
        "func": "if(msg.payload===\"odd\")\n{\nmsg.data={flag:msg.payload, number}\n}\nelse if(msg.payload===\"even\")\n{\nmsg.data={flag:msg.payload, number}\n}\nelse\n{\nnumber=Number(msg.payload)\n}\nreturn msg",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 300,
        "y": 260,
        "wires": [
            [
                "d3e90b530c6fd0ed"
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
        "x": 370,
        "y": 220,
        "wires": [
            [
                "3872072e6dc7b89f"
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
        "complete": "data",
        "targetType": "msg",
        "statusVal": "",
        "statusType": "auto",
        "x": 540,
        "y": 220,
        "wires": []
    },
    {
        "id": "d3e90b530c6fd0ed",
        "type": "switch",
        "z": "58d163b8c6dfbfe1",
        "name": "",
        "property": "data",
        "propertyType": "msg",
        "rules": [
            {
                "t": "nempty"
            }
        ],
        "checkall": "true",
        "repair": false,
        "outputs": 1,
        "x": 430,
        "y": 260,
        "wires": [
            [
                "0ecb86781f8f4b49",
                "e107660e8405e834",
                "59364d1f2a06c892"
            ]
        ]
    },
    {
        "id": "e107660e8405e834",
        "type": "ui_text",
        "z": "58d163b8c6dfbfe1",
        "group": "d7b74e7766b2aae6",
        "order": 0,
        "width": 0,
        "height": 0,
        "name": "Flag",
        "label": "Flag",
        "format": "{{msg.data.flag}}",
        "layout": "row-spread",
        "className": "",
        "x": 570,
        "y": 300,
        "wires": []
    },
    {
        "id": "59364d1f2a06c892",
        "type": "ui_text",
        "z": "58d163b8c6dfbfe1",
        "group": "d7b74e7766b2aae6",
        "order": 0,
        "width": 0,
        "height": 0,
        "name": "Number",
        "label": "Number",
        "format": "{{msg.data.number}}",
        "layout": "row-spread",
        "className": "",
        "x": 580,
        "y": 260,
        "wires": []
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
