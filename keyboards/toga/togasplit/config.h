/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

#include "config_common.h"

#define TAPPING_TERM 150

/* Select hand configuration */
#define SOFT_SERIAL_PIN D2
#define EE_HANDS

/* key matrix size */
// Rows are doubled-up 
#define MATRIX_ROWS 10
#define MATRIX_ROW_PINS { B1, B3, B2, B6, B5 }
#define MATRIX_ROW_PINS_RIGHT { D7, E6, B4, B5, B6 }

// wiring of each half
#define MATRIX_COLS 7
#define MATRIX_COL_PINS { B4, E6, D7, C6, D4, D0, D1 }
#define MATRIX_COL_PINS_RIGHT { F4, F5, F6, F7, B1, B3, B2 }

#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
