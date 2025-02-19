#include "host/usbh.h"
#include "class/hid/hid.h"
#include "class/hid/hid_host.h"
#include "class/hid/hid_device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <stdio.h>

// Mapping from HID keycodes to ASCII.
// This macro should be provided by your USB host/HID stack.
static uint8_t const keycodeToAscii[128][2] = { HID_KEYCODE_TO_ASCII };

/**
 * @brief Helper function to check if a key is present in a previous report.
 *
 * @param report Pointer to the previous keyboard report.
 * @param keycode The keycode to check.
 * @return true if the key is present, false otherwise.
 */
static inline bool isKeyInReport(const hid_keyboard_report_t* report, uint8_t keycode) {
  for (uint8_t i = 0; i < 6; i++) {
    if (report->keycode[i] == keycode)
      return true;
  }
  return false;
}

/**
 * @brief Process a keyboard report.
 *
 * Converts HID keycodes to ASCII and dispatches them to the USBHIDKeyboard instance.
 *
 * @param deviceAddress The USB device address.
 * @param report Pointer to the keyboard report.
 */
static void processKeyboardReport(uint8_t deviceAddress, const hid_keyboard_report_t* report) {
  (void) deviceAddress;
  static hid_keyboard_report_t previousReport = {0, 0, {0}};
  for (uint8_t i = 0; i < 6; i++) {
    uint8_t keycode = report->keycode[i];
    if (keycode && !isKeyInReport(&previousReport, keycode)) {
      bool isShift = report->modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT);
      uint8_t asciiChar = keycodeToAscii[keycode][isShift ? 1 : 0];
      if (asciiChar && keyboardInstance) {
        keyboardInstance->handleKey(asciiChar);
      }
    }
  }
  previousReport = *report;
}

/**
 * @brief Process a mouse report.
 *
 * Packages the report into an HIDMouseEvent structure and dispatches it to the USBHIDMouse instance.
 *
 * @param deviceAddress The USB device address.
 * @param report Pointer to the mouse report.
 */
static void processMouseReport(uint8_t deviceAddress, const hid_mouse_report_t* report) {
  HIDMouseEvent mouseEvent;
  mouseEvent.buttons = report->buttons;
  mouseEvent.xMovement = report->x;
  mouseEvent.yMovement = report->y;
  mouseEvent.wheelMovement = report->wheel;
  if (mouseInstance) {
    mouseInstance->handleMouseEvent(mouseEvent);
  }
  char tempBuffer[32];
  int count = sprintf(tempBuffer, "[%u] Buttons: %u, x: %d, y: %d, wheel: %d\r\n",
                      deviceAddress, report->buttons, report->x, report->y, report->wheel);
  Serial.write(tempBuffer, (uint32_t) count);
}

/**
 * @brief USB host callback: device mounted.
 *
 * Called when a HID device is mounted. Dispatches connection events to the appropriate instance.
 *
 * @param deviceAddress The USB device address.
 * @param interfaceInstance The HID interface instance.
 * @param descriptorReport Pointer to the report descriptor.
 * @param descriptorLength Length of the descriptor.
 */
extern "C" void tuh_hid_mount_cb(uint8_t deviceAddress, uint8_t interfaceInstance, uint8_t const* descriptorReport, uint16_t descriptorLength) {
  (void) descriptorReport;
  (void) descriptorLength;
  
  const char* protocolStr[] = { "None", "Keyboard", "Mouse" };
  uint8_t const interfaceProtocol = tuh_hid_interface_protocol(deviceAddress, interfaceInstance);
  
  uint16_t vendorId, productId;
  tuh_vid_pid_get(deviceAddress, &vendorId, &productId);
  char tempBuffer[256];

  /*
  int count = sprintf(tempBuffer, "[%04x:%04x][%u] HID Interface%u, Protocol = %s\r\n",
                        vendorId, productId, deviceAddress, interfaceInstance, protocolStr[interfaceProtocol]);
  Serial.write(tempBuffer, (uint32_t) count);
  */
  
  if (interfaceProtocol == HID_ITF_PROTOCOL_KEYBOARD || interfaceProtocol == HID_ITF_PROTOCOL_MOUSE) {
    if (interfaceProtocol == HID_ITF_PROTOCOL_KEYBOARD && keyboardInstance) {
      keyboardInstance->handleConnection(HIDDeviceType::KEYBOARD);
    } else if (interfaceProtocol == HID_ITF_PROTOCOL_MOUSE && mouseInstance) {
      mouseInstance->handleConnection(HIDDeviceType::MOUSE);
    }
    if (!tuh_hid_receive_report(deviceAddress, interfaceInstance)) {
      Serial.write("Error: cannot request report\r\n");
    }
  }
}

/**
 * @brief USB host callback: device unmounted.
 *
 * Called when a HID device is unmounted.
 *
 * @param deviceAddress The USB device address.
 * @param interfaceInstance The HID interface instance.
 */
extern "C" void tuh_hid_umount_cb(uint8_t deviceAddress, uint8_t interfaceInstance) {
  char tempBuffer[256];
  int count = sprintf(tempBuffer, "[%u] HID Interface%u is unmounted\r\n", deviceAddress, interfaceInstance);
  Serial.write(tempBuffer, (uint32_t) count);
}

/**
 * @brief USB host callback: report received.
 *
 * Called when a HID report is received. Dispatches the report based on the interface protocol.
 *
 * @param deviceAddress The USB device address.
 * @param interfaceInstance The HID interface instance.
 * @param report Pointer to the report data.
 * @param reportLength Length of the report.
 */
extern "C" void tuh_hid_report_received_cb(uint8_t deviceAddress, uint8_t interfaceInstance, uint8_t const* report, uint16_t reportLength) {
  (void) reportLength;
  uint8_t const interfaceProtocol = tuh_hid_interface_protocol(deviceAddress, interfaceInstance);
  
  switch (interfaceProtocol) {
    case HID_ITF_PROTOCOL_KEYBOARD:
      processKeyboardReport(deviceAddress, (hid_keyboard_report_t const*) report);
      break;
    case HID_ITF_PROTOCOL_MOUSE:
      processMouseReport(deviceAddress, (hid_mouse_report_t const*) report);
      break;
    default:
      break;
  }
  
  if (!tuh_hid_receive_report(deviceAddress, interfaceInstance)) {
    Serial.println("Error: cannot request report\r\n");
  }
}

/**
 * @brief Weak definition for low-level _write.
 *
 * Used by the USB host stack for writing debug messages.

extern "C" __attribute__((weak)) int _write (int fileHandle, const void *buffer, size_t count) {
  (void) fileHandle;
  static bool isInitialized = false;
  if (!isInitialized) {
    Serial1.begin(115200);
    isInitialized = true;
  }
  return Serial1.write_raw((uint8_t*)buffer, count);
}
 */