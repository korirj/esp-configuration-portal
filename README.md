# esp-configuration-portal
A web based UI built using ESPUI for configuring sensor parameters.


## Table of Contents
* [General Info](#general-information)
* [Technologies Used](#technologies-used)
* [Features](#features)
* [Screenshots](#screenshots)
* [Setup](#setup)
* [Usage](#usage)
* [Project Status](#project-status)
* [Room for Improvement](#room-for-improvement)
* [Acknowledgements](#acknowledgements)
* [Contact](#contact)
<!-- * [License](#license) -->


## General Information
Have you ever gone through trouble when configuring sensor details whwnever you change a network or location of a device built in arduino using Low cost ESP32 or ESP8266 controllers? This project is used to make a configuration portal to make dynamic  entries such as 
- wifi networks
- sensor Id
- APIs 

This project demonstrates how to Configure an mq2 gas sensor with a nodemcu(esp8266 based controller), whenever a sensor reading above the threshold is recorded, The controller sends a notification to whatsapp using the <a href= "https://www.callmebot.com">Callmebot</a>

<!-- You don't have to answer all the questions - just the ones relevant to your project. -->


## Technologies Used

Hardware Equipment used include
- ESP8266 development board - Wemos D1 R1
- mq2 sensor 
- breadboard
- jumper wires
- usb cable - to upload code

Software libraries used include:
- <a href="https://github.com/s00500/ESPUI">ESPUI </a>- version 2.2.1
- <a href="https://github.com/s00500/ESPUI">Arduino JSON </a>- version 6.19.3
- <a href="https://github.com/me-no-dev/ESPAsyncTCP">ESPAsyncTCP </a>- version 2.2.1
- <a href="https://github.com/esphome/ESPAsyncWebServer">ESPAsyncWebServer</a> - version 3.0.0
- <a href= "https://github.com/knolleary/pubsubclient">PubSubClient </a> - version 2.8.0
-
Other platforms used include
- <a href= "https://www.callmebot.com">CallMeBot api</a>
- <a href= "http://www.hivemq.com/demos/websocket-client/">Hive MQTT Broker </a>


## Features
List the ready features here:
- Whatsapp messenger notification
- Scan for available wifi networks
- wifi password configuration
- mqtt connection to connect to external applications
- Use EEPROM to store sensor configuration
- No wifi is required to configure the board

## Screenshots
![Example screenshot](./img/screenshot.png)
<!-- If you have screenshots you'd like to share, include them here. -->


## Setup
As earlier stated above, the project relies on the libraries listed above.
The easiest way to get started is using the arduino IDE. 
You can find these Libraries  in the Arduino IDE library manager.
 open your arduino IDE and Go to 
 `Sketch > Include Library > Library Manager`
 search for `ESPUI` and install. ( Arduino prompts you to install additional libraries. click yes, install additional libraries

If you cannot use the Library Manager, you can download the repositories and follow the [instructions](https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/how-to-install-a-library) to manually install libraries.

In the arduino setup() routine the interface can be customised by adding UI Elements. For our case we shall use :
- 2 instances of a button, one for restart and the other for submiting the configuration
- 3 textboxes:
 - one for password ( automatically replaced with `*` 
 - the second for SensorId  which is used as MQTT Topic 
 - third for callmebot api key 
 - the last for your phone number to receive whatsapp message 
- 1 dropdown menu to display all available Wifi Networks
each of the above elements in the interface calls a  Callback function when changed. 
To separate different events, event name is passed to the callback function that can be handled in a switch(){}case{} statement. 

Remember, whenever yoa add an element that needs to be persistent, make sure to include its handler callback , modify the struct that holds the configurationand thets all.

## Usage
* Connect the circuit as shown inthe figure below
* Connect Your NodeMCU to the Computer- Use the USB cable to connect your NodeMCU to the computer
*  Install the COM/Serial Port Driver - z For CP2102 you can download and install the driver [here](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers): The NodeMCUv0.9 comes with the CH340 serial chip that can be downloaded [here](https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers) 
*  Install the Arduino IDE 1.6.4 or Greater -Download Arduino IDE from Arduino.cc 
*  Install the ESP8266 Board Package on arduino  Open ` Arduino IDE–>File–>Perferences–>Settings).`
*  Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json`into Additional Board Manager then click OK.
*  use the Board Manager to install the ESP8266 package Enter the `Arduino IDE–>Tools–>Boards –> Boards Manager` and type `Esp8266` on the search bar. A module called “esp8266 by esp8266 Community” will show , select the latest version and click “Install“. The ESP8266 package has benn installed successfully.
*  restart Arduino IDE.
*  Setup ESP8266 Support - Select your board from `Tools->Board` dropdown Config the Board menu 
*  Choose the right Port for your device. 
*  Now just proceed as the Arduino: Start your sketching!



## Project Status
Project is: _in progress_ . For any changes please [contact me ](https://japhethkorir.netlify.app/contact)

## Room for Improvement
set threshold values
- implement a slider to handle threshold values

Access the UI over your network Over IP:
- Make the UI persistent even afterb connected to wiri


Connect to Home assistant and openhab:
- Implement webhooks for Hassio
- Implement webhooks for Openhab


## Acknowledgements
Give credit here.
- Many thanks to [E](https://arduinodiy.wordpress.com/2021/07/14/sending-messages-through-signal/) for the tutorial on how to use the whatsapp API


## Contact
Created by [@korir](https://japhethkorir.netlify.app/) - feel free to contact me!

## Licence
 licensed with GNU General Public License Version 3.0 (which means, if you use it in a product somewhere, you need to make the source and all your modifications available to the receiver of such product so that they have the freedom to adapt and improve).
