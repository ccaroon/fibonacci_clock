#ifndef __EFFECTS_H__
#define __EFFECTS_H__

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

namespace Effects {
void rainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait);
uint32_t Wheel(Adafruit_NeoPixel &strip, byte WheelPos);
void blinkIfYourAlive(Adafruit_NeoPixel &strip, uint8_t pixel);
} // namespace Effects

#endif
