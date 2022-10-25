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

## Screenshots
![Example screenshot](./img/screenshot.png)
<!-- If you have screenshots you'd like to share, include them here. -->


## Setup
You can find this Library in the Arduino IDE library manager. Go to `Sketch > Include Library > Library Manager` search for `ESPUI` and install.

If you cannot use the Library Manager, you can download the repository and follow the [instructions](https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use/how-to-install-a-library) to manually install libraries.



What are the project requirements/dependencies? Where are they listed? A requirements.txt or a Pipfile.lock file perhaps? Where is it located?

Proceed to describe how to install / setup one's local environment / get started with the project.


## Usage
How does one go about using it?
Provide various use cases and code examples here.

`write-your-code-here`


## Project Status
Project is: _in progress_ / _complete_ / _no longer being worked on_. If you are no longer working on it, provide reasons why.


## Room for Improvement
Include areas you believe need improvement / could be improved. Also add TODOs for future development.

Room for improvement:
- Improvement to be done 1
- Improvement to be done 2

To do:
- Feature to be added 1
- Feature to be added 2


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
