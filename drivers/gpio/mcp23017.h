/* Copyright 2022 Jasper Chan (Gigahawk)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Ensures the MCP23017 is set up for use with this driver.
 * Run this once per chip/address */
void mcp23017_init(uint8_t slave_addr);

/* Set the IO direction of a port */
void mcp23017_set_config(uint8_t slave_addr, uint8_t port, uint8_t conf);

/* Set the value of pins configured as output on a port */
void mcp23017_set_output(uint8_t slave_addr, uint8_t port, uint8_t conf);

/* Read the value of pins from a port */
uint8_t mcp23017_read_pins(uint8_t slave_addr, uint8_t port);

/* Read the value of all pins from both ports */
uint16_t mcp23017_read_all_pins(uint8_t slave_addr);

// Port definitions
#define MCP23017_PORTA 0
#define MCP23017_PORTB 1

// Register addresses (IOCON.BANK = 0)
#define MCP23017_IODIRA 0x00
#define MCP23017_IODIRB 0x01
#define MCP23017_IPOLA 0x02
#define MCP23017_IPOLB 0x03
#define MCP23017_GPINTENA 0x04
#define MCP23017_GPINTENB 0x05
#define MCP23017_DEFVALA 0x06
#define MCP23017_DEFVALB 0x07
#define MCP23017_INTCONA 0x08
#define MCP23017_INTCONB 0x09
#define MCP23017_IOCON 0x0A
// #define MCP23017_IOCON 0x0B  // IOCON is shared between ports
#define MCP23017_GPPUA 0x0C
#define MCP23017_GPPUB 0x0D
#define MCP23017_INTFA 0x0E
#define MCP23017_INTFB 0x0F
#define MCP23017_INTCAPA 0x10
#define MCP23017_INTCAPB 0x11
#define MCP23017_GPIOA 0x12
#define MCP23017_GPIOB 0x13
#define MCP23017_OLATA 0x14
#define MCP23017_OLATB 0x15

// Register addresses (IOCON.BANK = 1)
#define MCP23017_BANK1_IOCON 0x05
