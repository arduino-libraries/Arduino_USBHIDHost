#include <Arduino.h>
#include "Keyboard.h"

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
