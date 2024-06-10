#ifndef SK6805_H
#define SK6805_H

#include  <stdint.h>

// NOTE: LEDs data protocol can be simulated with plain SPI (MOSI only)
// with appropriate timing (1 byte per 1.2 us which gives SPI frequency 3.33 MHz),
// where 0 will be encoded with 0x80 and 1 will be encoded with 0xC0
#define SK6805_SPI_FREQ 3330000

// Encoding buffer size for one LED
#define SK6805_LED_ENCODING_SIZE 12

// Encode single LED data to buffer, return pointer to next LED data
uint8_t *SK6805_EncodeLedData(uint32_t grbColor, uint8_t *data);

#endif // SK6805_H
