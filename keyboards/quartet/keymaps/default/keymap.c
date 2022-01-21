// Copyright 2022 Gigahawk (@Gigahawk)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names { _BASE, _FN };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        OUT_USB, OUT_BT, KC_C, KC_D,
        KC_E,    KC_F,   KC_G, KC_H,
        KC_I,    KC_J,   KC_K,
        KC_L,    KC_M,   KC_N, KC_O,
             KC_P,       KC_Q, KC_R
    ),
    [_FN]   = LAYOUT(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______,
        _______, _______, _______, _______,
            _______,      _______, _______
    )
};
// clang-format on

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}

bool led_update_user(led_t led_state) {
    sethsv(0, 100, 2, (LED_TYPE *)&led[0]);
    rgblight_set();
    return true;
}

void led_matrix_indicators_user(void) { led_matrix_set_value_all(255); }

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("OLED"), false);

    return false;
}
#endif
