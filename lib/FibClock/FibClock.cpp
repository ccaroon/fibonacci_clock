#include "FibClock.h"
#include "Arduino.h"

namespace FibClock {
void begin() {
    srand(analogRead(0));
}

const Color *colorMapBySeason(int month, int day) {
    const Color *colorMap;

    int seasonId = (month * 100) + day;

    if (seasonId >= START_OF_SPRING && seasonId < START_OF_SUMMER) {
        Serial.println("Spring");
        colorMap = springMap;
    } else if (seasonId >= START_OF_SUMMER && seasonId < START_OF_FALL) {
        Serial.println("Summer");
        colorMap = summerMap;
    } else if (seasonId >= START_OF_FALL && seasonId < START_OF_WINTER) {
        Serial.println("Fall");
        colorMap = fallMap;
    } else if (seasonId >= START_OF_WINTER || seasonId < START_OF_SPRING) {
        Serial.println("Winter");
        colorMap = winterMap;
    }

    return colorMap;
}

void chooseBoxColors(uint8_t hours, uint8_t minutes, uint8_t *boxes) {
    if (hours > 12) {
        hours -= 12;
    }
    minutes /= 5;

    FibClock::numberToFibBoxes(hours, boxes, COLOR_HOURS);
    FibClock::numberToFibBoxes(minutes, boxes, COLOR_MINUTES);
}

void numberToFibBoxes(uint8_t number, uint8_t *boxes, uint8_t colorType) {
    uint8_t choice = 0;

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
            if (FibClock::numberMap[number][choice][i] != EMPTY) {
                boxes[FibClock::numberMap[number][choice][i]] += colorType;
            }
        }
    }
}
}; // namespace FibClock
