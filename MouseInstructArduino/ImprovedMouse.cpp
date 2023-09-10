/*
  ImprovedMouse.cpp
  16 bit mouse without scroll wheel
*/

#include "ImprovedMouse.h"

#if defined(_USING_HID)

/*
  [+] Increased report size to 16 bits per movement axis
  [-] Removed scroll wheel support
*/
static const uint8_t _hidReportDescriptor[] PROGMEM = {
  
  //  Mouse
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 54
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x85, 0x01,                    //     REPORT_ID (1)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x03,                    //     INPUT (Cnst,Var,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x16, 0x01, 0x80,              //     LOGICAL_MINIMUM (-32767)
    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //   END_COLLECTION
    0xc0,                          // END_COLLECTION
};

#define LOW_BYTE(x) ((uint8_t)(x & 0xFF))
#define HIGH_BYTE(x) ((uint8_t)((x >> 8) & 0xFF))

//================================================================================
//================================================================================
//  Mouse



ImprovedMouse_::ImprovedMouse_()
{
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void ImprovedMouse_::begin() 
{
}

void ImprovedMouse_::end() 
{
}

uint8_t* ImprovedMouse_::makeReport(const int16_t& x, const int16_t& y)
{
  uint8_t reportData[MOUSE_DATA_SIZE];
  reportData[0] = _buttons;
  reportData[1] = LOW_BYTE(x);
  reportData[2] = HIGH_BYTE(x);
  reportData[3] = LOW_BYTE(y);
  reportData[4] = HIGH_BYTE(y);
  return reportData;
}

void ImprovedMouse_::sendRawReport(const uint8_t* reportData)
{
  _buttons = reportData[0];
  HID().SendReport(1,reportData,MOUSE_DATA_SIZE);
}

ImprovedMouse_ ImprovedMouse;

#endif
