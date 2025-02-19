#ifndef MOUSE_H
#define MOUSE_H

#include "HIDBase.h"

/**
 * @brief Structure representing a mouse event.
 */
struct HIDMouseEvent {
  uint8_t buttons;  ///< Bitmask for mouse buttons (e.g., left, right, middle)
  int16_t xMovement; ///< Relative x movement
  int16_t yMovement; ///< Relative y movement
  int16_t wheelMovement; ///< Wheel movement
};

/**
 * @brief Callback type for mouse events.
 *
 * The callback is invoked with a reference to an HIDMouseEvent structure.
 */
typedef void (*MouseEventCallback)(const HIDMouseEvent &mouseEvent);

/**
 * @brief USBHIDMouse class.
 *
 * Inherits from USBHIDDevice. Converts incoming mouse reports into HIDMouseEvent
 * structures and dispatches them via a user-defined callback.
 */
class USBHIDMouse : public USBHIDDevice {
public:
  /**
   * @brief Construct a new USBHIDMouse object.
   */
  USBHIDMouse();

  /**
   * @brief Initialize the mouse subsystem.
   *
   * Should be called in setup().
   */
  void begin();

  /**
   * @brief Poll for USB events.
   *
   * Should be called repeatedly in loop().
   */
  void poll();

  /**
   * @brief Attach a mouse event callback.
   *
   * @param mouseEventCallback The callback function to be invoked for each mouse event.
   */
  void attachMouseEventCallback(MouseEventCallback mouseEventCallback);

  /**
   * @brief Internal handler for a new mouse event.
   *
   * Called by the USB host callback when a new mouse report is received.
   *
   * @param mouseEvent The mouse event data.
   */
  void handleMouseEvent(const HIDMouseEvent &mouseEvent);

private:
  MouseEventCallback mouseEventCallback; ///< User-provided callback for mouse events.
};

#endif // MOUSE_H
