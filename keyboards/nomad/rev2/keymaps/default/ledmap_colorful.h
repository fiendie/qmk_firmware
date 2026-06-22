/**
 * RGB LED Map
 *
 * The array follows the physical wiring of the RGB LED strip in each half.
 * It starts with the top right key on the left half and then goes down the
 * first column (including the thumb keys) and then up the second column, etc.
 * The layout is mirrored on the right half.
 *
 * Colors are encoded in HSV (Hue, Saturation, Value) format.
 */

#define RED     { 0,   255, 255 }
#define ORANGE  { 20,  255, 255 }
#define YELLOW  { 40,  255, 255 }
#define GREEN   { 85,  255, 255 }
#define CYAN    { 120, 255, 255 }
#define BLUE    { 170, 255, 255 }
#define PURPLE  { 200, 255, 255 }
#define MAGENTA { 230, 255, 255 }
#define OFF     { 0,   0,   0   }

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    // Base Layer
    [0] = {
        // Left half
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     MAGENTA,   MAGENTA,   GREEN,     GREEN,     // Column 1 (with thumbs)

        // Row 5           Row 4         Row 3         Row 2        Row 1
        CYAN,        CYAN,      CYAN,      MAGENTA,                 // Column 2 (4 keys only)

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     CYAN,      CYAN,      CYAN,      GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        GREEN,       CYAN,      CYAN,      CYAN,      MAGENTA,   // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     CYAN,      CYAN,      CYAN,      ORANGE,    // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        ORANGE,      CYAN,      CYAN,      CYAN,      MAGENTA,   // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        GREEN,       GREEN,     MAGENTA,   GREEN,     GREEN,     // Column 7

        // Right half (mirrored)
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     MAGENTA,   MAGENTA,   ORANGE,    GREEN,     // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        CYAN,        CYAN,      CYAN,      MAGENTA,                 // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     CYAN,      CYAN,      CYAN,      GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        GREEN,       MAGENTA,   CYAN,      CYAN,      MAGENTA,   // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     CYAN,      CYAN,      MAGENTA,   GREEN,     // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        GREEN,       GREEN,     MAGENTA,   CYAN,      MAGENTA,   // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        GREEN,       MAGENTA,   MAGENTA,   GREEN,     GREEN      // Column 7
    },

    // Symbol Layer
    [1] = {
        // Left half
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     MAGENTA,   MAGENTA,   OFF,       OFF,       // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,                     // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       MAGENTA,   OFF,       // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       CYAN,      OFF,       OFF,       // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       CYAN,      OFF,       OFF,       // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 7

        // Right half (mirrored)
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     MAGENTA,   MAGENTA,   ORANGE,    OFF,       // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        MAGENTA,     OFF,       OFF,       MAGENTA,                 // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         CYAN,      OFF,       OFF,       OFF,       // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         CYAN,      MAGENTA,   OFF,       OFF,       // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF        // Column 7
    },

    // FN Layer
    [2] = {
        // Left half
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     OFF,       OFF,       GREEN,     GREEN,     // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       MAGENTA,                 // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     OFF,       OFF,       OFF,       GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       MAGENTA,   // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     OFF,       OFF,       OFF,       ORANGE,    // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       MAGENTA,   // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 7

        // Right half (mirrored)
        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     GREEN,     GREEN,     GREEN,     GREEN,     // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       MAGENTA,                 // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     OFF,       OFF,       OFF,       GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       MAGENTA,   // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        MAGENTA,     OFF,       OFF,       OFF,       GREEN,     // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        GREEN,       GREEN,     OFF,       OFF,       MAGENTA,   // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       GREEN,     GREEN      // Column 7
    },

    // Settings Layer
    [3] = {
        // Left half
        // Row 1           Row 2         Row 3         Row 4        Row 5
        GREEN,       OFF,       OFF,       OFF,       OFF,       // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,                     // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        ORANGE,      OFF,       OFF,       OFF,       OFF,       // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 7

        // Right half (mirrored)
        // Row 1           Row 2         Row 3         Row 4        Row 5
        GREEN,       GREEN,     GREEN,     OFF,       OFF,       // Column 1

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,                     // Column 2

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       GREEN,     // Column 3

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 4

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 5

        // Row 5           Row 4         Row 3         Row 2        Row 1
        OFF,         OFF,       OFF,       OFF,       OFF,       // Column 6

        // Row 1           Row 2         Row 3         Row 4        Row 5
        OFF,         OFF,       OFF,       OFF,       OFF        // Column 7
    }
};
