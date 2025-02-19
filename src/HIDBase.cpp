#include "HIDBase.h"

USBHIDDevice::USBHIDDevice()
  : isDeviceConnected(false),
    connectionCallback(nullptr)
{
}

USBHIDDevice::~USBHIDDevice() { }

void USBHIDDevice::attachConnectionCallback(HIDConnectionCallback connectionCallback) {
  this->connectionCallback = connectionCallback;
}

void USBHIDDevice::handleConnection(HIDDeviceType deviceType) {
  // Only support keyboard and mouse devices.
  if (deviceType != HIDDeviceType::KEYBOARD && deviceType != HIDDeviceType::MOUSE) {
    Serial.println("Error: Connected device is not supported!");
    while (true) { } // Halt execution.
  }
  isDeviceConnected = true;
  Serial.println("HID device connected successfully.");
  if (connectionCallback) {
    connectionCallback();
  }
}
