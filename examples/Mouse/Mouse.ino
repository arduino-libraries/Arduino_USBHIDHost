#include <Arduino.h>
#include "Mouse.h"

// Create a global mouse instance.
USBHIDMouse ms;

// User-defined connection callback.
void onMouseConnected() {
  Serial.println("Mouse connected (callback).");
}

// User-defined mouse event callback.
void onMouseEvent(const HIDMouseEvent &event) {
  Serial.print("Mouse event (callback) - Buttons: ");
  Serial.print(event.buttons);
  Serial.print(", x: ");
  Serial.print(event.xMovement);
  Serial.print(", y: ");
  Serial.print(event.yMovement);
  Serial.print(", wheel: ");
  Serial.println(event.wheelMovement);
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
  // Additional mouse processing if needed.
}
