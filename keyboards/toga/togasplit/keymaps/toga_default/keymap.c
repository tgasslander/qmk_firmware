#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
	#include "lufa.h"
	#include "split_util.h"
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _QWERTY_SE,
    _FN,
    _MAX_LAYER,
};

// Keycode defines for layers
#define QWERTY   	DF(_QWERTY)
#define QWERTY_SE	DF(_QWERTY_SE)
#define FN       	MO(_FN)

// Chords
// LCTL + RCTL + {nbr}
// nbr:
// 0 = Default
// 1 = SWE
// 2 = FreeCad
//
// SHIFT + BkSp = DEL

void keyboard_pre_init_user(void) {
  print("keyboard_pre_init_user");
  setPinOutput(B0);
  setPinOutput(D5);
//  debug_enable=true;
//  debug_matrix=true;
//  debug_keyboard=true;
}

void flashLed(int wait) {
  writePinLow(B0);
  writePinLow(D5);
  wait_ms(wait);
  writePinHigh(B0);
  writePinHigh(D5);
} 

#define MODS_CTRL_MASK_BOTH		(MOD_BIT(KC_LCTL) & MOD_BIT(KC_RCTRL))

bool mod_state_layer_switch(uint8_t mod_state) {
    bool layer_switch_mod = false;
    
    if ((mod_state & MOD_BIT(KC_LCTL)) && (mod_state & MOD_BIT(KC_RCTRL))) {
	layer_switch_mod = true;
    }

    return layer_switch_mod;
}

bool switch_to_layer(uint8_t layer, uint8_t mod_state) {
	if (!mod_state_layer_switch(mod_state)) {
	    return false;
	}
	for (uint8_t l=0; l<_MAX_LAYER; l++) {
            layer_off(l);
	}
	layer_on(layer);
	return true;
}

uint8_t mod_state;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  mod_state = get_mods();
  switch (keycode) {
    case KC_BSPC:
    {
      static bool delkey_registered;
	  if (record->event.pressed) {
	  	if (mod_state & MOD_MASK_SHIFT) {
	  	  del_mods(MOD_MASK_SHIFT);
	  	  register_code(KC_DEL);
	  	  delkey_registered = true;
	  	  set_mods(mod_state);
	  	  return false;
	  	}
	  } else {
	    if (delkey_registered) {
	      unregister_code(KC_DEL);
	      delkey_registered = false;
	      return false;
	    }
	  }
	  return true;
	}
	case KC_0:
	{
	  if (switch_to_layer(_QWERTY, mod_state)) {
	    return false;
	  }
	  return true;
	}
	case KC_1:
	{	
	  if (switch_to_layer(_QWERTY_SE, mod_state)) {
	    return false;
	  }
	  return true;
     }
  }
  return true;
}
void keyboard_post_init_user(void) {
  print("keyboard_post_init_user");
}

#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------.             ,------------------------------------------------.
   * |GR_ESC|   1  |   2  |   3  |   4  |   5  |   [  |             |   ]  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   {  |             |   }  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * |FN_CAPS|  A  |   S  |   D  |   F  |   G  |   (  |             |   )  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   -  |             |   =  |   N  |   M  |   ,  |   .  |   /  |Shift |
   * `------+------+------+------+------+------+------'             `------+------+------+------+------+------+------'
   *                             | LGUI |                                         | Space|
   *                             +------+------+                           +------+------+
   *                                    | L OPT|                           | ENTER|       
   *                                    +------+------+             +------+------+       
   *                                           | L CTL|             | R CTL|
   *                                           +------+             +------+
   */
  [_QWERTY] = LAYOUT( \
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LBRC,   KC_RBRC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LCBR,   KC_RCBR,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \
    FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN,   KC_RPRN,  KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MINS,   KC_EQL,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
                                        KC_LGUI, KC_LOPT, KC_LCTL,   KC_RCTL,  KC_ENT,  KC_SPC \
  ),
  
  /* Qwerty_SE
   * ,------------------------------------------------.             ,------------------------------------------------.
   * |      |      |      |      |      |      |      |             |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |             |      |      |      |      |      |      |   Å  |
   * |------+------+------+------+------+------|------|             |------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |             |      |      |      |      |      |   Ö  |   Ä  |
   * |------+------+------+------+------+------+------|             |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |             |      |      |      |      |      |      |      |
   * `------+------+------+------+------+------+------'             `------+------+------+------+------+------+------'
   *                             |      |                                         |      |
   *                             +------+------+                           +------+------+
   *                                    |      |                           |      |       
   *                                    +------+------+             +------+------+       
   *                                           |      |             |      |
   *                                           +------+             +------+
   */
  [_QWERTY_SE] = LAYOUT( \
    KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LBRC,   KC_RBRC,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LCBR,   KC_RCBR,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_LBRC, \
    FN_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN,   KC_RPRN,  KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MINS,   KC_EQL,   KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
                                        KC_LGUI, KC_LOPT, KC_LCTL,   KC_RCTL,  KC_ENT,  KC_SPC \
  ),

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |   ~  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      |      |      |      |      | HOME |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | LEFT | DOWN |  UP  |RIGHT |      | 
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  [_FN] = LAYOUT( \
    KC_TILDE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F5,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12, _______, \
    _______, KC_PGDN,   KC_UP, KC_PGUP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                        _______, _______, _______, _______, _______, _______ \
  )
};

