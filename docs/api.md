# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`class ` [`USBHIDDevice`](#class_u_s_b_h_i_d_device) | Base class for USB HID devices.
`class ` [`USBHIDKeyboard`](#class_u_s_b_h_i_d_keyboard) | [USBHIDKeyboard](#class_u_s_b_h_i_d_keyboard) class.
`class ` [`USBHIDMouse`](#class_u_s_b_h_i_d_mouse) | [USBHIDMouse](#class_u_s_b_h_i_d_mouse) class.
`struct ` [`HIDMouseEvent`](#struct_h_i_d_mouse_event) | Structure representing a mouse event.

# class `USBHIDDevice` <a id="class_u_s_b_h_i_d_device" class="anchor"></a>

Base class for USB HID devices.

Provides common connection callback functionality for all HID devices.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`USBHIDDevice`](#class_u_s_b_h_i_d_device_1a99831d39786cc0186e8c780c202f46da) | Construct a new [USBHIDDevice](#class_u_s_b_h_i_d_device) object. |
| [`~USBHIDDevice`](#class_u_s_b_h_i_d_device_1a87b5400ec3747933d6c33204b7c9c7a2) | Destroy the [USBHIDDevice](#class_u_s_b_h_i_d_device) object. |
| [`attachConnectionCallback`](#class_u_s_b_h_i_d_device_1a1a2c5b59829d743132ddc9435b70856d) | Attach a connection callback. |
| [`handleConnection`](#class_u_s_b_h_i_d_device_1aea3e06465b67c0f523413d3a14ab5800) | Internal handler for connection events. |
| [`isConnected`](#class_u_s_b_h_i_d_device_1a8e8cfdadc4556bdf301eea065d8c3262) | Check whether the device is connected. |

## Members

### `USBHIDDevice` <a id="class_u_s_b_h_i_d_device_1a99831d39786cc0186e8c780c202f46da" class="anchor"></a>

```cpp
USBHIDDevice()
```

Construct a new [USBHIDDevice](#class_u_s_b_h_i_d_device) object.

<hr />

### `~USBHIDDevice` <a id="class_u_s_b_h_i_d_device_1a87b5400ec3747933d6c33204b7c9c7a2" class="anchor"></a>

```cpp
virtual ~USBHIDDevice()
```

Destroy the [USBHIDDevice](#class_u_s_b_h_i_d_device) object.

<hr />

### `attachConnectionCallback` <a id="class_u_s_b_h_i_d_device_1a1a2c5b59829d743132ddc9435b70856d" class="anchor"></a>

```cpp
void attachConnectionCallback(HIDConnectionCallback connectionCallback)
```

Attach a connection callback.

#### Parameters
* `connectionCallback` A callback function to be invoked when the device connects.
<hr />

### `handleConnection` <a id="class_u_s_b_h_i_d_device_1aea3e06465b67c0f523413d3a14ab5800" class="anchor"></a>

```cpp
void handleConnection(HIDDeviceType deviceType)
```

Internal handler for connection events.

Called by the USB host callbacks to indicate a device connection. If the connected device type is not supported, an error is printed and execution halts.

#### Parameters
* `deviceType` The detected HID device type.
<hr />

### `isConnected` <a id="class_u_s_b_h_i_d_device_1a8e8cfdadc4556bdf301eea065d8c3262" class="anchor"></a>

```cpp
inline bool isConnected() const
```

Check whether the device is connected.

#### Returns
true if connected, false otherwise.
<hr />

# class `USBHIDKeyboard` <a id="class_u_s_b_h_i_d_keyboard" class="anchor"></a>

```cpp
class USBHIDKeyboard
  : public USBHIDDevice
  : public Stream
```

[USBHIDKeyboard](#class_u_s_b_h_i_d_keyboard) class.

Inherits from [USBHIDDevice](#class_u_s_b_h_i_d_device) and Arduino's Stream interface. It buffers incoming keystrokes so that they can be read via the stream API and also raises an event callback for each key press.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`USBHIDKeyboard`](#class_u_s_b_h_i_d_keyboard_1a71b6c823bd4b3943efd3561ddf50a1cc) | Construct a new [USBHIDKeyboard](#class_u_s_b_h_i_d_keyboard) object. |
| [`begin`](#class_u_s_b_h_i_d_keyboard_1a6e8c1d8bb99e32b158f3ccca4f4876ae) | Initialize the keyboard subsystem. |
| [`poll`](#class_u_s_b_h_i_d_keyboard_1a7e5675d35163eaf611e3d4f560c935f5) | Poll for USB events. |
| [`attachKeyboardEventCallback`](#class_u_s_b_h_i_d_keyboard_1ae5f780d5b42191dc6fbb2804bfc4d8ed) | Attach a keyboard event callback. |
| [`handleKey`](#class_u_s_b_h_i_d_keyboard_1a302c35210ccb0d0c853f26ef3713360e) | Internal handler for a new key event from USB. |
| [`available`](#class_u_s_b_h_i_d_keyboard_1a2dd03cc0280dde2973b2d1a9132460f7) | Return the number of characters available in the buffer. |
| [`read`](#class_u_s_b_h_i_d_keyboard_1a8f037af0b1d434b3d95d72d03106a4e8) | Read the next character from the buffer. |
| [`peek`](#class_u_s_b_h_i_d_keyboard_1a112c43dc0d4762b166d5f0c91b7dfca0) | Peek at the next character without removing it from the buffer. |
| [`flush`](#class_u_s_b_h_i_d_keyboard_1ace1e9fdf6459cf7f05595c3579c65792) | Flush the internal buffer. |
| [`write`](#class_u_s_b_h_i_d_keyboard_1a9ecf8198b596c0f5fc1ef4ca28272e79) | Write is not supported. |

## Members

### `USBHIDKeyboard` <a id="class_u_s_b_h_i_d_keyboard_1a71b6c823bd4b3943efd3561ddf50a1cc" class="anchor"></a>

```cpp
USBHIDKeyboard()
```

Construct a new [USBHIDKeyboard](#class_u_s_b_h_i_d_keyboard) object.

<hr />

### `begin` <a id="class_u_s_b_h_i_d_keyboard_1a6e8c1d8bb99e32b158f3ccca4f4876ae" class="anchor"></a>

```cpp
void begin()
```

Initialize the keyboard subsystem.

Should be called in setup().
<hr />

### `poll` <a id="class_u_s_b_h_i_d_keyboard_1a7e5675d35163eaf611e3d4f560c935f5" class="anchor"></a>

```cpp
void poll()
```

Poll for USB events.

Should be called repeatedly in loop().
<hr />

### `attachKeyboardEventCallback` <a id="class_u_s_b_h_i_d_keyboard_1ae5f780d5b42191dc6fbb2804bfc4d8ed" class="anchor"></a>

```cpp
void attachKeyboardEventCallback(KeyboardEventCallback keyboardEventCallback)
```

Attach a keyboard event callback.

#### Parameters
* `keyboardEventCallback` The callback function to be invoked for every key event.
<hr />

### `handleKey` <a id="class_u_s_b_h_i_d_keyboard_1a302c35210ccb0d0c853f26ef3713360e" class="anchor"></a>

```cpp
void handleKey(uint8_t key)
```

Internal handler for a new key event from USB.

Called by the USB host callback when a new key is received.

#### Parameters
* `key` The ASCII value of the key.
<hr />

### `available` <a id="class_u_s_b_h_i_d_keyboard_1a2dd03cc0280dde2973b2d1a9132460f7" class="anchor"></a>

```cpp
virtual int available()
```

Return the number of characters available in the buffer.

#### Returns
int Number of available characters.
<hr />

### `read` <a id="class_u_s_b_h_i_d_keyboard_1a8f037af0b1d434b3d95d72d03106a4e8" class="anchor"></a>

```cpp
virtual int read()
```

Read the next character from the buffer.

#### Returns
int The next character, or -1 if none available.
<hr />

### `peek` <a id="class_u_s_b_h_i_d_keyboard_1a112c43dc0d4762b166d5f0c91b7dfca0" class="anchor"></a>

```cpp
virtual int peek()
```

Peek at the next character without removing it from the buffer.

#### Returns
int The next character, or -1 if none available.
<hr />

### `flush` <a id="class_u_s_b_h_i_d_keyboard_1ace1e9fdf6459cf7f05595c3579c65792" class="anchor"></a>

```cpp
virtual void flush()
```

Flush the internal buffer.

<hr />

### `write` <a id="class_u_s_b_h_i_d_keyboard_1a9ecf8198b596c0f5fc1ef4ca28272e79" class="anchor"></a>

```cpp
virtual size_t write(uint8_t c)
```

Write is not supported.

#### Parameters
* `c` Character to write. 

#### Returns
size_t Always returns 0.
<hr />

# class `USBHIDMouse` <a id="class_u_s_b_h_i_d_mouse" class="anchor"></a>

```cpp
class USBHIDMouse
  : public USBHIDDevice
```

[USBHIDMouse](#class_u_s_b_h_i_d_mouse) class.

Inherits from [USBHIDDevice](#class_u_s_b_h_i_d_device). Converts incoming mouse reports into [HIDMouseEvent](#struct_h_i_d_mouse_event) structures and dispatches them via a user-defined callback.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`USBHIDMouse`](#class_u_s_b_h_i_d_mouse_1a24f491506148b7c334e7ff7acc8df1ce) | Construct a new [USBHIDMouse](#class_u_s_b_h_i_d_mouse) object. |
| [`begin`](#class_u_s_b_h_i_d_mouse_1af4f5212531f4334450a8afa30499f773) | Initialize the mouse subsystem. |
| [`poll`](#class_u_s_b_h_i_d_mouse_1a6896edf4fc8de719180218dbd71e1e55) | Poll for USB events. |
| [`attachMouseEventCallback`](#class_u_s_b_h_i_d_mouse_1acb41fb77e1ff5bafce0a90742b99b93e) | Attach a mouse event callback. |
| [`handleMouseEvent`](#class_u_s_b_h_i_d_mouse_1a11cbb10b2a32bf5c6f1fad73297e364d) | Internal handler for a new mouse event. |

## Members

### `USBHIDMouse` <a id="class_u_s_b_h_i_d_mouse_1a24f491506148b7c334e7ff7acc8df1ce" class="anchor"></a>

```cpp
USBHIDMouse()
```

Construct a new [USBHIDMouse](#class_u_s_b_h_i_d_mouse) object.

<hr />

### `begin` <a id="class_u_s_b_h_i_d_mouse_1af4f5212531f4334450a8afa30499f773" class="anchor"></a>

```cpp
void begin()
```

Initialize the mouse subsystem.

Should be called in setup().
<hr />

### `poll` <a id="class_u_s_b_h_i_d_mouse_1a6896edf4fc8de719180218dbd71e1e55" class="anchor"></a>

```cpp
void poll()
```

Poll for USB events.

Should be called repeatedly in loop().
<hr />

### `attachMouseEventCallback` <a id="class_u_s_b_h_i_d_mouse_1acb41fb77e1ff5bafce0a90742b99b93e" class="anchor"></a>

```cpp
void attachMouseEventCallback(MouseEventCallback mouseEventCallback)
```

Attach a mouse event callback.

#### Parameters
* `mouseEventCallback` The callback function to be invoked for each mouse event.
<hr />

### `handleMouseEvent` <a id="class_u_s_b_h_i_d_mouse_1a11cbb10b2a32bf5c6f1fad73297e364d" class="anchor"></a>

```cpp
void handleMouseEvent(const HIDMouseEvent & mouseEvent)
```

Internal handler for a new mouse event.

Called by the USB host callback when a new mouse report is received.

#### Parameters
* `mouseEvent` The mouse event data.
<hr />

# struct `HIDMouseEvent` <a id="struct_h_i_d_mouse_event" class="anchor"></a>

Structure representing a mouse event.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
| [`buttons`](#struct_h_i_d_mouse_event_1af3129f12ed81c6efa68005235545db60) | Bitmask for mouse buttons (e.g., left, right, middle) |
| [`xMovement`](#struct_h_i_d_mouse_event_1aa7143890ec68eefd60a5bd55e848f816) | Relative x movement. |
| [`yMovement`](#struct_h_i_d_mouse_event_1a12bb38dcdd4bfdd0306cef7cf599ddd2) | Relative y movement. |
| [`wheelMovement`](#struct_h_i_d_mouse_event_1af0734a85ac9f0089780ace5b9cc5d86e) | Wheel movement. |

## Members

### `buttons` <a id="struct_h_i_d_mouse_event_1af3129f12ed81c6efa68005235545db60" class="anchor"></a>

```cpp
uint8_t buttons
```

Bitmask for mouse buttons (e.g., left, right, middle)

<hr />

### `xMovement` <a id="struct_h_i_d_mouse_event_1aa7143890ec68eefd60a5bd55e848f816" class="anchor"></a>

```cpp
int16_t xMovement
```

Relative x movement.

<hr />

### `yMovement` <a id="struct_h_i_d_mouse_event_1a12bb38dcdd4bfdd0306cef7cf599ddd2" class="anchor"></a>

```cpp
int16_t yMovement
```

Relative y movement.

<hr />

### `wheelMovement` <a id="struct_h_i_d_mouse_event_1af0734a85ac9f0089780ace5b9cc5d86e" class="anchor"></a>

```cpp
int16_t wheelMovement
```

Wheel movement.

<hr />

