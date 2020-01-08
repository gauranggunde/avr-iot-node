# Microchip AVR IoT Application

Devices: \| **ATmega4808(MCU)** \| **WINC1510(Wi-Fi®)** \| **ECC608(CryptoAuthLib)** \|

## Requirements

+ **MPLAB® X Integrated Development Environment (IDE) v5.25 or later**:
MPLAB® X IDE is a computer software program based on the open source NetBeans IDE from Oracle. It is used to develop applications for Microchip microcontrollers and digital signal controllers. It runs on Windows®, Mac OS® and Linux®.

+ **MPLAB® XC8 Compiler v2.05 or later**:
MPLAB® XC compilers support all of Microchip’s PIC, AVR and dsPIC devices where the code is written in the C programming language. XC8 is the recommended compiler for 8-bit PIC MCUs and is also supported by some AVR devices. In this lab, as well as with the succeeding labs, you will be using MPLAB® XC8 for an AVR MCU.

+ **AVR IoT Development Board**:
The AVR-IoT WG development board combines a powerful 8-bit ATmega4808 MCU, an ATECC608A CryptoAuthentication™ secure element IC and the fully certified ATWINC1510 Wi-Fi® network controller - which provides the most simple and effective way to connect your embedded application to a cloud platform. The board also includes an on-board debugger and requires no external hardware to program and debug the MCU.


## Cloud Platforms

+ Google Cloud
  1. Publish packet
     * topic:   /devices/deviceID/events
	 * payload:  {"Light":lightValue,"Temp":temperatureValue}
  2. Subscribe packet
     * topic:   /devices/deviceID/config
  
+ AWS
  1. Publish packet
     * topic:   thingID/sensors
     * payload: {"DeviceID": "deviceID","Light": lightValue,"Temp": temperatureValue}
  2. Subscribe packet from device
     * topic:   $aws/things/thingID/shadow/update/delta
  3. UI sends publish packet to shadow 
     * topic:   $aws/things/thingID/shadow/update
     * payload: {"state": {"desired": { "DeviceID": "deviceID","toggle": toBeUpdatedToggleValue } } } 
  4. Publish packet to update device shadow/update/delta
     * topic:   $aws/things/thingID/shadow/update
     * payload: {"state": {"reported": { "DeviceID": "deviceID","toggle": updatedToggleValue } } }
	 Note: Press SW0 to send this packet
  
#### The AVR IoT WG development board publishes data from the on-board light and temperature sensor every second to the cloud.
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
