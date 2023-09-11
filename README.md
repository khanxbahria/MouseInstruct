# MouseInstruct
Mouse Instruct is an Arduino firmware that serves as a controlled USB mouse emulator. It works by receiving designated instructions from the host for mouse actions through the USB HID protocol and executing these actions acting as an actual USB HID Mouse.

The system utilizes two HID interfaces. One interface belongs to the HID Mouse class, while the other involves a Generic HID class `Raw HID` primarily functioning as an output from host to relay mouse reports via `Raw HID` to arduino and dictate mouse behaviors, like movements and button clicks.
Mouse Instruct firmware is based on `ImprovedMouse` class which provides a higher resolution of 16 bits per movement axis (unlike the `Mouse` class from Arduino library which supports only 8 bits). However the mouse scroll functionality is not supported.

## Purpose
Mouse Instruct serves a distinct purpose: **externally** mimicking a mouse device to execute mouse actions while being controlled by the host system.  This becomes important for bypassing the limitations posed by certain anticheat software that prevents the use of simulated mouse movements via the win32 API's `SendInput` events. Mouse Instruct bypasses this restriction with a controlled external mouse that operates through the existing USB HID protocol, as opposed to the more easily detectable conventional Serial UART approach.

## Build firmware
1. Copy files from `shared` to `ArduinoMouseInstruct`.
2. Install [HID-Project Library](https://www.arduino.cc/reference/en/libraries/hid-project/) in Arduino IDE.
3. (Optional) [Change `VID`/`PID`/`usb_product`/`usb_manufacturer`](https://gist.github.com/nebhead/c92da8f1a8b476f7c36c032a0ac2592a).
4. Disable CDC Serial by appending ` -DCDC_DISABLED` to relevant `build.extra_flags` in `boards.txt`.
4. Upload.

## Client Dependencies
Mouse Instruct client relies on MouseInstruct class which is reponsible for providing a simple Mouse API and forwarding the instructions to external MCU. MouseInstruct depends on [hidapi](https://github.com/libusb/hidapi) library to interface with Arduino over USB HID.

## Re-enable CDC Serial
### Leonardo/32u4-based boards
Instructions taken from: [Arduino Forum](https://forum.arduino.cc/t/serial-port-for-leonardo-has-disappeared-from-ide/932053/2)
1. Remove ` -DCDC_DISABLED` flag.
2. Start uploading the blink example.
3. When the IDE reports the memory usage, immediately press and release the reset button on the Arduino board.
### UNO/Hoodloader2
1. Remove ` -DCDC_DISABLED` flag.
2. Re-install [Hoodloader2 bootloader](https://github.com/NicoHood/HoodLoader2/wiki/Hardware-Installation).

