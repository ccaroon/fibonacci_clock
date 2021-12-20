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
const Color off = {red : 0, green : 0, blue : 0};        // black
const Color hours = {red : 128, green : 0, blue : 0};    // red
const Color minutes = {red : 0, green : 128, blue : 0};  // green
const Color both = {red : 128, green : 128, blue : 128}; // white
const Color colorMap[4] = {off, hours, minutes, both};

#define MAX_CHOICES 4
#define MAX_COMBOS 5

namespace FibClock {
void begin();
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
