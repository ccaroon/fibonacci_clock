#include <Adafruit_NeoPixel.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <Wire.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "FibClock.h"

// RTC_DS1307 rtc;
RTC_Millis rtc;

#define NEO_PIN 12
// #define NEO_COUNT 5
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
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  setSyncProvider(rtcSync);
  setSyncInterval(60);
  if (timeStatus() != timeSet) {
    Serial.println("Failed to Sync Time with RTC");
  }

  // srand(analogRead(0));

  // initTime();
}

// void initTime() {
//   int hour, min, sec, month = 1, day = 1, year = 2016;
//   sscanf(__TIME__, "%02d:%02d:%02d\n", &hour, &min, &sec);
//   setTime(hour, min, sec, day, month, year);
// }

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

void loop() {
  int hours, minutes;
  uint8_t boxes[BOX_COUNT] = {0};

  hours = hour();
  if (hours > 12) {
    hours -= 12;
  }
  minutes = minute();
  minutes /= 5;

  // memset(boxes, 0, BOX_COUNT * sizeof(uint8_t));
  FibClock::numberToFibBoxes(hours, boxes, COLOR_HOURS);
  FibClock::numberToFibBoxes(minutes, boxes, COLOR_MINUTES);

  // printTime();
  // printBoxes(boxes);

  // for (uint8_t i = 0; i < BOX_COUNT; i++) {
  //   Color c = colorMap[boxes[i]];
  //   uint32_t color = strip.Color(c.red, c.green, c.blue);
  //   strip.setPixelColor(i, color);
  // }

  strip.show();

  delay(60000);
  // delay(999);
}
