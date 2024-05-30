# analogWrite

It operates with two parameters, first parameter designates the pin number where the analog signal will be generated, while the second parameter specifies the desired analog value to be output, typically ranging from 0 to 255.

The microcontroller generates a pulse-width modulation (PWM) signal with a duty cycle corresponding to the analog value provided. This entails rapidly switching the pin between HIGH and LOW states, where the ratio of time spent in the HIGH state to the total period determines the average voltage output. The duty cycle of the PWM signal is directly proportional to the analog value passed to analogWrite().

For instance, when analogWrite(pin, 127) is invoked, the PWM signal on the designated pin will have a duty cycle of approximately 50%, resulting in an average voltage output of about half the maximum voltage of the board (usually 5V or 3.3V).

__Syntax:__
analogWrite(pin, value)

# Requirements

**1. Windows, Linux OS** </br>
**2. Arduino IDE** </br>
**3. Node Red** </br>
**4. ESP32 MCU** </br>
**5. USB Type B, Micro Cable** </br>

# Working

![NodesArchitecture](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T5-LedIntensity/4.PNG) </br>

We need to convert it into objects. For this reason a JSON node is connected right after the function and the data will be converted to objects that can be further used as wanted. ESP32 Node MCU (Microcontroller Unit) processes a program in which we  switching LED connecting at output pin containing two main scenarios (HIGH defined by 0) and (LOW defined by 1) when our input is high it give data to controller and controller give the 5v to our output led and shown the message at msg.playload is **0** which means High and vice versa. These two labels are packet and transmitted after each time input is given by user and main loop runs. </br>

<!-- In Node Red application **Serial In Node** reads the data of ESP32 Node MCU. The data read is printed in **Debug Node** separately after each line but has an enter symbol binded with it, therefore first we need to remove it. For removing the enter **↵** symbol, a **Function Node** is used and below given javascript program is to be written in it. </br>
```
msg.payload = msg.payload.trim();
return msg;
```
This **Function Node** is connected right **↵** after the **Serial Node**. If **Debug Node** is connected after the function node then the each data is received separately without enter symbol. </br> -->
The output on display screen have two cases one is for **power: 0** which means LED is glowing and other is **power 1** which means led is turn off

![Data1](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T5-LedIntensity/2.PNG) </br>

Now the data received looks organized in form when input is HIGH it shows High in output screen in contineously until the second input could'nt given . </br>

![Data2](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T5-LedIntensity/3.PNG) </br>

At an end a dashboard is built by using two text display nodes. One text node will display a HIGH state button and the second text node will display a LOW state button as shown below. </br>

![Dashboard](https://github.com/syedmohiuddinzia/Node-Red/blob/main/T5-LedIntensity/2.PNG) </br>

# Instructions

**Step 1.** </br>
Open Arduino IDE, select ESP32 MCU board (Dev Module) and the right serial port from tools menu. </br>
**Step 2.** </br>
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
    intensity=incomingString.toInt();
    analogWrite(ledpin, intensity);
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
        "id": "58d163b8c6dfbfe1",
        "type": "tab",
        "label": "OddEven (Simple)",
        "disabled": false,
        "info": ""
    },
    {
        "id": "dc3769e405b793fa",
        "type": "serial out",
        "z": "58d163b8c6dfbfe1",
        "name": "ESP32 Serial Port",
        "serial": "fdf528aa7c448b35",
        "x": 390,
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
        "x": 370,
        "y": 100,
        "wires": []
    },
    {
        "id": "8be7bee48c69d77d",
        "type": "ui_slider",
        "z": "58d163b8c6dfbfe1",
        "name": "Intensity",
        "label": "Intensity",
        "tooltip": "",
        "group": "d7b74e7766b2aae6",
        "order": 0,
        "width": 0,
        "height": 0,
        "passthru": true,
        "outs": "all",
        "topic": "topic",
        "topicType": "msg",
        "min": 0,
        "max": "255",
        "step": 1,
        "className": "",
        "x": 160,
        "y": 100,
        "wires": [
            [
                "dc3769e405b793fa",
                "da8f99e112820657"
            ]
        ]
    },
    {
        "id": "4251cb74d74b2740",
        "type": "ui_text_input",
        "z": "58d163b8c6dfbfe1",
        "name": "",
        "label": "Intensity",
        "tooltip": "",
        "group": "d7b74e7766b2aae6",
        "order": 1,
        "width": 0,
        "height": 0,
        "passthru": true,
        "mode": "number",
        "delay": "0",
        "topic": "topic",
        "sendOnBlur": true,
        "className": "",
        "topicType": "msg",
        "x": 160,
        "y": 160,
        "wires": [
            [
                "dc3769e405b793fa",
                "da8f99e112820657"
            ]
        ],
        "icon": "node-red/arrow-in.svg"
    },
    {
        "id": "fdf528aa7c448b35",
        "type": "serial-port",
        "serialport": "COM4",
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

