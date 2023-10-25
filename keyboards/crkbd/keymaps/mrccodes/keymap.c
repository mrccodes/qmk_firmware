/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdint.h>
#include "hid.h"  // Make sure to include the appropriate header for HID

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Create a struct to hold system data
typedef struct {
  char sys;
  uint8_t cpu;
  uint8_t gpu;
  uint8_t mem;
} SystemMetrics;

// Global variable to hold metrics
SystemMetrics metrics = {'w', 0, 0, 0};


#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define CTLTB CTL_T(KC_TAB)
#define GUIEI GUI_T(KC_LNG2)
#define ALTKN ALT_T(KC_LNG1)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT,  KC_A,   KC_S,    KC_D,     KC_F,    KC_G,                         KC_H,   KC_J,    KC_K,     KC_L,  KC_SCLN, KC_QUOT,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,     KC_B,                         KC_N,    KC_M,  KC_COMM,  KC_DOT, KC_SLSH, KC_ESC,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LGUI,  MO(1),  KC_SPC,     KC_ENT,   MO(2),  KC_RALT
                                            //`--------------------------'  `--------------------------'

        ),

    [1] = LAYOUT_split_3x6_3(
        //,-----------------  ------------------------------------.                    ,-----------------------------------------------------.
            KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                       XXXXXXX,  KC_7,  KC_8,     KC_9,   XXXXXXX, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,                       XXXXXXX,  KC_4,    KC_5,    KC_6,   XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,  KC_1,   KC_2,    KC_3,   XXXXXXX, KC_RALT,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LGUI, _______, KC_SPC,      KC_ENT,  MO(3),    KC_0
                                            //`--------------------------'  `--------------------------'
        ),

    [2] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            KC_TAB,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_MINS,  KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LGUI, MO(3), KC_SPC,       KC_ENT, _______, KC_RALT
                                                //`--------------------------'  `--------------------------'
        ),

    [3] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                KC_LGUI, _______, KC_SPC,    KC_ENT, _______, KC_RALT
                                            //`--------------------------'  `--------------------------'
        )};


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}


#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return rotation;
    }
}

// void render_crkbd_logo(void) {
//     static const char PROGMEM crkbd_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//         0};
//     oled_write_P(crkbd_logo, false);
// }

uint8_t GAUGE_BAR_X = 45;
uint8_t GAUGE_BAR_HEIGHT = 6;

static void draw_line_h(uint8_t x, uint8_t y, uint8_t len, bool on) {
     for (uint8_t i = 0; i < len; i++) {
         oled_write_pixel(i + x, y, on);
     }
 }

 static void draw_line_v(uint8_t x, uint8_t y, uint8_t len, bool on) {
     for (uint8_t i = 0; i < len; i++) {
         oled_write_pixel(x, i + y, on);
     }
 }

void draw_rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    uint8_t tempHeight;

    draw_line_h(x, y, width, on);
    draw_line_h(x, y + height - 1, width, on);

    tempHeight = height - 2;

    if (tempHeight < 1) return;

    draw_line_v(x, y + 1, tempHeight, on);
    draw_line_v(x + width - 1, y + 1, tempHeight, on);
}

void draw_rect_filled(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    for (int i = x; i < x + width; i++) {
        if (i == x || i == (x + width - 1))
            draw_line_v(i, y, height, on);
        else
            draw_line_v(i, y, height, on);
    }
}


void draw_gauge_bar(uint8_t percentage, char metric, bool on) {
    uint8_t y;
    uint8_t percentf = percentage / 10 * 4;

    switch(metric) {
        case 'c':
            y = 0;
            break;
        case 'g':
            y = 8;
            break;
        case 'm':
            y = 16;
            break;
        default:
            return;
    }

    draw_rect(GAUGE_BAR_X, y, 40, GAUGE_BAR_HEIGHT, on);
    draw_rect_filled(GAUGE_BAR_X, y, percentf, GAUGE_BAR_HEIGHT, on);

    return;
}

void draw_metrics(bool on) {

    char buf[30];

    // Draw CPU metrics
    snprintf(buf, sizeof(buf), "CPU %d%% | ", metrics.cpu);
    oled_write(buf, false);
    draw_gauge_bar(metrics.cpu, 'c', on);
    oled_advance_page(true); // New line

    // Draw GPU metrics
    snprintf(buf, sizeof(buf), "GPU %d%% | ", metrics.gpu);
    oled_write(buf, false);
    draw_gauge_bar(metrics.gpu, 'g', on);
    oled_advance_page(true); // New line

    // Draw MEM metrics
    snprintf(buf, sizeof(buf), "MEM %d%% | ", metrics.mem);
    oled_write(buf, false);
    draw_gauge_bar(metrics.mem, 'm', on);
    oled_advance_page(true); // New line

}

void raw_hid_receive(uint8_t *data, uint8_t length) {
 if (length < 5) {
    return; // Not enough data to determine command
  }
    uint8_t command = data[0];
  switch(command) {
    case 0x01: // Command to update metrics
        metrics.sys = data[1];
        metrics.cpu = data[2];
        metrics.gpu = data[3];
        metrics.mem = data[4];

      break;
    case 0x02: // Command to display error message
        oled_write_P(PSTR("Error getting metrics"), false);

    default:
      // Unknown command, handle or ignore
      break;
  }
}


#    define KEYLOG_LEN 5
char     keylog_str[KEYLOG_LEN] = {};
uint8_t  keylogs_str_idx        = 0;
uint16_t log_timer              = 0;

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    }

    for (uint8_t i = KEYLOG_LEN - 1; i > 0; i--) {
        keylog_str[i] = keylog_str[i - 1];
    }
    if (keycode < 60) {
        keylog_str[0] = code_to_name[keycode];
    }
    keylog_str[KEYLOG_LEN - 1] = 0;

    log_timer = timer_read();
}

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        add_keylog(0);
    }
}

void render_keylogger_status(void) {
    oled_write_P(PSTR("KLogr"), false);
    oled_write(keylog_str, false);
}

void render_default_layer_state(void) {
    oled_write_P(PSTR("Layout"), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(" QRTY"), false);
            break;
    }
}

void render_layer_state(void) {
    oled_write_P(PSTR("LAYER"), false);
    oled_write_P(PSTR("Lower"), layer_state_is(_LOWER));
    oled_write_P(PSTR("Raise"), layer_state_is(_RAISE));
}

void render_keylock_status(led_t led_state) {
    oled_write_P(PSTR("Lock:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("N"), led_state.num_lock);
    oled_write_P(PSTR("C"), led_state.caps_lock);
    oled_write_ln_P(PSTR("S"), led_state.scroll_lock);
}

void render_mod_status(uint8_t modifiers) {
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

// void render_bootmagic_status(void) {
//     /* Show Ctrl-Gui Swap options */
//     static const char PROGMEM logo[][2][3] = {
//         {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
//         {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
//     };
//     oled_write_P(PSTR("BTMGK"), false);
//     oled_write_P(PSTR(" "), false);
//     oled_write_P(logo[0][0], !keymap_config.swap_lctl_lgui);
//     oled_write_P(logo[1][0], keymap_config.swap_lctl_lgui);
//     oled_write_P(PSTR(" "), false);
//     oled_write_P(logo[0][1], !keymap_config.swap_lctl_lgui);
//     oled_write_P(logo[1][1], keymap_config.swap_lctl_lgui);
//     oled_write_P(PSTR(" NKRO"), keymap_config.nkro);
// }

void render_system_logo(char status)
{
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    //switch for windows or apple logo
    switch(status)
    {
        case 'w':
            oled_write_ln_P(logo[0][0], false);
            oled_write_ln_P(logo[0][1], false);
            break;
        case 'a':
            oled_write_ln_P(logo[1][0], false);
            oled_write_ln_P(logo[1][1], false);
            break;
        default:
            return;
    }
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    render_default_layer_state();
    render_keylock_status(host_keyboard_led_state());
    render_mod_status(get_mods());
    render_system_logo(metrics.sys);
}

bool oled_task_user(void) {
    update_log();
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        draw_metrics(true);
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        add_keylog(keycode);
    }
    return true;
}
#endif
