#include QMK_KEYBOARD_H

//#ifdef PROTOCOL_LUFA
	#include "lufa.h"
	#include "split_util.h"
//#endif


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _FN,
};

// Keycode defines for layers
#define QWERTY   DF(_QWERTY)
#define FN       MO(_FN)

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  RGB_MENU
};

void keyboard_pre_init_user(void) {
	print("keyboard_pre_init_user");
	setPinOutput(B0);
	setPinOutput(D5);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	print("process_record_user");
	writePinHigh(B0);
	writePinHigh(D5);
	return true;
}
void keyboard_post_init_user(void) {
  print("keyboard_post_init_user");
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
}




#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------.             ,------------------------------------------------.
   * |  ESC |   1  |   2  |   3  |   4  |   5  |   -  |             |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |             |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |   F  |   G  |   (  |             |   )  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   {  |             |   }  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * |------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|
   *                             | LGUI |                                         | Space|
   *                             +------+------+                           +------+------+
   *                                    | L CTL|                           | R CTL|       
   *                                    +------+------+             +------+------+       
   *                                           | L OPT|             | Enter|
   *                                           +------+             +------+
   */
  [_QWERTY] = LAYOUT( \
     KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,   KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC,   KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
    FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN,   KC_RPRN, KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LCBR,   KC_RCBR, KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,\
                                        KC_LGUI, KC_LCTL, KC_LOPT,   KC_SPC,  KC_RCTL,  KC_ENT \
  ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      | PGDN |  UP  | PGUP | PRINT| HOME |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | LEFT | DOWN | RIGHT|INSERT| END  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |      |  |      |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \
    _______, KC_PGDN,   KC_UP, KC_PGUP, _______, _______, _______, KC_SLCK, _______, KC_PGDN,   KC_UP, KC_PGUP, KC_PSCR, KC_HOME, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_NLCK, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,  KC_END, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                        _______, _______, _______, _______, _______, _______ \
  )
};

