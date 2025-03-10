#include <Arduino.h>
#include "Mouse.h"

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
