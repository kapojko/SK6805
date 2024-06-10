#include "SK6805.h"

static struct SK6805_Platform *platform;

void SK6805_Init(struct SK6805_Platform *platformPtr) {
    platform = platformPtr;
}

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

 void SK6805_Transmit(uint32_t grbColors[], int ledsNumber, uint8_t *buf) {
    // Encode led data
    uint8_t *data = buf;
    for (int i = 0; i < ledsNumber; ++i) {
        data = SK6805_EncodeLedData((uint32_t)grbColors[i], data);
    }

    // Transmit with SPI
    platform->spiWrite(buf, SK6805_LED_ENCODING_SIZE * ledsNumber);

    // Delay 80 us, as per datasheet
    platform->delayUs(80);
}
