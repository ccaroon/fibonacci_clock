#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#include "main.h"

#define NEO_PIN 6
// #define NEO_COUNT 5
Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(BOX_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800);

void numberToFibBoxes(uint8_t number, uint8_t *boxes, uint8_t colorType) {
  uint8_t choice;

  // TODO: simplify this
  switch (number) {
  case 1:
    choice = rand() % 2; // Actual number of choices
    break;
  case 2:
    choice = rand() % 2; // Actual number of choices
    break;
  case 3:
    choice = rand() % 3; // Actual number of choices
    break;
  case 4:
    choice = rand() % 3; // Actual number of choices
    break;
  case 5:
    choice = rand() % 3; // Actual number of choices
    break;
  case 6:
    choice = rand() % 4; // Actual number of choices
    break;
  case 7:
    choice = rand() % 2; // Actual number of choices
    break;
  case 8:
    choice = rand() % 3; // Actual number of choices
    break;
  case 9:
    choice = rand() % 3; // Actual number of choices
    break;
  case 10:
    choice = rand() % 2; // Actual number of choices
    break;
  case 11:
    choice = rand() % 2; // Actual number of choices
    break;
  case 12:
    choice = 0; // Actual number of choices
    break;
  }

  if (number > 0) {
    for (uint8_t i = 0; i < MAX_COMBOS; i++) {
      if (fibMap[number][choice][i] != EMPTY) {
        boxes[fibMap[number][choice][i]] += colorType;
      }
    }
  }
}

void setup() {
  strip.begin();
  Serial.begin(9600);
  srand(analogRead(0));

  setTime(7, 7, 7, 19, 2, 1977);
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
  numberToFibBoxes(hours, boxes, COLOR_HOURS);
  numberToFibBoxes(minutes, boxes, COLOR_MINUTES);

  printTime();
  printBoxes(boxes);

  for (uint8_t i = 0; i < BOX_COUNT; i++) {
    Color c = colorMap[boxes[i]];
    uint32_t color = strip.Color(c.red, c.green, c.blue);
    strip.setPixelColor(i, color);
  }

  strip.show();

  delay(60000);
  // delay(999);
}
