# ESP32_FirebaseRealtimeDatabase_LEDstrip

## Overview

This project demonstrates how to connect an ESP32 microcontroller to the internet, interface with the Firebase Realtime Database, and control a connected LED strip. The ESP32 reads LED control commands from the Firebase Realtime Database and updates the LED strip accordingly.

## Features

- Connect ESP32 to the internet
- Interface with Firebase Realtime Database
- Control connected LED strip remotely

## Prerequisites

- [Arduino IDE](https://www.arduino.cc/en/software) installed
- [ESP32 board](https://www.espressif.com/en/products/socs/esp32) added to Arduino IDE
- Firebase account
- LED strip
- Jumper wires
- Breadboard

## Hardware Setup

1. Connect the LED strip to the ESP32 as follows:
    - **VCC** to **3.3V** or **5V** (based on the LED strip requirements)
    - **GND** to **GND**
    - **Data Input** to **GPIO pin** (e.g., GPIO 4)

2. Connect the ESP32 to your computer using a USB cable.

## Software Setup

### Setting Up Firebase

1. Create a new project on the [Firebase Console](https://console.firebase.google.com/).
2. Create WEB Project, which generates your API Key.
3. Create Authorization -> then create at least one user.
4. Go to **Project settings** > **General** > **WEB API KEY**
   
### Installing Required Libraries

1. Open Arduino IDE.
2. Go to **Sketch** > **Include Library** > **Manage Libraries**.
3. Search for and install the following libraries:
    - `Firebase ESP32 Client`
    - `Adafruit NeoPixel`

### Uploading the Code to ESP32

1. Clone or download this repository.
2. Open `ESP32_FirebaseRealtimeDatabase_LEDstrip.ino` in Arduino IDE.
3. Update the WiFi credentials and Firebase project details in the code.
4. Select the correct ESP32 board from **Tools** > **Board**.
5. Upload the code to your ESP32.

## Usage

1. After uploading the code to your ESP32 and setting up the hardware:
    - The ESP32 will connect to the WiFi and Firebase Realtime Database.
    - The LED strip will be ready to receive commands from the Firebase database.
2. To control the LED strip:
    - Update the `LEDStatus` field in the Firebase Realtime Database with the desired value.
    - The LED strip will change its color or state based on the value.
