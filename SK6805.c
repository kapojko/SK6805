#include "SK6805.h"

uint8_t *SK6805_EncodeLedData(uint32_t grbColor, uint8_t *data) {
    uint32_t mask = 0x800000;
    uint8_t  code4bit = 0;

    // Encode color for transmitting
    for (int idx = 0; idx < SK6805_LED_ENCODING_SIZE; ++idx) {
        if ((uint32_t)grbColor & mask) {
            code4bit = 0xC0;
        } else {
            code4bit = 0x80;
        }
        mask >>= 1;
        if ((uint32_t)grbColor & mask) {
            code4bit |= 0x0C;
        } else {
            code4bit |= 0x8;
        }
        mask >>= 1;
        data[idx] = code4bit;
    }

    // Return a pointer to the next led data
    return &(data[SK6805_LED_ENCODING_SIZE]);
}
