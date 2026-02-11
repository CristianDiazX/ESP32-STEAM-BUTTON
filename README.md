# ESP32 Steam Button Project

## Overview
This project involves using the ESP32 microcontroller to create a steam button that can be used for various applications, such as a remote control for your PC gaming. This README will guide you through connecting the hardware, setting up the development environment, and uploading the code to the ESP32.

## Hardware Requirements
- **ESP32 Development Board**
- **Push Button** (Normally Open)
- **220 Ohm Resistor**
- **Breadboard and Jumper Wires**
- **USB Cable**
- **Computer (Windows, macOS, or Linux)**

## Connecting the Hardware
1. **Connect the Push Button**
   - Connect one terminal of the push button to a digital pin on the ESP32 (e.g., GPIO 23).
   - Connect the other terminal to the ground (GND).
   - Use a pull-down resistor (220 Ohm) connected between the digital pin and ground to ensure a stable state.

2. **Power the ESP32**
   - Connect the ESP32 to your computer using the USB cable. Make sure the correct drivers are installed if required.

## Setting Up the Development Environment
1. **Install the Arduino IDE** (if you haven't already)
   - Download the Arduino IDE from [the official website](https://www.arduino.cc/en/software).

2. **Install the ESP32 Board in Arduino IDE**
   - Open the Arduino IDE.
   - Go to `File` -> `Preferences`.
   - In the "Additional Board Manager URLs" field, enter:
     `https://dl.espressif.com/dl/package_esp32_index.json`
   - Go to `Tools` -> `Board` -> `Board Manager`, search for `ESP32`, and install "esp32 by Espressif Systems".

3. **Select the ESP32 Board**
   - Go to `Tools` -> `Board` and select your ESP32 board model (e.g., ESP32 Dev Module).
   - Select the correct COM port by going to `Tools` -> `Port`.

## Uploading the Code to the ESP32
1. **Open the Code Example**
   - You can use the sample code provided below or write your own logic.

   ```cpp
   #include <Arduino.h>
   
   const int buttonPin = 23;  // Pin where the button is connected
   
   void setup() {
       pinMode(buttonPin, INPUT);
       Serial.begin(115200);
   }
   
   void loop() {
       if (digitalRead(buttonPin) == HIGH) {
           Serial.println("Button Pressed!");
           delay(1000);  // Delay to avoid multiple triggers
       }
   }
   ```

2. **Upload the Code**
   - Click on the upload button (right arrow) in Arduino IDE to compile and upload the code to the ESP32.
   - Open the Serial Monitor (Tools -> Serial Monitor) to see the output from your ESP32.

## Conclusion
You have now successfully set up a steam button using the ESP32. Customize the code as needed for your own applications!