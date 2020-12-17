#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "FibClock.h"

RTC_DS1307 rtc;
// RTC_Millis rtc;

#define NEO_PIN 12
Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(BOX_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

time_t rtcSync() {
    DateTime now = rtc.now();
    return now.unixtime();
}

void setup() {
    strip.begin();
    Serial.begin(9600);

    FibClock::begin();

    rtc.begin();
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(F(__DATE__), F("19:56:00")));

    // Serial.println(__DATE__);
    // Serial.println(__TIME__);

    setSyncProvider(rtcSync);
    setSyncInterval(60);
    if (timeStatus() != timeSet) {
        Serial.println("Failed to Sync Time with RTC");
    }
}

void loop() {
    int hours, minutes;
    uint8_t boxes[BOX_COUNT] = {0};

    hours = hour();
    minutes = minute();

    FibClock::chooseBoxColors(hours, minutes, boxes);

    for (uint8_t i = 0; i < BOX_COUNT; i++) {
        Color c = colorMap[boxes[i]];
        strip.setPixelColor(i, c.red, c.green, c.blue);
    }
    strip.show();

    printTime();

    delay(60000);
}

void printBoxes(uint8_t const *boxes) {
    for (uint8_t i = 0; i < BOX_COUNT; i++) {
        Serial.print("(");
        Serial.print(boxes[i]);
        Serial.print(") ");
    }
    Serial.println("");
}

void printTime() {
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.println(second());
}
