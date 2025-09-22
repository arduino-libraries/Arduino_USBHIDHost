/*
 * This simple example shows how to read keyboard data by both listening for events and polling for available character data in the internal buffers of the USB HID Host.
 * There are two general ways user input can be detected, either by constantly checking for the state of a buffer (or pin, for example), which we refer to as the "polling" method, or
 * by having some event fire as soon as the user input (key press in this case) is detected, which, in turn, calls a function we registered previously with the lower layers.
 * The below example demonstrates both these methods of capturing user input.
 * 
 * Instructions:
 * 1. Connect your Arduino Portenta C33 to a mid-carrier board;
 * 2. Upload this sketch to the Portenta;
 * 3. Open the Serial Monitor and chose 115200 as baud rate;

 * 4. Connect your keyboard to the USB-A connector and any keypress should be printed to the console window.
 */

#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

USBHIDKeyboard kb;

void onKeyboardConnected() {
  Serial.println("Keyboard connected (callback).");
}

// This function will now be called every time a key is pressed by the user, as a single event
void onKeyboardEvent(uint8_t key) {
  Serial.print("Key pressed (event callback): ");
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
  kb.poll(); // This function will continuously check if a key has been pressed, this is generally referred to as "polling"

  // If keystrokes were registered, we enter a second loop and print out the entire buffer
  while (kb.available() > 0) {
    char c = kb.read();
    Serial.print("Key pressed (polling detection): ");
    Serial.println(c);
  }
}
