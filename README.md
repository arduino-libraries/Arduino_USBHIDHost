# Arduino_USBHIDHost


This library provides support for USB HID devices such as keyboards and mice on the Portenta C33. It should support any device that emulates keyboards (for example, barcode readers). The library automatically detects the insertion of a compatible device on the USB port of the chosen breakout board. You can use `attachConnectionCallback()` to get notified when a compatible device is connected.

The library has two main classes:
- **Keyboard**: Provides both event callbacks and a standard Arduino [`Stream`](https://www.arduino.cc/reference/en/language/functions/communication/stream/) implementation (e.g., using `read()` and `available()`) for reading keyboard data.
- **Mouse**: Provides event callbacks for receiving mouse information.

## Examples

- **examples/Mouse** – Demonstrates receiving mouse events via a callback.
- **examples/Keyboard** – Demonstrates receiving keyboard events via both callbacks and the Stream interface.
- **examples/MouseAndKeyboard** – Demonstrates simultaneous support for both mouse and keyboard devices.

## Usage

To use this library, simply include the appropriate header(s) in your sketch, attach any callbacks you desire, and then call the device’s `begin()` method in `setup()` and `poll()` in `loop()`. Below are some code snippets illustrating the usage.

### Keyboard

You can use the keyboard class in two ways:

1. **Event Callback:**  
   Attach a keyboard event callback that will be invoked for every key event (with the ASCII code).  
   ```cpp
   void onKeyboardEvent(uint8_t key) {
     Serial.print("Keyboard event (callback): ");
     Serial.println((char) key);
   }
   
   void setup(){
    usbKetboard.begin();
    usbKeyboard.attachKeyboardEventCallback(onKeyboardEvent);
   }

   ```

2. **Stream Interface**
The USBHIDKeyboard class also implements the Arduino Stream interface so you can use standard functions like read() and available()
```cpp
void loop() {
  usbKeyboard.poll();
  while (usbKeyboard.available() > 0) {
    char keyChar = usbKeyboard.read();
    Serial.print(keyChar);
  }
}
```

The connection callback (via attachConnectionCallback()) notifies you when a compatible keyboard is connected.

### Mouse
Reading Mouse Information
The mouse class provides a callback that returns a structure containing mouse event data. The structure is defined as follows:

```cpp
struct HIDMouseEvent {
  uint8_t buttons;       ///< Bitmask for mouse buttons (e.g., left, right, middle)
  int16_t xMovement;     ///< Relative movement in the x-direction
  int16_t yMovement;     ///< Relative movement in the y-direction
  int16_t wheelMovement; ///< Movement of the mouse wheel
};
```

Attach your mouse event callback as shown below:

```cpp
void onMouseEvent(const HIDMouseEvent &mouseEvent) {
  Serial.print("Mouse event (callback) - Buttons: ");
  Serial.print(mouseEvent.buttons);
  Serial.print(", x: ");
  Serial.print(mouseEvent.xMovement);
  Serial.print(", y: ");
  Serial.print(mouseEvent.yMovement);
  Serial.print(", wheel: ");
  Serial.println(mouseEvent.wheelMovement);
}
```

```cpp
usbMouse.attachMouseEventCallback(onMouseEvent);
```

