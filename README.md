# Arduino_USBHIDHost

[![Check Arduino](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/check-arduino.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/check-arduino.yml) [![Compile Examples](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/compile-examples.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/compile-examples.yml) [![Spell Check](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/spell-check.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/spell-check.yml) [![Sync Labels](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/sync-labels.yml/badge.svg)](https://github.com/bcmi-labs/Arduino_USBHIDHost/actions/workflows/sync-labels.yml)


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

### Temp. Development instructions 
Before all the changes get merged into the core, you will have to do some modifications to get this library to compile.

1. Enable TinyUSB HID Host support 

In the core by modify [variants/PORTENTA_C33/tusb_config.h](https://github.com/arduino/ArduinoCore-renesas/blob/main/variants/PORTENTA_C33/tusb_config.h).
On line 106, add `#define CFG_TUH_HID              1`. 
Check [this PR](https://github.com/arduino/ArduinoCore-renesas/compare/main...cristidragomir97:ArduinoCore-renesas:hid_host_c33) for more information.

2. Enable weak callback for `tuh_hid_report_received_cb`
When enabling CFG_TUH_HID in tusb_config.h, the stack will expect a tuh_hid_report_received_cb callback to be defined in every sketch, preventing any sketch that doesn't have anything to do with the HID Host stack from compiling. The hid_host.h file defines weak callbacks in order to prevent this issue, but the TU_ATTR_WEAK is prefixed to most callbacks except fortuh_hid_report_received_cb. These changes add this attribute, allowing any sketch to compile.

Check [this PR](https://github.com/arduino/tinyusb/pull/3/commits/e3e9dd066cd64d98de6bd19d2920fec3019b71c4) for more information.