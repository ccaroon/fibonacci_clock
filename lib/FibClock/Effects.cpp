#include "Effects.h"

namespace Effects {
void rainbowCycle(Adafruit_NeoPixel &strip, uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) {
        // ***
        // *** 5 cycles of all colors on wheel
        // ***
        for (i = 0; i < strip.numPixels(); i++) {
            strip.setPixelColor(
                i, Wheel(strip, ((i * 256 / strip.numPixels()) + j) & 255));
        }

        strip.show();
        delay(wait);
    }
}

void blinkIfYourAlive(Adafruit_NeoPixel &strip, uint8_t pixel) {
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    delay(1000);

    strip.setPixelColor(0, 0, 255, 0);
    strip.show();
    delay(1000);
}

uint32_t Wheel(Adafruit_NeoPixel &strip, byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }

    if (WheelPos < 170) {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }

    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

} // namespace Effects
