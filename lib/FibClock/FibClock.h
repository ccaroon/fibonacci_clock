#ifndef __FIBCLOCK_H__
#define __FIBCLOCK_H__

#include <stdint.h>

#define ONE 0
#define ONE_PRIME 1
#define TWO 2
#define THREE 3
#define FIVE 4
#define EMPTY 255

#define BOX_COUNT 5

#define COLOR_HOURS 1
#define COLOR_MINUTES 2

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} Color;

// Set your preferred colors here
const Color off = {red : 0, green : 0, blue : 0}; // black

// ----- Seasonal Color Sets ---------------------------------------------------
// Winter Colors
#define WINTER 0
// 0:off, 1:hours, 2:minutes, 3:both
const Color winterMap[4] = {
    off,
    {red : 0, green : 64, blue : 128},    // blue
    {red : 0, green : 128, blue : 64},    // cyan
    {red : 128, green : 128, blue : 128}, // white
};

// Spring Colors
#define SPRING 1
// 0:off, 1:hours, 2:minutes, 3:both
const Color springMap[4] = {
    off,
    {red : 0, green : 255, blue : 25},  // green
    {red : 255, green : 0, blue : 150}, // pink
    {red : 40, green : 0, blue : 255},  // blue
};

// Summer Colors
#define SUMMER 2
// 0:off, 1:hours, 2:minutes, 3:both
const Color summerMap[4] = {
    off,
    {red : 255, green : 255, blue : 0}, // yellow
    {red : 50, green : 50, blue : 255}, // blue
    {red : 0, green : 255, blue : 0},   // green
};

// Fall Colors
#define FALL 3
// 0:off, 1:hours, 2:minutes, 3:both
const Color fallMap[4] = {
    off,
    {red : 255, green : 0, blue : 0},   // red
    {red : 240, green : 255, blue : 0}, // yellow
    {red : 255, green : 100, blue : 0}, // orange
};
// -----------------------------------------------------------------------------

// ------ Holiday Color Sets ---------------------------------------------------
#define NEWYEAR 101
const Color newyearMap[4] = {
    {red : 255, green : 255, blue : 0},   // yellow
    {red : 0, green : 150, blue : 200},   // blue
    {red : 255, green : 255, blue : 255}, // white
    {red : 175, green : 0, blue : 255},   // purple
};

#define VALENTINES 214
const Color vdayMap[4] = {
    off,
    {red : 255, green : 0, blue : 0},     // red
    {red : 255, green : 255, blue : 255}, // white
    {red : 255, green : 64, blue : 64},   // pink
};

#define BIRTHDAY 219
const Color birthdayMap[4] = {
    {red : 0, green : 255, blue : 0},   // green
    {red : 255, green : 0, blue : 255}, // purple
    {red : 0, green : 0, blue : 255},   // blue
    {red : 255, green : 255, blue : 0}, // yellow
};

#define PICASSO_BDAY 1025
const Color picassoMap[4] = {
    {red : 255, green : 0, blue : 0},     // red
    {red : 0, green : 0, blue : 255},     // blue
    {red : 255, green : 255, blue : 0},   // yellow
    {red : 255, green : 255, blue : 255}, // white
};

#define STPATTY 317
const Color stpattyMap[4] = {
    off,
    {red : 0, green : 255, blue : 0},     // green
    {red : 255, green : 255, blue : 255}, // white
    {red : 40, green : 255, blue : 40},   // light-green
};

#define INDYPENDY 704
const Color indyMap[4] = {
    off,
    {red : 255, green : 0, blue : 0},     // red
    {red : 255, green : 255, blue : 255}, // white
    {red : 0, green : 0, blue : 255},     // blue
};

#define HALLOWEEN 1031
const Color halloweenMap[4] = {
    {red : 255, green : 255, blue : 255}, // white
    {red : 255, green : 100, blue : 0},   // orange
    {red : 255, green : 0, blue : 255},   // purple
    {red : 0, green : 255, blue : 0},     // green
};

// Not *exactly* the correct day, but close enough :)
#define THANKSGIVING 1125
const Color thanksgivingMap[4] = {
    {red : 255, green : 255, blue : 255}, // white
    {red : 255, green : 0, blue : 0},     // red
    {red : 240, green : 255, blue : 0},   // yellow
    {red : 255, green : 100, blue : 0},   // orange
};

// red, green, white, light-blue
#define CHRISTMAS 1225
const Color christmasMap[4] = {
    {red : 255, green : 255, blue : 255}, // white
    {red : 0, green : 255, blue : 0},     // green
    {red : 255, green : 0, blue : 0},     // red
    {red : 75, green : 150, blue : 255},  // light-blue
};
// -----------------------------------------------------------------------------

// Spring: 3-20  to 6-20   => 320 to 620
// Summer: 6-21  to 9-21   => 621 to 921
// Fall:   9-22  to 12-20  => 922 to 1220
// Winter: 12-21 to 3-19   => 1221 to 319
#define START_OF_SPRING 320
#define START_OF_SUMMER 621
#define START_OF_FALL 922
#define START_OF_WINTER 1221

#define MAX_CHOICES 4
#define MAX_COMBOS 5

namespace FibClock {
void begin();
const Color *colorMapBySeason(int month, int day);
void numberToFibBoxes(uint8_t number, uint8_t *boxes, uint8_t colorType);
void chooseBoxColors(uint8_t hours, uint8_t minutes, uint8_t *boxes);

const uint8_t numberMap[13][MAX_CHOICES][MAX_COMBOS] = {
    // ZERO => Placeholder, not used, makes indexing easier
    {},
    // ONE =>  1 | 1`
    {
        {ONE, EMPTY, EMPTY, EMPTY, EMPTY},
        {ONE_PRIME, EMPTY, EMPTY, EMPTY, EMPTY},
    },
    // TWO => 1,1` | 2
    {{ONE, ONE_PRIME, EMPTY, EMPTY, EMPTY}, {TWO, EMPTY, EMPTY, EMPTY, EMPTY}},
    // THREE => 1,2 | 1`,2 | 3
    {
        {ONE, TWO, EMPTY, EMPTY, EMPTY},
        {ONE_PRIME, TWO, EMPTY, EMPTY, EMPTY},
        {THREE, EMPTY, EMPTY, EMPTY, EMPTY},
    },
    // FOUR => 1,3 | 1`,3 | 1,1`,2
    {
        {ONE, THREE, EMPTY, EMPTY, EMPTY},
        {ONE_PRIME, THREE, EMPTY, EMPTY, EMPTY},
        {ONE, ONE_PRIME, TWO, EMPTY, EMPTY},
    },
    // FIVE => 1,1`,3 | 2,3 | 5
    {{ONE, ONE_PRIME, THREE, EMPTY, EMPTY},
     {TWO, THREE, EMPTY, EMPTY, EMPTY},
     {FIVE, EMPTY, EMPTY, EMPTY, EMPTY}},
    // SIX =>  1,5 | 1`,5 | 1,2,3 | 1`,2,3
    {{ONE, FIVE, EMPTY, EMPTY, EMPTY},
     {ONE_PRIME, FIVE, EMPTY, EMPTY, EMPTY},
     {ONE, TWO, THREE, EMPTY, EMPTY},
     {ONE_PRIME, TWO, THREE, EMPTY, EMPTY}},
    // SEVEN => 2,5 | 1,1`,2,3
    {{TWO, FIVE, EMPTY, EMPTY, EMPTY}, {ONE, ONE_PRIME, TWO, THREE, EMPTY}},
    // EIGHT => 3,5 | 1,2,5 | 1`,2,5
    {{THREE, FIVE, EMPTY, EMPTY, EMPTY},
     {ONE, TWO, FIVE, EMPTY, EMPTY},
     {ONE_PRIME, TWO, FIVE, EMPTY, EMPTY}},
    // NINE => 1,1`,2,5 | 1,3,5 | 1`,3,5
    {{ONE, ONE_PRIME, TWO, FIVE, EMPTY},
     {ONE, THREE, FIVE, EMPTY, EMPTY},
     {ONE_PRIME, THREE, FIVE, EMPTY, EMPTY}},
    // TEN => 2,3,5 | 1,1`,3,5
    {{TWO, THREE, FIVE, EMPTY, EMPTY}, {ONE, ONE_PRIME, THREE, FIVE, EMPTY}},
    // ELEVEN => 1,2,3,5 | 1`,2,3,5
    {{ONE, TWO, THREE, FIVE, EMPTY}, {ONE_PRIME, TWO, THREE, FIVE, EMPTY}},
    // TWELVE => 1,1`,2,3,5
    {{ONE, ONE_PRIME, TWO, THREE, FIVE}}};
}; // namespace FibClock

#endif
