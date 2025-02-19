#include <Arduino.h>
#include "Keyboard.h"

USBHIDKeyboard kb;

void onKeyboardConnected() {
  Serial.println("Keyboard connected (callback).");
}

void onKeyboardEvent(uint8_t key) {
  Serial.print("Keyboard event (callback): ");
  Serial.println((char) key);
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  kb.attachConnectionCallback(onKeyboardConnected);
  kb.attachKeyboardEventCallback(onKeyboardEvent);
  kb.begin();
}

void loop() {
  kb.poll();

  while (kb.available() > 0) {
    char c = kb.read();
    Serial.print(c);
  }
}
