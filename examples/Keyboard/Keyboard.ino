/* This simple example shows how to read keyboard data by both listening for events and polling for available character data in the internal buffers of the USB HID Host */

#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

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
  kb.attachKeyboardEventCallback(onKeyboardEvent); // Register callback to get the keystrokes via events
  kb.begin();
}

void loop() {
  kb.poll();

  // Second way of reading back the keystrokes is via polling for available characters
  while (kb.available() > 0) {
    char c = kb.read();
    Serial.println(c);
  }
}
