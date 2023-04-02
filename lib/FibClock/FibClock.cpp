#include "FibClock.h"
#include "Arduino.h"

namespace FibClock {
void begin() {
    srand(analogRead(0));
}

const Color *colorMapBySeason(int month, int day) {
    const Color *colorMap;

    int dateCode = (month * 100) + day;

    // Pick Color for Season
    if (dateCode >= START_OF_SPRING && dateCode < START_OF_SUMMER) {
        Serial.println("Season: Spring");
        colorMap = springMap;
    } else if (dateCode >= START_OF_SUMMER && dateCode < START_OF_FALL) {
        Serial.println("Season: Summer");
        colorMap = summerMap;
    } else if (dateCode >= START_OF_FALL && dateCode < START_OF_WINTER) {
        Serial.println("Season: Fall");
        colorMap = fallMap;
    } else if (dateCode >= START_OF_WINTER || dateCode < START_OF_SPRING) {
        Serial.println("Season: Winter");
        colorMap = winterMap;
    }

    // Override colorMap if it's a specific holiday
    switch (dateCode) {
    case NEWYEAR:
        Serial.println("Holiday: New Year");
        colorMap = newyearMap;
        break;
    case VALENTINES:
        Serial.println("Holiday: St. Valentines");
        colorMap = vdayMap;
        break;
    case BIRTHDAY:
        Serial.println("Holiday: Birthday");
        colorMap = birthdayMap;
        break;
    case PICASSO_BDAY:
        Serial.println("Holiday: Picasso's Birthday");
        colorMap = picassoMap;
        break;
    case STPATTY:
        Serial.println("Holiday: St. Patrick's");
        colorMap = stpattyMap;
        break;
    case INDYPENDY:
        Serial.println("Holiday: Independence Day");
        colorMap = indyMap;
        break;
    case HALLOWEEN:
        Serial.println("Holiday: Halloween");
        colorMap = halloweenMap;
        break;
    case THANKSGIVING:
        Serial.println("Holiday: Thanksgiving");
        colorMap = thanksgivingMap;
        break;
    case CHRISTMAS:
        Serial.println("Holiday: Christmas");
        colorMap = christmasMap;
        break;
    default:
        break;
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
