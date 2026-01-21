/**
 * RGB LED Map
 *
 * The array follows the physical wiring of the RGB LED strip in each half.
 * It starts with the top right key on the left half and then goes down the
 * first column (including the thumb keys) and then up the second column, etc.
 * The layout is mirrored on the right half.
 *
 * Colors are encoded in HSV (Hue, Saturation, Value) format.
 *
 * Available colors are:
 * HSV_AZURE
 * HSV_BLACK/HSV_OFF
 * HSV_BLUE
 * HSV_CHARTREUSE
 * HSV_CORAL
 * HSV_CYAN
 * HSV_GOLD
 * HSV_GOLDENROD
 * HSV_GREEN
 * HSV_MAGENTA
 * HSV_ORANGE
 * HSV_PINK
 * HSV_PURPLE
 * HSV_RED
 * HSV_SPRINGGREEN
 * HSV_TEAL
 * HSV_TURQUOISE
 * HSV_WHITE
 * HSV_YELLOW
 */
#include "color.h"

#define _OFF_ { HSV_OFF }
// symbol layer (green/yellow)
#define ACCENTED { HSV_GREEN }
#define MOVE { HSV_CHARTREUSE }
#define SYMBOL { HSV_YELLOW }
// media layer (blues)
#define FUNC { HSV_CYAN }
#define MOUSE { HSV_BLUE }
#define NUMPAD { HSV_TURQUOISE }
#define MEDIA { HSV_PURPLE }
// settings layes (reds)
#define FW { HSV_RED }
#define LIGHT { HSV_PINK }
#define RGB { HSV_MAGENTA }
#define SLEEP { HSV_ORANGE }
#define TOGGLE { HSV_ORANGE }

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    // Symbol Layer
    [0] = {
        // Left half
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      SYMBOL,     SYMBOL, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    SYMBOL,     _OFF_,      _OFF_,      _OFF_, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      SYMBOL,     _OFF_, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      SYMBOL,     _OFF_,      ACCENTED,   _OFF_, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      SYMBOL,     _OFF_, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      SYMBOL,     ACCENTED,   _OFF_,      _OFF_, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 7

        // Right half (mirrored)
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      ACCENTED,   _OFF_,      _OFF_,      _OFF_, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      _OFF_,      _OFF_,      ACCENTED,   _OFF_, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      ACCENTED,   _OFF_,      _OFF_,      MOVE, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        MOVE,       MOVE,       _OFF_,      _OFF_,      _OFF_, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      MOVE // Column 7
    },
    // Media Layer
    [1] = {
        // Left half
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       _OFF_,      _OFF_,      MEDIA,      MEDIA, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    _OFF_,      _OFF_,      _OFF_,      FUNC, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      MOUSE,      MOUSE,      MOUSE,      FUNC, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       MOUSE,      MOUSE,      MOUSE,      _OFF_, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      MOUSE,      MOUSE,      MOUSE,      FUNC, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 7

        // Right half (mirrored)
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       _OFF_,      _OFF_,      MEDIA,      MEDIA, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    _OFF_,      _OFF_,      _OFF_,      FUNC, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        NUMPAD,     NUMPAD,     NUMPAD,     NUMPAD,     FUNC, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        FUNC,       NUMPAD,     NUMPAD,     NUMPAD,     NUMPAD, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        NUMPAD,     NUMPAD,     NUMPAD,     NUMPAD,     FUNC, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      NUMPAD,     NUMPAD,     NUMPAD,     NUMPAD  // Column 7
    },
    // Settings Layer
    [2] = {
        // Left half
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      TOGGLE,     TOGGLE, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      FW,         FW,         FW,         _OFF_, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      FW,         _OFF_,      _OFF_, // Column 7

        // Right half (mirrored)
        // Row 1    Row 2       Row 3       Row 4       Row 5
        LIGHT,      LIGHT,      _OFF_,      _OFF_,      _OFF_, // Column 1
        // Row 5    Row 4       Row 3       Row 2       Row 1
                    _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 2
        // Row 1    Row 2       Row 3       Row 4       Row 5
        RGB,        RGB,        RGB,        RGB,        RGB, // Column 3
        // Row 5    Row 4       Row 3       Row 2       Row 1
        RGB,        RGB,        RGB,        RGB,        _OFF_, // Column 4
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 5
        // Row 5    Row 4       Row 3       Row 2       Row 1
        _OFF_,      _OFF_,      _OFF_,      _OFF_,      _OFF_, // Column 6
        // Row 1    Row 2       Row 3       Row 4       Row 5
        _OFF_,      SLEEP,      _OFF_,      _OFF_,      _OFF_  // Column 7
    }
};
