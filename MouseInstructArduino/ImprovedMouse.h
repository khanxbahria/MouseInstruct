/*
  ImprovedMouse.h
  Improved HID Mouse device firmware with 16 bit per movement axis
*/

#pragma once

#include <HID.h>

#include "AbstractMouse.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else


//================================================================================
//================================================================================
//  ImprovedMouse

class ImprovedMouse_ : public AbstractMouse
{
public:
  ImprovedMouse_();
  void begin();
  void end();
  uint8_t* makeReport(const int16_t& x, const int16_t& y) override;
  void sendRawReport(const uint8_t* reportData) override;
};
extern ImprovedMouse_ ImprovedMouse;

#endif
