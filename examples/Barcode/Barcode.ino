/*
 * This example shows how to use the Arduino Portenta C33 USBHIDHost library to read barcodes like the ones printed on common
 * products packaging.
 * 
 * By connecting a handheld barcode reader to the USB-A port on the mid-carrier board of your 
 * Arduino Portenta C33, you should immediately be able to read standard 13-digit bar codes on 
 * any ordinary commercial product packaging.
 * Please note that barcodes longer than 13 digits will result in "Invalid character detected, resetting..." messages being printed.
 * 
 * Instructions:
 * 1. Connect your Arduino Portenta C33 to a mid-carrier board;
 * 2. Upload this sketch to the Portenta;
 * 3. Open the Serial Monitor and chose the same baud rate as used in the sketch;
 * 4. Connect your barcode scanner to the USB-A connector on the mid-carrier board and scan away.
 */

#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

USBHIDKeyboard keyboard;

const int EAN_LENGTH = 13;
char eanBuffer[EAN_LENGTH + 1]; // +1 for null terminator
int eanIndex = 0;
bool collecting = false;

void setup() {
  Serial.begin(115200);
  keyboard.begin();
  Serial.println("Waiting for EAN-13 barcode input...");
}

void loop() {
  keyboard.poll();

  while (keyboard.available()) {
    int key = keyboard.read();

    if (key >= '0' && key <= '9') {
      if (!collecting) {
        collecting = true;
        eanIndex = 0;
      }

      if (eanIndex < EAN_LENGTH) {
        eanBuffer[eanIndex++] = (char)key;
      }

      // When we have 13 digits
      if (eanIndex == EAN_LENGTH) {
        eanBuffer[EAN_LENGTH] = '\0'; // Null-terminate the string
        Serial.print("EAN-13 Code: ");
        Serial.println(eanBuffer);
        collecting = false;
        eanIndex = 0;
      }
    }

    else if (collecting) {
      Serial.println("Invalid character detected, resetting...");
      collecting = false;
      eanIndex = 0;
    }
  }
}
