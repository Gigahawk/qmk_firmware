// Copyright 2022 Gigahawk (@Gigahawk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quartet.h"

// clang-format off
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_1 }, // Row 1
    { 0, C1_2 },
    { 0, C1_3 },
    { 0, C1_4 },
    { 0, C2_1 }, // Row 2
    { 0, C2_2 },
    { 0, C2_3 },
    { 0, C2_4 },
    { 0, C3_1 }, // Row 3
    { 0, C3_2 },
    { 0, C3_3 },
    { 0, C4_1 }, // Row 4
    { 0, C4_2 },
    { 0, C4_3 },
    { 0, C4_4 },
    { 0, C5_1 }, // Row 5
    { 0, C5_2 }
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,  1,      2,      3 },
        {  4,  5,      6,      7 },
        {  8,  9,     10, NO_LED },
        { 11, 12,     13,     14 },
        { 15, 16, NO_LED, NO_LED },
    }, {
        // LED Index to Physical Position
        { 0, 0 }, { 2,  0 }, { 4,  0 }, { 6,  0 },
        { 0, 2 }, { 2,  2 }, { 4,  2 }, { 6,  3 },
        { 0, 4 }, { 2,  4 }, { 4,  4 },
        { 0, 6 }, { 2,  6 }, { 4,  6 }, { 6,  7 },
            { 1, 8 },       { 4,  8 }
    }, {
        // LED Index to Flag
        4, 4, 4, 4,
        4, 4, 4, 4,
        4, 4, 4,
        4, 4, 4, 4,
        4, 4
    }
};
// clang-format on
