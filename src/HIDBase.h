#ifndef HIDBASE_H
#define HIDBASE_H

#include <Arduino.h>

/**
 * @brief Enumeration for HID device types.
 */
enum class HIDDeviceType : uint8_t {
  KEYBOARD,  ///< Keyboard device
  MOUSE,     ///< Mouse device
  UNKNOWN    ///< Unknown device
};

/**
 * @brief Callback type for a successful HID device connection.
 *
 * This callback is raised when an HID device is successfully connected.
 */
typedef void (*HIDConnectionCallback)(void);

/**
 * @brief Base class for USB HID devices.
 *
 * Provides common connection callback functionality for all HID devices.
 */
class USBHIDDevice {
public:
  /**
   * @brief Construct a new USBHIDDevice object.
   */
  USBHIDDevice();

  /**
   * @brief Destroy the USBHIDDevice object.
   */
  virtual ~USBHIDDevice();

  /**
   * @brief Attach a connection callback.
   *
   * @param connectionCallback A callback function to be invoked when the device connects.
   */
  void attachConnectionCallback(HIDConnectionCallback connectionCallback);

  /**
   * @brief Internal handler for connection events.
   *
   * Called by the USB host callbacks to indicate a device connection.
   * If the connected device type is not supported, an error is printed and execution halts.
   *
   * @param deviceType The detected HID device type.
   */
  void handleConnection(HIDDeviceType deviceType);

  /**
   * @brief Check whether the device is connected.
   *
   * @return true if connected, false otherwise.
   */
  bool isConnected() const { return isDeviceConnected; }

protected:
  bool isDeviceConnected;               ///< Flag indicating if the device is connected.
  HIDConnectionCallback connectionCallback;  ///< User-provided connection callback.
};

#endif // HIDBASE_H
