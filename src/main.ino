#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "Effects.h"
#include "FibClock.h"

RTC_DS1307 rtc;

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
    // UNCOMMENT to adjust the date and time to the timestamp of this file
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

    // UNCOMMENT to adjust the date & time to a set date or time
    // rtc.adjust(DateTime(F(__DATE__), F("19:56:00")));
    // rtc.adjust(DateTime(F("Jul 20 2022"), F("18:45:15")));

    // Serial.println(__DATE__);
    // Serial.println(__TIME__);

    setSyncProvider(rtcSync);
    setSyncInterval(60);
    if (timeStatus() != timeSet) {
        Serial.println("Failed to Sync Time with RTC");
    }
}

void fibClock(uint8_t displayMins) {
    int hours, minutes, currDay, currMonth;
    uint8_t boxes[BOX_COUNT] = {0};
    const Color *colorMap;

    hours = hour();
    minutes = minute();

    currDay = day();
    currMonth = month();

    FibClock::chooseBoxColors(hours, minutes, boxes);
    Serial.println((currMonth * 100) + currDay);
    colorMap = FibClock::colorMapBySeason(currMonth, currDay);
    // Test a colorMap by Month & Day
    // colorMap = FibClock::colorMapBySeason(10, 25);

    // TEST Pattern. Show each box in differet color
    // for (uint8_t i = 0; i < BOX_COUNT; i++) {
    //     Color c = colorMap[i];
    //     strip.setPixelColor(i, c.red, c.green, c.blue);
    // }
    // -------------------------------------------------------------------------
    // Display Time Colors
    for (uint8_t i = 0; i < BOX_COUNT; i++) {
        Color c = colorMap[boxes[i]];
        strip.setPixelColor(i, c.red, c.green, c.blue);
    }
    strip.show();

    delay(60000 * displayMins);
}

void loop() {
    // int minutes = minute();

    printTime();
    fibClock(1);
    // if (minutes % 15 == 0) {
    //     fibClock(5);
    // } else {
    //     Effects::rainbowCycle(strip, 45);
    // }
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
