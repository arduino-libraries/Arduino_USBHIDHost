/*
 * This simple example shows how to read mouse data, like cursor position and key states, by registering a callback and listening for events
 * 
 * Instructions:
 * 1. Connect your Arduino Portenta C33 to a mid-carrier board;
 * 2. Upload this sketch to the Portenta;
 * 3. Open the Serial Monitor and chose the same baud rate as used in the sketch;
 * 4. Connect your mouse to the USB-A connector and any movement or keypress should be printed as data to the console.
 * Please not that scroll wheel data works inconsistently and might not function correctly with your mouse.
 */

#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

// Create a global mouse instance.
USBHIDMouse ms;

HIDMouseEvent mouseEvent;
bool eventReceived = false;

// User-defined connection callback.
void onMouseConnected() {
  Serial.println("Mouse connected (callback).");
}

// User-defined mouse event callback.
void onMouseEvent(const HIDMouseEvent &event) {
  eventReceived = true;
  mouseEvent = event;
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  ms.attachConnectionCallback(onMouseConnected);
  ms.attachMouseEventCallback(onMouseEvent);
  ms.begin();
}

void loop() {
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
  // Additional mouse processing if needed.
}
