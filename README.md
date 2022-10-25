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






## Usage













In the arduino setup() routine the interface can be customised by adding UI Elements. This is done by calling the corresponding library methods on the Library object ESPUI. Eg: ESPUI.button("button", &myCallback); creates a button in the interface that calls the myCallback(Control *sender, int eventname) function when changed. All buttons and items call their callback whenever there is a state change from them. This means the button will call the callback when it is pressed and also again when it is released. To separate different events, an integer number with the event name is passed to the callback function that can be handled in a switch(){}case{} statement. 
How does one go about using it?
Provide various use cases and code examples here.

`write-your-code-here`


## Project Status
Project is: _in progress_ . For any changes please contact me at <mail>jephekipa@gmail.com.</mail>


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
- This project was inspired by...
- This project was based on [this tutorial](https://www.example.com).
- Many thanks to...


## Contact
Created by [@flynerdpl](https://www.flynerd.pl/) - feel free to contact me!


<!-- Optional -->
<!-- ## License -->
<!-- This project is open source and available under the [... License](). -->

<!-- You don't have to include all sections - just the one's relevant to your project -->
