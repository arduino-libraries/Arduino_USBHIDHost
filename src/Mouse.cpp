#include "Mouse.h"
#include "host/usbh.h"
#include "class/hid/hid.h"
#include "class/hid/hid_host.h"
#include "class/hid/hid_device.h"
#include <stdio.h>

// Global pointer for USBHIDMouse instance (used in callbacks).
USBHIDMouse* mouseInstance = nullptr;

USBHIDMouse::USBHIDMouse()
  : mouseEventCallback(nullptr)
{
}

void USBHIDMouse::begin() {
  mouseInstance = this;
  // Initialize USB host stack if required.
}

void USBHIDMouse::poll() {
  // Process USB host tasks.
  tuh_task();
}

void USBHIDMouse::attachMouseEventCallback(MouseEventCallback mouseEventCallback) {
  this->mouseEventCallback = mouseEventCallback;
}

void USBHIDMouse::handleMouseEvent(const HIDMouseEvent &mouseEvent) {
  if (mouseEventCallback) {
    mouseEventCallback(mouseEvent);
  }
}
