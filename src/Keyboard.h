#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "HIDBase.h"
#include <Stream.h>

/**
 * @brief Callback type for keyboard events.
 *
 * This callback is invoked for every key event received, with the ASCII code of the key.
 */
typedef void (*KeyboardEventCallback)(uint8_t key);

/**
 * @brief USBHIDKeyboard class.
 *
 * Inherits from USBHIDDevice and Arduino's Stream interface. It buffers incoming
 * keystrokes so that they can be read via the stream API and also raises an event
 * callback for each key press.
 */
class USBHIDKeyboard : public USBHIDDevice, public Stream {
public:
  /**
   * @brief Construct a new USBHIDKeyboard object.
   */
  USBHIDKeyboard();

  /**
   * @brief Initialize the keyboard subsystem.
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
   * @brief Attach a keyboard event callback.
   *
   * @param keyboardEventCallback The callback function to be invoked for every key event.
   */
  void attachKeyboardEventCallback(KeyboardEventCallback keyboardEventCallback);

  /**
   * @brief Internal handler for a new key event from USB.
   *
   * Called by the USB host callback when a new key is received.
   *
   * @param key The ASCII value of the key.
   */
  void handleKey(uint8_t key);

  // --- Stream API Overrides ---

  /**
   * @brief Return the number of characters available in the buffer.
   *
   * @return int Number of available characters.
   */
  virtual int available() override;

  /**
   * @brief Read the next character from the buffer.
   *
   * @return int The next character, or -1 if none available.
   */
  virtual int read() override;

  /**
   * @brief Peek at the next character without removing it from the buffer.
   *
   * @return int The next character, or -1 if none available.
   */
  virtual int peek() override;

  /**
   * @brief Flush the internal buffer.
   */
  virtual void flush() override;

  /**
   * @brief Write is not supported.
   *
   * @param c Character to write.
   * @return size_t Always returns 0.
   */
  virtual size_t write(uint8_t c) override;

private:
  static const size_t BUFFER_SIZE = 64;   ///< Size of the internal ring buffer.
  uint8_t keyBuffer[BUFFER_SIZE];         ///< Buffer to store incoming keys.
  size_t bufferHead;                      ///< Index of the first valid data.
  size_t bufferTail;                      ///< Index where new data will be written.
  KeyboardEventCallback keyboardEventCallback; ///< User-provided keyboard event callback.

  /**
   * @brief Enqueue a key into the internal buffer.
   *
   * @param key The ASCII value of the key.
   */
  void enqueueKey(uint8_t key);
};

#endif // KEYBOARD_H
