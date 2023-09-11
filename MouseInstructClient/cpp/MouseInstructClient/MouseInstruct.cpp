#include "MouseInstruct.h"

#include <iostream>
#include <string>

using namespace std;

#define LOW_BYTE(x) ((uint8_t)(x & 0xFF))
#define HIGH_BYTE(x) ((uint8_t)((x >> 8) & 0xFF))

bool checkPing(hid_device* dev, const uint8_t& pingCode) {
    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] = pingCode;
    hid_write(dev, buf, 2);
    size_t bytesRead = hid_read_timeout(dev, buf, sizeof(pingCode), 10);
    return bytesRead > 0 && buf[0] == pingCode;
}

hid_device* findMouseDevice(
    const unsigned short& vid,
    const unsigned short& pid,
    const int8_t& pingCode
) {
    hid_device_info* enumeration = hid_enumerate(vid, pid);
    hid_device_info* possibleMouseInfo = enumeration;
    hid_device* dev = nullptr;
    bool found = false;
    while (possibleMouseInfo != nullptr) {
        dev = hid_open_path(possibleMouseInfo->path);
        found = checkPing(dev, pingCode);
        if (found)
            break;
        hid_close(dev);
        possibleMouseInfo = possibleMouseInfo->next;
    }
    hid_free_enumeration(enumeration);
    return found ? dev : nullptr;
}

MouseInstruct MouseInstruct::getMouse(
    const unsigned short& vid,
    const unsigned short& pid,
    const uint8_t& pingCode
) {
    hid_init();
    hid_device* dev = findMouseDevice(vid, pid, pingCode);
    if (dev == nullptr) {
        throw DeviceNotFoundException(
            "[-] Device VendorID: " + std::to_string(vid) +
            ", " + " ProductID: " + std::to_string(pid) + " not found!"
        );
    }
    return MouseInstruct(dev);
}

MouseInstruct::MouseInstruct(hid_device* dev) : dev(dev) {}

MouseInstruct::~MouseInstruct() {
    hid_close(dev);
    hid_exit();
}

uint8_t* MouseInstruct::makeReport(const int16_t& x, const int16_t& y) {
    _reportData[0] = 0x00; // Report ID: 0
    _reportData[1] = _buttons;
    _reportData[2] = LOW_BYTE(x);
    _reportData[3] = HIGH_BYTE(x);
    _reportData[4] = LOW_BYTE(y);
    _reportData[5] = HIGH_BYTE(y);
    return _reportData;
}

void MouseInstruct::sendRawReport(const uint8_t* reportData) {
    hid_write(dev, reportData, MOUSE_DATA_SIZE + 1);
}