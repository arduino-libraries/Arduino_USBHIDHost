#include "Keyboard.h"
#include "host/usbh.h"
#include "class/hid/hid.h"
#include "class/hid/hid_host.h"
#include "class/hid/hid_device.h"
#include <stdio.h>

// Mapping from HID keycodes to ASCII. (Defined by your USB host stack.)
static uint8_t const keycodeToAscii[128][2] = { HID_KEYCODE_TO_ASCII };

// Global pointer for USBHIDKeyboard instance (used in callbacks).
USBHIDKeyboard* keyboardInstance = nullptr;

USBHIDKeyboard::USBHIDKeyboard()
  : bufferHead(0),
    bufferTail(0),
    keyboardEventCallback(nullptr)
{
}

void USBHIDKeyboard::begin() {
  keyboardInstance = this;
  // Initialize USB host stack if needed (e.g., tuh_init(0);)
}

void USBHIDKeyboard::poll() {
  // Process USB host tasks.
  tuh_task();
}

void USBHIDKeyboard::attachKeyboardEventCallback(KeyboardEventCallback keyboardEventCallback) {
  this->keyboardEventCallback = keyboardEventCallback;
}

int USBHIDKeyboard::available() {
  if (bufferTail >= bufferHead) {
    return bufferTail - bufferHead;
  } else {
    return BUFFER_SIZE - bufferHead + bufferTail;
  }
}

int USBHIDKeyboard::read() {
  if (available() == 0) return -1;
  uint8_t key = keyBuffer[bufferHead];
  bufferHead = (bufferHead + 1) % BUFFER_SIZE;
  return key;
}

int USBHIDKeyboard::peek() {
  if (available() == 0) return -1;
  return keyBuffer[bufferHead];
}

void USBHIDKeyboard::flush() {
  bufferHead = 0;
  bufferTail = 0;
}

size_t USBHIDKeyboard::write(uint8_t c) {
  (void)c; // Not supported.
  return 0;
}

void USBHIDKeyboard::enqueueKey(uint8_t key) {
  size_t nextTail = (bufferTail + 1) % BUFFER_SIZE;
  // Only enqueue if there is available space.
  if (nextTail != bufferHead) {
    keyBuffer[bufferTail] = key;
    bufferTail = nextTail;
  }
  // Otherwise, key is dropped.
}

void USBHIDKeyboard::handleKey(uint8_t key) {
  if (keyboardEventCallback) {
    keyboardEventCallback(key);
  }
  enqueueKey(key);
}
