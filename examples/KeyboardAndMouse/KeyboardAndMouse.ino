/* This simple example demonstrates how to read mouse and keyboard data, by connecting these devices at the same time to the Portenta, via a USB hub */

#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

/* 
 * In order to use two (or more) HID devices connected via a USB hub to your Portenta C33 board, please open "tusb_config.h" below (right click -> Go To Definition)
 * and make sure that "CFG_TUH_HUB" is set to value 1, and that "CFG_TUH_HID" is set to the number of HID devices you intend to connect to your Arduino (2 in this example). 
 * Please also keep in mind that some keyboards and mice which include advanced illumination features might draw more power than the Arduino is able to provide on its
 * USB-A port and might therefore lead to a reset or failure to be enumerated by the board. Ideally, use basic USB keyboards and mice, these should work best.
 */

#include <tusb_config.h>

// Global device instances
USBHIDKeyboard kb;
USBHIDMouse ms;

HIDMouseEvent mouseEvent;
bool eventReceived = false;

// Keyboard connection callback
void onKeyboardConnected() {
  Serial.println("Keyboard connected (callback).");
}

// Keyboard key event callback
void onKeyboardEvent(uint8_t key) {
  Serial.print("Keyboard event (callback): ");
  Serial.println((char)key);
}

// Mouse connection callback
void onMouseConnected() {
  Serial.println("Mouse connected (callback).");
}

// Mouse movement/button event callback
void onMouseEvent(const HIDMouseEvent &event) {
  eventReceived = true;
  mouseEvent = event;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Setup keyboard
  kb.attachConnectionCallback(onKeyboardConnected);
  kb.attachKeyboardEventCallback(onKeyboardEvent);
  kb.begin();

  // Setup mouse
  ms.attachConnectionCallback(onMouseConnected);
  ms.attachMouseEventCallback(onMouseEvent);
  ms.begin();

  Serial.println("Keyboard and Mouse listeners started.");
}

void loop() {
  // Poll both HID devices
  kb.poll();
  ms.poll();

  if(eventReceived){
    Serial.print("Mouse event (callback) - Buttons: ");
    Serial.print(mouseEvent.buttons);
    Serial.print(", x: ");
    Serial.print(mouseEvent.xMovement);
    Serial.print(", y: ");
    Serial.print(mouseEvent.yMovement);
    Serial.print(", wheel: ");
    Serial.println(mouseEvent.wheelMovement);
    eventReceived = false;
   }
}
