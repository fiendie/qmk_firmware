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
 * Examples:
 *
 *  { 0,   255, 255 },  // Red
 *  { 20,  255, 255 },  // Orange
 *  { 40,  255, 255 },  // Yellow
 *  { 85,  255, 255 },  // Green
 *  { 120, 255, 255 },  // Cyan
 *  { 170, 255, 255 },  // Blue
 *  { 200, 255, 255 },  // Purple
 *  { 230, 255, 255 },  // Magenta
 *
 */

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    // Base Layer
    [0] = {
        // Left half
        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 230, 255, 255 }, { 230, 255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, // Column 1 (with thumbs)

        // Row 5           Row 4              Row 3              Row 2              Row 1
                           { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 2 (4 keys only)

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 230, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3             Row 2             Row 1
        { 85,  255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 4

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 230, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 20,  255, 255 }, // Column 5

        // Row 5           Row 4              Row 3             Row 2             Row 1
        { 20,  255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 6

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 85,  255, 255 }, { 85,  255, 255 }, { 230, 255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, // Column 7

        // Right half (mirrored)
        // Row 1            Row 2             Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 230, 255, 255 }, { 230, 255, 255 }, { 20,  255, 255 }, { 85,  255, 255 }, // Column 1

        // Row 5           Row 4              Row 3               Row 2             Row 1
                           { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 2

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 85,  255, 255 }, { 230, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 120, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, { 85,  255, 255 }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 85,  255, 255 }, { 85,  255, 255 }, { 230, 255, 255 }, { 120, 255, 255 }, { 230, 255, 255 }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 85,  255, 255 }, { 230, 255, 255 }, { 230, 255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }  // Column 7
    },

    // Symbol Layer
    [1] = {
        // Left half
        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 230, 255, 255 }, { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 1

        // Row 5           Row 4              Row 3              Row 2              Row 1
                           { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 2

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 3

        // Row 5           Row 4              Row 3             Row 2             Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, { 0,   0,   0   }, // Column 4

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 120, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 5

        // Row 5           Row 4              Row 3             Row 2             Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 120, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 6

        // Row 1           Row 2              Row 3             Row 4             Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 7

        // Right half (mirrored)
        // Row 1            Row 2             Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 230, 255, 255 }, { 230, 255, 255 }, { 20,  255, 255 }, { 0,   0,   0   }, // Column 1

        // Row 5           Row 4              Row 3               Row 2             Row 1
                           { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 2

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 120, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 120, 255, 255 }, { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }  // Column 7
    },

    // FN Layer
    [2] = {
        // Left half
        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, { 85,  255, 255 }, // Column 1

        // Row 5           Row 4              Row 3              Row 2              Row 1
                           { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 2

        // Row 1           Row 2              Row 3              Row 4               Row 5
        { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 20,  255, 255 }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,  0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 7

        // Right half (mirrored)
        // Row 1            Row 2             Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, // Column 1

        // Row 5           Row 4              Row 3               Row 2             Row 1
                           { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 2

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 230, 255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 85,  255, 255 }, { 85,  255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 230, 255, 255 }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, { 85,  255, 255 }  // Column 7
    },

    // Settings Layer
    [3] = {
        // Left half
        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 85,  255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 1

        // Row 5           Row 4              Row 3              Row 2              Row 1
                           { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 2

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 20,  255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 7

        // Right half (mirrored)
        // Row 1            Row 2             Row 3              Row 4              Row 5
        { 85,  255, 255 }, { 85,  255, 255 }, { 85,  255, 255 }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 1

        // Row 5           Row 4              Row 3               Row 2             Row 1
                           { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 2

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 85,  255, 255 }, // Column 3

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 4

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 5

        // Row 5           Row 4              Row 3              Row 2              Row 1
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, // Column 6

        // Row 1           Row 2              Row 3              Row 4              Row 5
        { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }, { 0,   0,   0   }  // Column 7
    }
};
