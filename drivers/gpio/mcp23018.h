// Copyright 2022 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define mcp23018_PORTA 0
#define mcp23018_PORTB 1

#define ALL_OUTPUT 0
#define ALL_INPUT 0xFF
#define ALL_LOW 0
#define ALL_HIGH 0xFF

void mcp23018_init(uint8_t slave_addr);
bool mcp23018_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf);
bool mcp23018_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf);
bool mcp23018_set_output_all(uint8_t slave_addr, uint8_t confA, uint8_t confB);
bool mcp23018_readPins(uint8_t slave_addr, uint8_t port, uint8_t* ret);
bool mcp23018_readPins_all(uint8_t slave_addr, uint16_t* ret);
