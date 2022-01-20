/*
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
#include "mcp23018.h"
#include "quantum.h"
#include "wait.h"
#include "debug.h"
#include "config.h"

// Optimize scanning code for speed as a slight mitigation for the port expander
#pragma GCC push_options
#pragma GCC optimize("-O3")

#define I2C_ADDR 0x20

// MCP23017 is compatible with MCP23018
static uint16_t mcp23017_reset_loop = 0;
static uint8_t  mcp23017_errors     = 0;

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

//_____REGULAR funcs____________________________________________________________

static void select_row(uint8_t row) {
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row) { setPinInputHigh(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        unselect_row(x);
    }
}

static void init_pins(void) { unselect_rows(); }

//_____MCP23018 funcs___________________________________________________________

static void init_pins_MCP23017(void) {
    mcp23018_init(I2C_ADDR);
    // Set all pins to input with pullup
    mcp23017_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTA, 0xFF);
    mcp23017_errors += !mcp23018_set_config(I2C_ADDR, mcp23018_PORTB, 0xFF);
}

static uint8_t read_cols_MCP23017(void) {
    uint8_t state = 0xFF;
    mcp23017_errors += !mcp23018_readPins(I2C_ADDR, mcp23018_PORTA, &state);
    return (~state) & 0b1111;
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Select row and wait for row selection to stabilize
    select_row(current_row);
    wait_us(5);

    matrix_row_t current_row_value = read_cols_MCP23017();

    // Unselect row
    unselect_row(current_row);
    wait_us(5);

    if (last_row_value == current_row_value) {
        return false;
    }

    current_matrix[current_row] = current_row_value;
    return true;
}

//_____CUSTOM MATRIX IMPLEMENTATION____________________________________________________

void matrix_init_custom(void) {
    init_pins();
    init_pins_MCP23017();
    print("matrix_init_custom done\n");
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    if (mcp23017_errors) {
        if (++mcp23017_reset_loop > 0x7FFF) {
            // tuned to about 5s given the current scan rate
            print("trying to reset mcp23017\n");
            mcp23017_reset_loop = 0;
            mcp23017_errors     = 0;
            init_pins_MCP23017();
        }
        return changed;
    }

    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(current_matrix, current_row);
    }

    return changed;
}
#pragma GCC pop_options
