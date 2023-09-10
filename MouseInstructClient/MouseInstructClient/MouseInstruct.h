#pragma once

#include <cstdint>
#include <stdexcept>

#include <hidapi.h>
#include "AbstractMouse.h"

class MouseInstruct : public AbstractMouse
{
private:
    uint8_t _reportData[MOUSE_DATA_SIZE + 1] = { 0 }; // +1 for Report ID
    hid_device* dev;
    void sendRawReport(const uint8_t* reportData);
    uint8_t* makeReport(const int16_t& x, const int16_t& y);
    MouseInstruct(hid_device* dev);
public:
    /*
    pingCode should be greater than 7 to avoid conflicting with buttons mask
    */
    static MouseInstruct getMouse(
        const unsigned short& vid,
        const unsigned short& pid,
        const uint8_t& pingCode = (uint8_t)0xf9
    );
    ~MouseInstruct();
};

class DeviceNotFoundException : public std::runtime_error {
public:
    DeviceNotFoundException(const std::string& message)
        : std::runtime_error(message) {}
};
