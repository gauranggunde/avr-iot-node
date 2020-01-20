# Microchip AVR IoT Application

Devices: \| **ATmega4808(MCU)** \| **WINC1510(Wi-Fi®)** \| **ECC608(CryptoAuthLib)** \|

## Requirements

+ **MPLAB® X Integrated Development Environment (IDE) v5.25 or later**:
MPLAB® X IDE is a computer software program based on the open source NetBeans IDE from Oracle. It is used to develop applications for Microchip microcontrollers and digital signal controllers. It runs on Windows®, Mac OS® and Linux®.

+ **MPLAB® XC8 Compiler v2.05 or later**:
MPLAB® XC compilers support all of Microchip’s PIC, AVR and dsPIC devices where the code is written in the C programming language. XC8 is the recommended compiler for 8-bit PIC MCUs and is also supported by some AVR devices. In this lab, as well as with the succeeding labs, you will be using MPLAB® XC8 for an AVR MCU.

+ **AVR IoT Development Board**:
The AVR-IoT development board combines a powerful 8-bit ATmega4808 MCU, an ATECC608A CryptoAuthentication™ secure element IC and the fully certified ATWINC1510 Wi-Fi® network controller - which provides the most simple and effective way to connect your embedded application to a cloud platform. The board also includes an on-board debugger and requires no external hardware to program and debug the MCU.

---

## Project Platform Generation
This base repository acts as a central point for AVR IoT project development. Variations required for
cloud platforms are modified and produced using the FMPP framework, along with key token values used during project file generation.

Follow the below steps within the clone repository space:
0. **Required if 1st time executing FMPP from system EVER**: Follow the install instructions found presented within the 
[tool-environment-setup](https://bitbucket.microchip.com/projects/CITD/repos/tool-environment-setup/browse) READEME.md documentation.
   + Clone 'tool-environment-setup' repo.
   + Run prerequisites.bat/.sh. (WINDOWS | MAC)
      + Scripts should be run using Local Admin access as there will be tools installed during the process. 

1. Modify the pipeline.bat (WIN) pipeline.sh (MAC, Linux) node fmppSourceFileGenerator.js output.

``#Calls the tool to convert the templates for project operation.X and place the report in the 'output' directory ``
``node fmppSourceFileGenerator.js cf=../ sp=../AVRIoT.X/ rp=./report ``

2. Add Paremater (cf) to the ``node fmppSourceFileGenerator.js`` code.
**Enter the below to produce the desired platform's readme file during shell/bat script execution.**
   + Google: cf=../readme/google/README.md
   + Amazon: cf=../readme/amazon/README.md
   + Microsoft: cf=../readme/microsoft/README.md,../NextFile.fmpp

3. Navigate to the Cloned Directory using Command Prompt (WIN), or Terminal (MAC, Linux)

4. Execute the file:
   + pipeline.bat       (Windows)
   + sh pipleline.sh    (MAC, Linux)

5. Required FMPP resources will be fetched automatically; and the project generation will occur.

6. Once completed; the project will be ready to run or deploy.
   + The generated project will contain (2) configuration options: GOOGLE_IOT, AWS_IOT
   + Select the appropriate cloud platform configuration prior to programming.

---

## Cloud Platforms

+ Google
  1. Publish packet
     * topic:   /devices/deviceID/events
	 * payload:  {"Light":lightValue,"Temp":temperatureValue}
  2. Subscribe packet
     * topic:   /devices/deviceID/config
  
+ Amazon
  1. Publish packet
     * topic:   thingID/sensors
     * payload: {"DeviceID": "deviceID","Light": lightValue,"Temp": temperatureValue}
  2. Subscribe packet from device
     * topic:   $aws/things/thingID/shadow/update/delta
  3. UI sends publish packet to shadow 
     * topic:   $aws/things/thingID/shadow/update
     * payload: {"state": {"desired": { "DeviceID": "deviceID","toggle": toBeUpdatedToggleValue } } } 
  4. Publish packet to update device shadow/update
     * topic:   $aws/things/thingID/shadow/update
     * payload: {"state": {"reported": { "DeviceID": "deviceID","toggle": updatedToggleValue } } }
	 Note: Press SW0 to send this packet
  
+ Microsoft
  1. Publish packet
  2. Subscribe packet 

#### The AVR IoT development board publishes data from the on-board light and temperature sensor every second to the cloud.
#### The data received over the subscribed topic is displayed on a serial terminal.

## Sending MQTT publish packets  
+ The C code for sending MQTT publish packets is available in AVRIoT.X/mcc_generated_files/application_manager.c file.
+ The API ``static void sendToCloud(void)`` is responsible for publishing data at an interval of 1 second.

## Sending MQTT subscribe packets
+ The C code for sending MQTT subscribe packets is available in AVRIoT.X/mcc_generated_files/application_manager.c file.
+ The API ``static void subscribeToCloud(void)`` is responsible for sending MQTT subscribe packets to the cloud after MQTT connection is established.

## Processing Packets received over subscribed topic 
+ The C code for processing MQTT publish packets received over the subscribed topic is available in AVRIoT.X/mcc_generated_files/application_manager.c file.
+ The ``static void receivedFromCloud(uint8_t *topic, uint8_t *payload)`` function is used for processing packets published over the subscribed topic.