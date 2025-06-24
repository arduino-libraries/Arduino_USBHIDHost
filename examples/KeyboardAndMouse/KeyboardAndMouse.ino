#include <Arduino.h>
#include <Arduino_USBHIDHost.h>

// Global device instances
USBHIDKeyboard kb;
USBHIDMouse ms;

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

  // Optional: Read keyboard characters from buffer
  while (kb.available() > 0) {
    char c = kb.read();
    Serial.print("Buffered keystroke: ");
    Serial.println(c);
  }

  // You can also process mouse state if needed
}
